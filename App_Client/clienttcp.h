#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtNetwork>
#include <QtXml>
#include "ui_clienttcp.h" //La fenêtre générée
#include "xmldoc.h" //Notre module de gestion des sauvegardes

/*QT_BEGIN_NAMESPACE
namespace Ui { class ClientTcp; }
QT_END_NAMESPACE*/

class ClientTcp : public QMainWindow, private Ui::ClientTcp
{
    Q_OBJECT

public:
    //ClientTcp(QWidget *parent = nullptr);
    ClientTcp();
    ~ClientTcp();

private slots:

    ///////////////////////////////////////////
    /// Methode
    ///////////////////////////////////////////

    void afficherMessage(QTextBrowser * afficheur, QString message);
    void envoieMessage();
    void donneesRecues();
    void tentativeConnexion();
    void connecte();
    void deconnecte();
    void erreurSocket(QAbstractSocket::SocketError erreur);
    void sauvegardePseudo(QString nom);
    QString chargePseudo();

    ///////////////////////////////////////////
    /// spécifique QT
    ///////////////////////////////////////////

    void on_boutonConnexion_clicked();
    void on_boutonEnvoyer_clicked();
    void on_boxMessage_returnPressed();
    void on_boutonPseudo_clicked();
    void on_boxPseudo_returnPressed();

private:
    QTcpSocket *socket; //Représente le serveur
    quint16 tailleMessage;
    QString fichierXML = "config.txt";
    XmlDoc docXML;
    QString pseudo;
};
#endif // CLIENTTCP_H
