#include "clienttcp.h"

ClientTcp::ClientTcp(QTcpSocket *socket)
{
    setupUi(this);

    this->socket = socket;
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    //connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));

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

void ClientTcp::afficherMessage(QTextBrowser * afficheur, QString message) {
    afficheur->append(message);
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

//La fonction est appelé si on a réussi à se connecter au serveur
void ClientTcp::connecte() {
    afficherMessage(displayMessage, tr("<em>Connexion réussie !</em>"));
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






















