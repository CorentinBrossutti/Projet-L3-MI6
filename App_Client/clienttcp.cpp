#include "clienttcp.h"
#include "crypt/cesar.h"
#include "crypt/rsa.h"

ClientTcp::ClientTcp(QTcpSocket *socket)
{
    setupUi(this);

    this->socket = socket;
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    //connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));

    tailleMessage = 0;
    flag = 0;
    prtidx = 0;
    pcount = 0;
    parts = nullptr;
    pseudo = chargePseudo();
    boxPseudo->setText(pseudo);
#ifdef CESAR
    _engine = new Cesar;
    QString cle = chargeCle();
    if (cle == "") {
        _lkey = _engine->generate();
        sauvegardeCle(QString::fromStdString(_lkey->tostr()));
    }
    else _lkey = RealKey::from_str(cle.toStdString());
#else
    _engine = new Rsa;
    if (chargeCle() == "") {
        _lkey = _engine->generate();
        sauvegardeCle(QString::fromStdString(_lkey->tostr()));
    }
    else _lkey = RSAKey::from_str(chargeCle().toStdString());
#endif

    _skey = nullptr;
}

ClientTcp::~ClientTcp()
{
    //delete server_key;
    //delete local_key;
    //delete ui;
    delete _engine;
    delete _lkey;
    delete _skey;

    if(parts)
        delete[] parts;
}

QTcpSocket * ClientTcp::getSocket() {
    return this->socket;
}

void ClientTcp::setSocket(QTcpSocket *socket) {
    this->socket = socket;
}

void ClientTcp::afficherMessage(QTextBrowser * afficheur, QString message) {
    afficheur->append(message);
}

//Methdode envoieMessage qui va envoyer un message
void ClientTcp::envoieMessage()
{
    send(tr("<strong>") + pseudo +tr("</strong> : ") + boxMessage->text());
    boxMessage->clear();
    boxMessage->setFocus();
}

void ClientTcp::send(const QString& val, bool part, unsigned short flag, bool encrypt)
{
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    Message msg(val.toStdString());
    if(_skey && encrypt)
        _engine->encrypt(msg, _skey);

    // Envoi du flag
    out << (quint16) flag;
    if(part)
    {
        //On place le flag, puis le nombre de part de notre message
        out << (quint16) msg.count();

        for (unsigned int i = 0; i < msg.count(); i++)
            out << (quint16) mpz_sizeinbase(msg.part(i).get_mpz_t(), 10);

        for (unsigned int i = 0; i < msg.count(); i++)
            out << QString::fromStdString(msg.part(i).get_str());
    }
    else
    {
        out << (quint16) 0 << val;
        out.device()->seek(2); // On se replace au début du paquet
        out << (quint16) (paquet.size() - sizeof(quint16) * 2);
    }
    out.device()->seek(0);
    socket->write(paquet);
}


// appel de envoieMessage si on clique sur le bouton envoyer
void ClientTcp::on_boutonEnvoyer_clicked() {
    envoieMessage();
}

// appel de envoieMessage si on appuie sur 'Entree'
void ClientTcp::on_boxMessage_returnPressed() {
    envoieMessage();
}


