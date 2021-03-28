#include "fenetreConnexion.h"
#include "ui_fenetreConnexion.h"
#include "clienttcp.h"
#include <iostream>

fenetreConnexion::fenetreConnexion(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::fenetreConnexion)
{
    ui->setupUi(this);
    socket = new QTcpSocket(this);
    fenetrePrincipale = new ClientTcp(socket);
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));
    connect(socket, SIGNAL(disconnected()), this, SLOT(deconnecte()));
}

fenetreConnexion::~fenetreConnexion()
{
    delete ui;
}

void fenetreConnexion::afficherMessage(QTextEdit * afficheur, QString message) {
    afficheur->append(message);
}

void fenetreConnexion::on_boutonConnexion_clicked() {
    tentativeConnexion();
    ui->boutonConnexion->setEnabled(false);
    socket->abort(); //On désactive les connexions précédentes s'il y en a
    //On va se connecter au serveur demandé
    socket->connectToHost(ui->boxIp->text(), ui->boxPort->value());
}

//Fonction appellé quand on essaie de se connecter
void fenetreConnexion::tentativeConnexion() {
    afficherMessage(ui->displayMessage,tr("<em>Tentative de connexion en cours...</em>"));
}

void fenetreConnexion::connecte() {
    ui->boutonConnexion->setEnabled(true);
    afficherFenetrePrincipale();
}

//Si la connexion est réussi alors on afficher la fenetre de chat et cache la fenetre de connexion
void fenetreConnexion::afficherFenetrePrincipale() {
    fenetrePrincipale->setSocket(this->socket);
    fenetrePrincipale->show();
    this->hide();
    connect(fenetrePrincipale,SIGNAL(closed()), this, SLOT(afficherMenuConnexion()));

}

// Si la fenetre de chat est fermée alors on réaffiche la fenêtre de connexion
void fenetreConnexion::afficherMenuConnexion() {
    this->socket = fenetrePrincipale->getSocket();
    this->show();
    deconnecte();
}

//Cette fonction est appelé lorsqu'on est déconnecté du serveur
void fenetreConnexion::deconnecte() {
    ui->displayMessage->append(tr("<em>Déconnecté du serveur </em>"));
}

void fenetreConnexion::erreurSocket(QAbstractSocket::SocketError erreur) {
    switch(erreur) { //On affiche un message différent selon l'erreur
        case QAbstractSocket::HostNotFoundError:
            ui->displayMessage->append(tr("<em>ERREUR : le serveur n'a pas pu être trouvé. Vérifiez l'IP et le port.</em>"));
            break;
        case QAbstractSocket::ConnectionRefusedError:
            ui->displayMessage->append(tr("<em>ERREUR : le serveur a refusé la connexion. Vérifiez si le programme \"serveur\" a bien été lancé. Vérifiez aussi l'IP et le port.</em>"));
            break;
        case QAbstractSocket::RemoteHostClosedError:
            ui->displayMessage->append(tr("<em>ERREUR : le serveur a coupé la connexion.</em>"));
            break;
        default:
            //Le cas default est appelés pour les erreurs non gérées
            ui->displayMessage->append(tr("<em>ERREUR : ") + socket->errorString() + tr("</em>"));
    }
    ui->boutonConnexion->setEnabled(true);
}
