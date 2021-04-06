#ifndef CLIENTTCP_H
#define CLIENTTCP_H

#include <QMainWindow>
#include <QtWidgets>
#include <QtNetwork>
#include <QtXml>

#include "ui_clienttcp.h" //La fenêtre générée
#include "xmldoc.h" //Notre module de gestion des sauvegardes
#include "crypt/engine.h"

#define NO_FLAG 1
#define DISPATCH_PKEY 2

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

    void send(const QString& val, unsigned short flag = NO_FLAG, bool encrypt = true);

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

private:
    QTcpSocket *socket; //Représente le serveur
    quint16 tailleMessage;
    quint16 flag;
    QString fichierXML = "config.txt";
    XmlDoc docXML;
    QString pseudo;

    Engine* _engine;
    Key* _skey;
    Key* _lkey;
};
#endif // CLIENTTCP_H