//On a reçu un paquet (ou un sous-paquet)
void ClientTcp::donneesRecues() {
    // 1 : on reçoit un paquet (ou un sous-paquet) d'un des clients

    // On détermine quel client envoie le message (recherche du QTcpSocket du client)
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

    // si on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
    if (socket == 0) return;

    // Si tout va bien, on continue : on récupère le message
    QDataStream in(socket);

    if (flag == 0) {
        if(socket->bytesAvailable() < (int)sizeof(quint16))
            return;

        in >> flag;
    }

    Message* m;
    QString message;
    switch(flag)
    {
    case DISPATCH_PKEY:
    case NORMAL_MESSAGE:
        // Si on ne connait pas encore la taille du message, on essaie de la récupérer
        if (tailleMessage == 0) {
            // On n'a pas reçu la taille du message en entier
            if ( socket->bytesAvailable() < (int)sizeof(quint16)) return;

            // Si on a reçu la taille du message en entier, on la récupère
            in >> tailleMessage;
        }

        // Si on connaît la taille du message, on vérifie si on a reçu le message en entier
        if (socket->bytesAvailable() < tailleMessage)
            // Si on a pas encore tout reçu, on arrête la méthode
            return;

        // Si on a reçu tout le message : on le récupère
        in >> message;
        m = _engine->msgprep(message.toStdString());
        break;
    case PARTED_MESSAGE:
        if (pcount == 0) {
            // On n'a pas reçu la taille du message en entier
            if ( socket->bytesAvailable() < (int)sizeof(quint16)) return;

            // Si on a reçu la taille du message en entier, on la récupère
            in >> pcount;
        }

        while(plengths.size() < pcount)
        {
            // On n'a pas reçu la taille du message en entier
            if ( socket->bytesAvailable() < (int)sizeof(quint16)) return;

            // Si on a reçu la taille du message en entier, on la récupère
            quint16 temp;
            in >> temp;
            plengths.push_back(temp);
        }

        parts = new QString[pcount];

        do
        {
            unsigned int cursize = 0;
            while(parts[prtidx] == "" || (cursize = mpz_sizeinbase(bigint(parts[prtidx].toStdString()).get_mpz_t(), 10)) < plengths[prtidx])
            {
                uint tr = plengths[prtidx] - cursize;
                if(socket->bytesAvailable() < tr)
                    return;

                QString tbuf;
                in >> tbuf;
                buffer.append(tbuf);

                parts[prtidx].append(buffer.left(tr));
                buffer.remove(0, tr);
            }
        }while(++prtidx < pcount);

        std::vector<bigint> stack;
        for(unsigned int i = 0;i < pcount;i++)
            stack.push_back(bigint(parts[i].toStdString()));

        m = _engine->msgprep(stack);
        if(parts){
            delete[] parts;
            parts = nullptr;
        }
    }

    if(flag == DISPATCH_PKEY)
    {
#ifdef CESAR
        _skey = RealKey::from_str(message.toStdString());
        send(QString::fromStdString(_lkey->tostr()), false, DISPATCH_PKEY, false);
#else
        _skey = new RsaKey;
        ((RsaKey*)client->key)->publ = PublicKey::from_str(message.toStdString());
        send(QString::fromStdString(((RsaKey*)_lkey)->publ->tostr()), false, DISPATCH_PKEY, false);
#endif
    }
    else
    {
        _engine->decrypt(*m, _lkey);
        afficherMessage(displayMessage, QString::fromStdString(m->get()));
    }

    //3 : remise de la taille du message à 0 pour la réception des futurs messages
    tailleMessage = 0;
    flag = 0;
    pcount = 0;
    plengths = std::vector<quint16>();
    prtidx = 0;
    buffer = QString();
    delete m;
}

//La fonction est appelé si on a réussi à se connecter au serveur
void ClientTcp::connecte() {
    afficherMessage(displayMessage, tr("<em>Connexion réussie !</em>"));
    // TODO envoyer clé publique au serveur
    // local_key->publ->str()
}


//Cette fonction est appelé lorsqu'on est déconnecté du serveur
void ClientTcp::deconnecte() {
    //afficherMessage(displayMessage, tr("<em>Déconnecté du serveur </em>"));
}

//Méthode de changement de Pseudo
void ClientTcp::sauvegardePseudo(QString nom) {
    docXML.sauvegarderPseudo(fichierXML, nom);
    pseudo = chargePseudo();
    boxPseudo->setFocus();
}

void ClientTcp::on_boutonPseudo_clicked() {
    sauvegardePseudo(boxPseudo->text());
}

void ClientTcp::on_boxPseudo_returnPressed() {
    sauvegardePseudo(boxPseudo->text());
}


//Méthode de chargement du pseudo
QString ClientTcp::chargePseudo() {
    return docXML.chargerPseudo(fichierXML);
}


//Méthode de sauvegarde de la Clé
void ClientTcp::sauvegardeCle(QString cle) {
    docXML.sauvegarderCle(fichierXML, cle);
}


//Méthode de chargement de la Clé
QString ClientTcp::chargeCle() {
    return docXML.chargerCle(fichierXML);
}




















