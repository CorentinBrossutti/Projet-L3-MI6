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
    ClientTcp(QTcpSocket *socket);
    ~ClientTcp();
    QTcpSocket * getSocket() ;
    void setSocket(QTcpSocket * socket);
    void sauvegardePseudo(QString nom);
    QString chargePseudo();

private slots:

    ///////////////////////////////////////////
    /// Methode
    ///////////////////////////////////////////

    void afficherMessage(QTextBrowser * afficheur, QString message);
    void envoieMessage();
    void donneesRecues();
    void connecte();
    void deconnecte();
<<<<<<< Updated upstream
    void sauvegardePseudo(QString nom);
    QString chargePseudo();
=======
    void erreurSocket(QAbstractSocket::SocketError erreur);
>>>>>>> Stashed changes

    ///////////////////////////////////////////
    /// spécifique QT
    ///////////////////////////////////////////

    void on_boutonEnvoyer_clicked();
    void on_boxMessage_returnPressed();
    void on_boutonPseudo_clicked();
    void on_boxPseudo_returnPressed();

signals:
    void closed();
protected:
    void closeEvent(QCloseEvent *event) override {
        emit closed(); // on émet le signal closed()
        event->accept();
    }

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
