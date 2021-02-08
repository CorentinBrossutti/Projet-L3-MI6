#ifndef SERVEURTCP_H
#define SERVEURTCP_H

#include <QMainWindow>
#include <QObject>
#include <QWidget>
#include <QtNetwork>
#include <QLabel>
#include <QPushButton>

class ServeurTCP : public QWidget
{
    Q_OBJECT

public:
    ServeurTCP();
    void envoyerATous(const QString &message);

private slots :
    void nouvelleConnexion();
    void donneesRecues();
    void deconnexionClient();

private :
    QLabel *etatServeur;
    QPushButton *boutonQuitter;

    QTcpServer *serveur;
    QList<QTcpSocket *> clients;
    quint16 tailleMessage;
};

#endif // SERVEURTCP_H
