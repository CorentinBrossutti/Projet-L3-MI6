#include "clienttcp.h"
#include "ui_clienttcp.h"

ClientTcp::ClientTcp()
{
    setupUi(this);

    socket = new QTcpSocket(this);
    connect(socket, SIGNAL(readyRead()), this, SLOT(donneesRecues()));
    connect(socket, SIGNAL(connected()), this, SLOT(connecte()));
    connect(socket, SIGNAL(error(QAbstractSocket::SocketError)), this, SLOT(erreurSocket(QAbstractSocket::SocketError)));

    tailleMessage = 0;
}

ClientTcp::~ClientTcp()
{
    //delete ui;
}

