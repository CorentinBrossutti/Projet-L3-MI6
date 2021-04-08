#ifndef SERVEURTCP_H
#define SERVEURTCP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtNetwork>
#include <QLabel>
#include <QPushButton>

#include "client.h"
#include "crypt/key.h"


class ServeurTCP : public QWidget
{
    Q_OBJECT

public:
    ServeurTCP();
    ~ServeurTCP();
    void envoyerATous(const QString &message);

private slots :
    void nouvelleConnexion();
    void donneesRecues();
    void deconnexionClient();

private :
    QLabel *etatServeur;
    QPushButton *boutonQuitter;

    QTcpServer *serveur;
    QMap<QTcpSocket*, Client*> clients;
    quint16 tailleMessage;
    quint16 flag;

    Key* _key;
    Engine* _engine;
};

#endif // SERVEURTCP_H
