#include "client.h"

#include "crypt/cesar.h"


unsigned long long int Client::idcounter = 0;

Client::Client(QTcpSocket* socket)
{
    this->socket = socket;
    this->cid = idcounter++;
    this->key = nullptr;
    this->dummy = false;
}

Client::Client()
{
    dummy = true;
    key = nullptr;
}

Client::~Client()
{
    if(key)
        delete key;
}

void Client::send(const std::string& msg, Engine *engine, bool part, bool encrypt, unsigned short msgtype)
{
    send(QString::fromStdString(msg), engine, part, encrypt, msgtype);
}

void Client::send(const QString &msg, Engine* engine, bool part, bool encrypt, unsigned short msgtype)
{
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    Message ifmsg(msg.toStdString());
    if(key && encrypt)
        engine->encrypt(ifmsg, key);

    // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    // Puis un deuxième quint16 pour le flag
    out << (quint16) msgtype;

    if(part)
    {
        //On place le flag, puis le nombre de part de notre message
        out << (quint16) ifmsg.count();

        for (unsigned int i = 0; i < ifmsg.count(); i++)
            out << (quint16) mpz_sizeinbase(ifmsg.part(i).get_mpz_t(), 10);

        for (unsigned int i = 0; i < ifmsg.count(); i++)
            out << QString::fromStdString(ifmsg.part(i).get_str());
    }
    else
    {
        out << (quint16) 0 << msg;
        out.device()->seek(2); // On se replace au début du paquet
        out << (quint16) (paquet.size() - sizeof(quint16) * 2);
    }

    out.device()->seek(0);
    socket->write(paquet);
}
