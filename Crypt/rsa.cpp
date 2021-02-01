#include "pch.h"
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


RsaKey* Rsa::generate()
{
    // TODO
    return new RsaKey(0, 0, 0);
}

bigint Rsa::run(const bigint& source, Key* key)
{
    // TODO
    return bigint();
}
