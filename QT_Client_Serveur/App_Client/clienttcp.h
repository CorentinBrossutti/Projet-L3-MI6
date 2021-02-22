#ifndef CLIENTTCP_H
#define CLIENTTCP_H

//#include <QMainWindow>
#include <QtWidgets>
#include <QtNetwork>
#include "ui_clienttcp.h" //La fenêtre générée

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
    void on_boutonConnexion_clicked();
    void on_boutonEnvoyer_clicked();
    void on_message_returnPressed();
    void donneesRecues();
    void connecte();
    void deconnecte();
    void erreurSocket(QAbstractSocket::SocketError erreur);

private:
    QTcpSocket *socket; //Représente le serveur
    quint16 tailleMessage;
};
#endif // CLIENTTCP_H
