#include "crypt/global.h"
#include "crypt/rsa.h"
#include <math.h>
#include <string>
#include <stdio.h>
#include <time.h>

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

bigint Rsa::random_integer() 
{
    bigint a = 0;
    int x;
    srand(time(NULL));

    for (int i = 50; i > 0; i--)
    {
        x = rand() % 10;
        a = a + pow(10, i);
    }

    do
    {
        x = rand() % 10;
    } while (x % 2 == 0 || x== 5);

    a = a + x;
    return a;
}

bigint Rsa::toBinary(const bigint& n)
{
    string r;
    while (n != 0) 
    {
        r += (n % 2 == 0 ? "0" : "1");
        n /= 2;
    }
    return (bigint)r;
}

bool Rsa::prime(const bigint& num)
{
    srand(time(NULL));
    bigint tab[5];
    for (int i = 0; i < 5; i++)
    {
        tab[i] = rand() % n;
    }

    for (int j = 0; j < 5; j++)
    {
        if (modpow(tab[j], num - 1, num) != 1)
        {
            return false;
        }
    }
    return true;
}

bigint Rsa::euclide(const bigint& a, bigint& b)
{
    bigint r1 = a;
    bigint r2 = b;
    bigint u1 = 1;
    bigint u2 = 0;
    bigint v1 = 0;
    bigint v2 = 1;
    bigint q, u3, v3, r3;

    while (r2 != 0)
    {
        q = r1 / r2;
        r3 = r1;
        u3, v3 = u1, v1;
        r1 = r2;
        u1, v1 = u2, v2;
        r2 = r3 - q * r2;
        u2 = u3 - q * u2;
        v2 = v3 - q * v2;
    }
    return u1;
}

bigint Rsa::modpow(const bigint& base, bigint& exp, bigint& m)
{
    bigint res = 1;
    bigint exp_b = toBinary(exp);
    bigint num = base;
    while (exp_b != 0)
    {
        int r = (exp_b % 10);
        if (r == 1)
        {
            res = (res * num) % m;
        }
        exp_b /= 10;
        num = (num * *2) % m;
    }

    return res;
}

bigint Rsa::exposant_code(const bigint& m)
{
    if (m % 3)
    {
        return 3;
    }

    if (m % 7)
    {
        return 7;
    }

    if (m % 11)
    {
        return 11;
    }

    if (m % 13)
    {
        return 13;
    }
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
    bigint e = exposant_code(ind); /* A REVOIR */
    bigint d = euclide(e, ind);

    return new RsaKey(n, e, d);
}

bigint Rsa::run(const bigint& source, Key* key)
{
    KeyPair* kp = (KeyPair*)key;
    bigint res = modpow(source, kp->b, kp->a);
    return res;
}
