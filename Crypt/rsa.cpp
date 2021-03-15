#include "crypt/global.h"
#include "crypt/rsa.h"
#include "crypt/math.h"
#include <math.h>
#include <string>
#include <stdio.h>
#include <time.h>

#include <iostream>

using namespace std;


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
    return Engine::decode(source, ((RsaKey*)key)->publ, padsize);
}


RsaKey* Rsa::generate()
{
    bigint p, q;

    do
    {
        p = random_integer();
    } while (prime(p) != true);

    do
    {
        q = random_integer();
    } while (prime(q) != true);

    bigint n = p * q;
    bigint ind = (p - 1) * (q - 1);
    bigint e = exposant_code(ind); 
    bigint d = euclide(e, ind);

    return new RsaKey(n, e, d);
}

bigint Rsa::run(const bigint& source, Key* key)
{
    KeyPair* kp = (KeyPair*)key;
    return modpow(source, ((RealKey*)kp->b)->value, ((RealKey*)kp->a)->value);
}
