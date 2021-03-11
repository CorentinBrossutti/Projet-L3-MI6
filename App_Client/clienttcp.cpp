#include "clienttcp.h"

ClientTcp::ClientTcp()
{
    setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

    tailleMessage = 0;
}

ClientTcp::~ClientTcp()
{
    //delete ui;
}

void ClientTcp::afficherMessage(QTextBrowser * afficheur, QString message) {
    afficheur->append(message);
}

//Tentative de Connexion au serveur
void ClientTcp::on_boutonConnexion_clicked() {
    // On annonce sur la fenêtre qu'on est en train de se connecter
    tentativeConnexion();
    boutonConnexion->setEnabled(false);

    socket->abort(); //On désactive les connexions précédentes s'il y en a
    //On va se connecter au serveur demandé
    socket->connectToHost(boxIp->text(), boxPort->value());
}


//Methdode envoieMessage qui va envoyer un message
void ClientTcp::envoieMessage() {
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);
    //On prépare le paquet à envoyer
    QString messageAEnvoyer = tr("<strong>") + boxPseudo->text() +tr("</strong> : ") + boxMessage->text();

    out << (quint16) 0;
    out << messageAEnvoyer;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    socket->write(paquet); //On envoie le paquet
    boxMessage->clear(); //On vide la zone d'écriture du message
    boxMessage->setFocus(); //On remet le curseur à l'intérieur
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

    if (socket->bytesAvailable() < tailleMessage) return;

    //Si on arrive ici, on peut récupérer le message entier
    QString messageRecu;
    in >> messageRecu;

    //On affiche le message sur la zone de chat
    afficherMessage(displayMessage, messageRecu);

    //On remet la taille du message à  pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
}

//Fonction appellé quand on essaie de se connecter
void ClientTcp::tentativeConnexion() {
    afficherMessage(displayMessage, tr("<em>Tentative de connexion en cours...</em>"));
}

//La fonction est appelé si on a réussi à se connecter au serveur
void ClientTcp::connecte() {
    afficherMessage(displayMessage, tr("<em>Connexion réussie !</em>"));
    boutonConnexion->setEnabled(true);
}


//Cette fonction est appelé lorsqu'on est déconnecté du serveur
void ClientTcp::deconnecte() {
   afficherMessage(displayMessage, tr("<em>Déconnecté du serveur </em>"));
}


void ClientTcp::erreurSocket(QAbstractSocket::SocketError erreur) {
    switch(erreur) { //On affiche un message différent selon l'erreur
        case QAbstractSocket::HostNotFoundError:
            afficherMessage(displayMessage, tr("<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            afficherMessage(displayMessage, tr("<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            afficherMessage(displayMessage, tr("<em>ERREUR : le serveur a coupé la connexion.</em>"));
            break;
        default:
            //Le cas default est appelés pour les erreurs non gérées
            afficherMessage(displayMessage, tr("<em>ERREUR : ") + socket->errorString() + tr("</em>"));
    }
    boutonConnexion->setEnabled(true);
}

























