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
    pseudo = chargePseudo();
    boxPseudo->setText(pseudo);
#ifdef CESAR
    _engine = new Cesar;
#else
    _engine = new Rsa;
#endif
    _lkey = _engine->generate();
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

void ClientTcp::send(const QString& val, unsigned short flag, bool encrypt)
{
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    // Puis un deuxième quint16 pour le flag
    out << (quint16) 0 << (quint16) flag;
    // Chiffrement et envoi
    if(_skey && encrypt)
    {
        Message encrypted(val.toStdString());
        _engine->encrypt(encrypted, _skey);
        out << QString::fromStdString(encrypted.get()); // On ajoute le message à la suite
    }
    else
        out << val;

    out.device()->seek(0); // On se replace au début du paquet

    // On écrase le 0 qu'on avait réservé par la longueur du message
    out << (quint16) (paquet.size() - sizeof(quint16) * 2);

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

    /*Même principe que lorsque le serveur reçoit un paquet :
     * On essaie de récupérer la taille du message
     * Une fois qu'on l'a, on attend d'avoir reçu le message entier
     * (en se basant sur la taille annoncé en tailleMessage)
     * */
    QDataStream in(socket);
    if (tailleMessage==0) {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) return;
        in >> tailleMessage;
    }
    if(flag == 0)
    {
        if (socket->bytesAvailable() < (int)sizeof(quint16)) return;
        in >> flag;
    }

    if (socket->bytesAvailable() < tailleMessage) return;

    //Si on arrive ici, on peut récupérer le message entier
    QString messageRecu;
    in >> messageRecu;

    //Décryptage
    Message m = _engine->msgprep(messageRecu.toStdString());
    switch(flag)
    {
    case NO_FLAG:
        _engine->decrypt(m, _lkey);
        messageRecu = QString::fromStdString(m.get());
        //On affiche le message sur la zone de chat
        afficherMessage(displayMessage, messageRecu);
        break;
    case DISPATCH_PKEY:
        if(_skey)
            delete _skey;
#ifdef CESAR
        _skey = RealKey::from_str(messageRecu.toStdString());
        send(QString::fromStdString(_lkey->tostr()), DISPATCH_PKEY, false);
#else
        _skey = new RsaKey;
        ((RsaKey*)_skey)->publ = PublicKey::from_str(messageRecu.toStdString());
        send(QString::fromStdString(((RsaKey*)_lkey)->publ->tostr()), DISPATCH_PKEY, false);
#endif
        break;
    }

    //On remet la taille du message à  pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
    flag = 0;
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
    boxPseudo->clear();
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






















