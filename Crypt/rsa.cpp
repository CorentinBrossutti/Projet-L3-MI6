#include "crypt/global.h"
#include "crypt/rsa.h"


PublicKey::PublicKey(const bigint& n, const bigint& e) : KeyPair(n, e)
{
    this->n = (RealKey*)a;
    this->e = (RealKey*)b;
}


PrivateKey::PrivateKey(const bigint& n, const bigint& d) : KeyPair(n, d)
{
    this->n = (RealKey*)a;
    this->d = (RealKey*)b;
}


RsaKey::RsaKey(const bigint& n, const bigint& e, const bigint& d)
{
    publ = new PublicKey(n, e);
    priv = new PrivateKey(n, d);

    a = publ;
    b = priv;
}


bigint Rsa::encode(const bigint& source, Key* key, unsigned int padsize)
{
    return Engine::encode(source, ((RsaKey*)key)->publ, padsize);
}

bigint Rsa::decode(const bigint& source, Key* key, unsigned int padsize)
{
    return Engine::decode(source, ((RsaKey*)key)->priv, padsize);
}

RsaKey* Rsa::generate()
{
    // TODO
    return new RsaKey(0, 0, 0);
}

bigint Rsa::run(const bigint& source, Key* key)
{
    // Clé publique ou clé privé, peu importe, on utilise a (= n) et b (= e ou d)
    KeyPair* kp = (KeyPair*)key;
    //TODO
    return bigint();
}
