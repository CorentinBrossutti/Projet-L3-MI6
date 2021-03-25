#include "clienttcp.h"

ClientTcp::ClientTcp(QTcpSocket *socket)
{
    setupUi(this);

    this->socket = socket;
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
   // connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
    //connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

    tailleMessage = 0;
    pseudo = chargePseudo();
    boxPseudo->setText(pseudo);
}

ClientTcp::~ClientTcp()
{
    //delete ui;
}

QTcpSocket * ClientTcp::getSocket() {
    return this->socket;
}

void ClientTcp::setSocket(QTcpSocket *socket) {
    this->socket = socket;
}

//Tentative de Connexion au serveur
void ClientTcp::on_boutonConnexion_clicked() {
    // On annonce sur la fenêtre qu'on est en train de se connecter
    displayMessage->append(tr("<em>Tentative de connexion en cours...</em>"));
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

    QString messageAEnvoyer = tr("<strong>") + pseudo +tr("</strong> : ") + boxMessage->text();

    out << (quint16) 0;
    out << messageAEnvoyer;
    out.device()->seek(0);
    out << (quint16) (paquet.size() - sizeof(quint16));

    socket->write(paquet); //On envoie le paquet
    boxMessage->clear(); //On vide la zone d'écriture du message
    boxMessage->setFocus(); //On remet le curseur à l'intérieur
}

//On va coder "Si on appuie sur la touche Entrée çà aura le même effet que cliquer sur "Envoyer"
void ClientTcp::on_boxMessage_returnPressed() {
    on_boutonEnvoyer_clicked();
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
    displayMessage->append(messageRecu);

    //On remet la taille du message à  pour pouvoir recevoir de futurs messages
    tailleMessage = 0;
}


//La fonction est appelé si on a réussi à se connecter au serveur
void ClientTcp::connecte() {
    displayMessage->append(tr("<em>Connexion réussie !</em>"));
   // boutonConnexion->setEnabled(true);
}


//Cette fonction est appelé lorsqu'on est déconnecté du serveur
void ClientTcp::deconnecte() {
    //displayMessage->append(tr("<em>Déconnecté du serveur </em>"));
}


void ClientTcp::erreurSocket(QAbstractSocket::SocketError erreur) {
    switch(erreur) { //On affiche un message différent selon l'erreur
        case QAbstractSocket::HostNotFoundError:
            displayMessage->append(tr("<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            displayMessage->append(tr("<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            displayMessage->append(tr("<em>ERREUR : le serveur a coupé la connexion.</em>"));
            break;
        default:
            //Le cas default est appelés pour les erreurs non gérées
            displayMessage->append(tr("<em>ERREUR : ") + socket->errorString() + tr("</em>"));
    }
    boutonConnexion->setEnabled(true);
}

//Méthode de changement de Pseudo
void ClientTcp::sauvegardePseudo(QString nom) {
    docXML.sauvegarderPseudo(fichierXML, nom);
    pseudo = chargePseudo();
    boxPseudo->clear();
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






















