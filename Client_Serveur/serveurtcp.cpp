#include "serveurtcp.h"

#include <QVBoxLayout>

#include "crypt/cesar.h"
#include "crypt/rsa.h"

ServeurTCP::ServeurTCP()
{
    //Création et disposition des widgets de la fenêtre
    etatServeur = new QLabel;
    boutonQuitter = new QPushButton(tr("Quitter"));
    connect(boutonQuitter, SIGNAL(clicked()), qApp, SLOT(quit()));

    QVBoxLayout *layout = new QVBoxLayout;
    layout -> addWidget(etatServeur);
    layout -> addWidget(boutonQuitter);
    setLayout(layout);

    setWindowTitle(tr("Serveur"));

    // Gestion du serveur
    serveur = new QTcpServer(this);
    // Démarrage du serveur sur toutes les IP disponibles et sur le port 50585
    if (!serveur->listen(QHostAddress::Any, 50885)) {
        // si le serveur à rencontré un soucis et n'a pas correctement démarré
        etatServeur->setText(tr("Le serveur n'a pas pu être démarré :<br />") + serveur ->errorString());
    }
    else {
        // Si le serveur a été démarré correctement
        etatServeur->setText(tr("Le serveur a été démarré sur le port <strong>") + QString::number(serveur->serverPort()) + tr("</strong>.<br />Des clients peuvent maintenant se connecter."));
        connect(serveur, SIGNAL(newConnection()), this, SLOT(nouvelleConnexion()));
    }

    tailleMessage = 0;
    flag = 0;
    prtidx = 0;
    pcount = 0;
    parts = nullptr;

#ifdef CESAR
    _engine = new Cesar;

#else
    _engine = new Rsa;
#endif
    _key = _engine->generate();

    parts = nullptr;
}

ServeurTCP::~ServeurTCP()
{
    delete _engine;
    delete _key;
    for(auto client : clients.toStdMap())
        delete client.second;
    if(parts)
        delete[] parts;
}

void ServeurTCP::nouvelleConnexion() {
    envoyerATous(tr("<em>Un nouveau client vient de se connecter</em>"));

    QTcpSocket *nouveauClient = serveur->nextPendingConnection();
    Client* client = new Client(nouveauClient);
    clients.insert(nouveauClient, client);

    connect(nouveauClient, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(nouveauClient, SIGNAL(disconnected()), this, SLOT(deconnexionClient()));

    // On envoie la clé publique du serveur au client
#ifdef CESAR
    client->send(_key->tostr(), _engine, false, false, DISPATCH_PKEY);
#else
    client->send(((RsaKey*)_key)->publ->tostr(), _engine, false, false, DISPATCH_PKEY);
#endif
}


void ServeurTCP::donneesRecues() {
    // 1 : on reçoit un paquet (ou un sous-paquet) d'un des clients

    // On détermine quel client envoie le message (recherche du QTcpSocket du client)
    QTcpSocket *socket = qobject_cast<QTcpSocket *>(sender());

    // si on n'a pas trouvé le client à l'origine du signal, on arrête la méthode
    if (socket == 0) return;

    // Si tout va bien, on continue : on récupère le message
    QDataStream in(socket);

    Client* client = clients.value(socket);
    if(client == nullptr || client->dummy)
    {
        tailleMessage = 0;
        flag = 0;
        return;
    }

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
            while(parts[prtidx] == "" || (cursize = bop::getsize(bigint(parts[prtidx].toStdString(), MSG_REP_BASE), MSG_REP_BASE, true)) < plengths[prtidx])
            {
                uint tr = plengths[prtidx] - cursize;
                if(socket->bytesAvailable() + buffer.size() < tr)
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
            stack.push_back(bigint(parts[i].toStdString(), MSG_REP_BASE));

        m = _engine->msgprep(stack);
        if(parts){
            delete[] parts;
            parts = nullptr;
        }
    }

    if(flag == DISPATCH_PKEY)
    {
        if(client->key)
            delete client->key;
#ifdef CESAR
        client->key = RealKey::from_str(message.toStdString());
#else
        client->key = new RsaKey;
        ((RsaKey*)client->key)->publ = PublicKey::from_str(message.toStdString());
#endif
    }
    else
    {
        _engine->decrypt(*m, _key);
        envoyerATous(QString::fromStdString(m->get()));
    }

    //3 : remise de la taille du message à 0 pour la réception des futurs messages
    delete m;
    tailleMessage = 0;
    flag = 0;
    pcount = 0;
    prtidx = 0;
    buffer = QString();
    plengths = std::vector<quint16>();
}


void ServeurTCP::deconnexionClient() {
    envoyerATous(tr("<em>Un client vient de se déconnecter</em>"));

    // On détermine quel client se déconnecte
    QTcpSocket *socket = qobject_cast<QTcpSocket*>(sender());
    if (socket == 0)
        // Si on n'a pas trouvé le client à l'orgine du signal, on arrête la méthode
        return;

    clients.remove(socket);

    socket->deleteLater();
}


void ServeurTCP::envoyerATous(const QString &message) {
    for(auto client : clients.toStdMap())
        client.second->send(message, _engine);
}






















