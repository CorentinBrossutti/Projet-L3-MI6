#include "crypt/global.h"
#include "crypt/rsa.h"
#include "crypt/math.h"

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

PublicKey* PublicKey::from_cptr(const char *stringrep, unsigned int base)
{
    return from_str(string(stringrep), base);
}

PublicKey* PublicKey::from_str(const string &stringrep, unsigned int base)
{
    size_t delimpos = stringrep.find(STR_KEY_DELIMITER);
    if(delimpos == string::npos)
        throw invalid_argument("PublicKey::from_str : impossible d'analyser la chaîne");
    string n = stringrep.substr(0, delimpos), e = stringrep.substr(delimpos + STR_KEY_DELIMSIZE);

    return new PublicKey(bigint(n, base), bigint(e, base));
}


PrivateKey::PrivateKey() : KeyPair()
{
}

PrivateKey::PrivateKey(const bigint& n, const bigint& d) : KeyPair(n, d)
{
    this->n = (RealKey*)a;
    this->d = (RealKey*)b;
}

PrivateKey* PrivateKey::from_cptr(const char *stringrep, unsigned int base)
{
    return from_str(string(stringrep), base);
}

PrivateKey* PrivateKey::from_str(const string &stringrep, unsigned int base)
{
    size_t delimpos = stringrep.find(STR_KEY_DELIMITER);
    if(delimpos == string::npos)
        throw invalid_argument("PrivateKey::from_str : impossible d'analyser la chaîne");
    string n = stringrep.substr(0, delimpos), d = stringrep.substr(delimpos + STR_KEY_DELIMSIZE);

    return new PrivateKey(bigint(n, base), bigint(d, base));
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

RsaKey* RsaKey::from_cptr(const char *stringrep, unsigned int base)
{
    return from_str(string(stringrep), base);
}

RsaKey* RsaKey::from_str(const string &stringrep, unsigned int base)
{
    string temp = stringrep;

    size_t delimpos = stringrep.find(STR_KEY_DELIMITER);
    if(delimpos == string::npos)
        throw invalid_argument("RsaKey::from_str : impossible d'analyser la chaîne");

    string n = temp.substr(0, delimpos);
    temp.erase(0, delimpos + STR_KEY_DELIMSIZE);
    delimpos = temp.find(STR_KEY_DELIMITER);
    if(delimpos == string::npos)
        throw invalid_argument("RsaKey::from_str : impossible d'analyser la chaîne");

    string e = temp.substr(0, delimpos), d = temp.substr(delimpos + STR_KEY_DELIMSIZE);

    return new RsaKey(bigint(n, base), bigint(e, base), bigint(d, base));
}


bigint Rsa::encode(const bigint& source, Key* key, unsigned int padsize) const
{
    Key* encoder;
    if(dynamic_cast<RsaKey*>(key))
        encoder = ((RsaKey*)key)->publ;
    else if(dynamic_cast<KeyPair*>(key))
        encoder = key;
    else
        throw invalid_argument("Rsa::encode : invalid key");

    return Engine::encode(source, encoder, padsize);
}

bigint Rsa::decode(const bigint& source, Key* key, unsigned int padsize) const
{
    Key* decoder;
    if(dynamic_cast<RsaKey*>(key))
        decoder = ((RsaKey*)key)->priv;
    else if(dynamic_cast<KeyPair*>(key))
        decoder = key;
    else
        throw invalid_argument("Rsa::decode : invalid key");

    return Engine::decode(source, decoder, padsize);
}

RsaKey* Rsa::generate() const
{
    bigint p = random_prime(_rand, KSIZE), q = random_prime(_rand, KSIZE);

    bigint n = p * q;
    bigint ind = (p - 1) * (q - 1);
    bigint e = expcode(ind);
    bigint d = euclide(e, ind);

    if (d<0)
        d+=ind;

    return new RsaKey(n, e, d);
}

bigint Rsa::run_crypt(const bigint& source, Key* key) const
{
    KeyPair* kp = (KeyPair*)key;
    return modpow(source, ((RealKey*)kp->b)->value, ((RealKey*)kp->a)->value);
}

bigint Rsa::run_decrypt(const bigint& source, Key* key) const
{
    KeyPair* kp = (KeyPair*)key;
    return modpow(source, ((RealKey*)kp->b)->value, ((RealKey*)kp->a)->value);
}

Key* Rsa::parse_default_key(const std::string &str, unsigned int base) const
{
    try
    {
        return RsaKey::from_str(str, base);
    }
    catch (invalid_argument iarg)
    {
        return nullptr;
    }
}
