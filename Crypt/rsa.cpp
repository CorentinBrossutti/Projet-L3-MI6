#include "crypt/global.h"
#include "crypt/rsa.h"
#include "crypt/math.h"
#include <math.h>
#include <string>
#include <stdio.h>
#include <time.h>

using namespace std;


PublicKey::PublicKey() : KeyPair()
{
}

PublicKey::PublicKey(const bigint& n, const bigint& e) : KeyPair(n, e)
{
    this->n = (RealKey*)a;
    this->e = (RealKey*)b;
}

PublicKey* PublicKey::from_cptr(const char *stringrep)
{
    return from_str(string(stringrep));
}

PublicKey* PublicKey::from_str(const string &stringrep)
{
    int delimpos = stringrep.find(STR_KEY_DELIMITER, -1);
    if(delimpos == -1)
        throw invalid_argument("PublicKey::from_str : impossible d'analyser la chaîne");
    string n = stringrep.substr(0, delimpos), e = stringrep.substr(delimpos + STR_KEY_DELIMSIZE);

    return new PublicKey(bigint(n), bigint(e));
}


PrivateKey::PrivateKey() : KeyPair()
{
}

PrivateKey::PrivateKey(const bigint& n, const bigint& d) : KeyPair(n, d)
{
    this->n = (RealKey*)a;
    this->d = (RealKey*)b;
}

PrivateKey* PrivateKey::from_cptr(const char *stringrep)
{
    return from_str(string(stringrep));
}

PrivateKey* PrivateKey::from_str(const string &stringrep)
{
    int delimpos = stringrep.find(STR_KEY_DELIMITER, -1);
    if(delimpos == -1)
        throw invalid_argument("PrivateKey::from_str : impossible d'analyser la chaîne");
    string n = stringrep.substr(0, delimpos), d = stringrep.substr(delimpos + STR_KEY_DELIMSIZE);

    return new PrivateKey(bigint(n), bigint(d));
}


RsaKey::RsaKey()
{
}

RsaKey::RsaKey(const bigint& n, const bigint& e, const bigint& d)
{
    publ = new PublicKey(n, e);
    priv = new PrivateKey(n, d);

    a = publ;
    b = priv;
}

string RsaKey::tostr() const
{
    return publ->n->tostr() + STR_KEY_DELIMITER + publ->e->tostr() + STR_KEY_DELIMITER + priv->d->tostr();
}

RsaKey* RsaKey::from_cptr(const char *stringrep)
{
    return from_str(string(stringrep));
}

RsaKey* RsaKey::from_str(const string &stringrep)
{
    string temp = stringrep;

    int delimpos = stringrep.find(STR_KEY_DELIMITER, -1);
    if(delimpos == -1)
        throw invalid_argument("RsaKey::from_str : impossible d'analyser la chaîne");

    string n = temp.substr(0, delimpos);
    temp.erase(delimpos + STR_KEY_DELIMSIZE);
    delimpos = temp.find(STR_KEY_DELIMITER, -1);
    if(delimpos == -1)
        throw invalid_argument("RsaKey::from_str : impossible d'analyser la chaîne");

    string e = stringrep.substr(0, delimpos), d = stringrep.substr(delimpos + STR_KEY_DELIMSIZE);

    return new RsaKey(bigint(n), bigint(e), bigint(d));
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

    if (d<0)
    {
        d+=ind;
    }

    return new RsaKey(n, e, d);
}

bigint Rsa::run_crypt(const bigint& source, Key* key)
{
    KeyPair* kp = (KeyPair*)key;
    return modpow(source, ((RealKey*)kp->b)->value, ((RealKey*)kp->a)->value);
}

bigint Rsa::run_decrypt(const bigint& source, Key* key)
{
    KeyPair* kp = (KeyPair*)key;
    return modpow(source, ((RealKey*)kp->b)->value, ((RealKey*)kp->a)->value);
}
