#pragma once

#include <QtNetwork>
#include "crypt/key.h"
#include "crypt/engine.h"

#define NORMAL_MESSAGE 1
#define DISPATCH_PKEY 2

class Client
{
    static unsigned long long int idcounter;
public:
    Key* key;
    QTcpSocket* socket;
    bool dummy;
    unsigned long long int cid;

    Client();
    Client(QTcpSocket* socket);
    ~Client();

    void send(const std::string& msg, Engine *engine, bool encrypt = true, unsigned short msgtype = NORMAL_MESSAGE);
    void send(const QString& msg, Engine* engine, bool encrypt = true, unsigned short msgtype = NORMAL_MESSAGE);
};
