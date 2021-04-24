#pragma once

#include <QtNetwork>
#include "crypt/key.h"
#include "crypt/engine.h"

#define NORMAL_MESSAGE 1
#define PARTED_MESSAGE 2
#define DISPATCH_PKEY 3

#define MSG_REP_BASE 62

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

    void send(const std::string& msg, Engine *engine, bool part = true, bool encrypt = true, unsigned short msgtype = PARTED_MESSAGE);
    void send(const QString& msg, Engine* engine, bool part = true, bool encrypt = true, unsigned short msgtype = PARTED_MESSAGE);
};
