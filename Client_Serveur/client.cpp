#include "client.h"

#include "crypt/cesar.h"


unsigned long long int Client::idcounter = 0;

Client::Client(QTcpSocket* socket)
{
    this->socket = socket;
    this->cid = idcounter++;
    this->key = nullptr;
}

Client::Client()
{
    dummy = true;
    key = nullptr;
}

Client::~Client()
{
}

void Client::send(const std::string& msg, Engine *engine, bool encrypt, unsigned short msgtype)
{
    send(QString::fromStdString(msg), engine, encrypt, msgtype);
}

void Client::send(const QString &msg, Engine* engine, bool encrypt, unsigned short msgtype)
{
    // Préparation du paquet
    QByteArray paquet;
    QDataStream out(&paquet, QIODevice::WriteOnly);

    // On écrit 0 au début du paquet pour réserver la place pour écrire la taille
    // Puis un deuxième quint16 pour le flag
    out << (quint16) 0 << (quint16) msgtype;
    // Chiffrement et envoi
    if(key && encrypt)
    {
        Message encrypted(msg.toStdString());
        engine->encrypt(encrypted, key);
        out << QString::fromStdString(encrypted.get()); // On ajoute le message à la suite
    }
    else
        out << msg;

    out.device()->seek(0); // On se replace au début du paquet

    // On écrase le 0 qu'on avait réservé par la longueur du message
    out << (quint16) (paquet.size() - sizeof(quint16) * 2);

    socket->write(paquet);
}
