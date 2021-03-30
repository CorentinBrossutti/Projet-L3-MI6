#ifndef FENETRECONNEXION_H
#define FENETRECONNEXION_H

#include <QDialog>
#include <QMainWindow>
#include <QtWidgets>
#include <QtNetwork>
#include "ui_fenetreConnexion.h"
#include "clienttcp.h"


/*namespace Ui {
class fenetreConnexion;
}*/

class fenetreConnexion : public QDialog , private Ui::fenetreConnexion
{
    Q_OBJECT

public:
    explicit fenetreConnexion(QWidget *parent = nullptr);
    ~fenetreConnexion();


private slots:

////////////////////////////////////////////////////////////////////
/// méthode
///////////////////////////////////////////////////////////////////


    void connecte();
    void erreurSocket(QAbstractSocket::SocketError erreur);
    void afficherFenetrePrincipale();
    void afficherMenuConnexion();
    void deconnecte();
    void afficherMessage(QTextEdit * afficheur, QString message);
    void tentativeConnexion();

//////////////////////////////////////////////////////////////////
/// Spécifique QT
/////////////////////////////////////////////////////////////////

    void on_boutonConnexion_clicked();

private:
    Ui::fenetreConnexion *ui;
    QTcpSocket *socket; //Représente le serveur
    ClientTcp *fenetrePrincipale;

    QString fichierXML = "config.txt";
    XmlDoc docXML;
    QString pseudo;
};

#endif // FENETRECONNEXION_H
