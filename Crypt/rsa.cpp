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

bigint Rsa::random_integer() 
{
    bigint a = 0;
    int x;
    srand(time(NULL));

    for (int i = 50; i > 1; i--)
    {
        x = rand() % 10;
        a += x * pow(10, i);
    }
    a *= 10;

    do
    {
        x = rand() % 10;
    } while (x % 2 == 0 || x== 5);

    a += x;
    return a;
}

bool Rsa::prime(const bigint& num)
{
    srand(time(NULL));
    bigint a;
    a = rand() % num;
    bigint temp = num - 1;

    return modpow(a, temp, num) == 1;
}

bigint Rsa::euclide(const bigint& a, const bigint& b)
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
        u3 = u1;
        v3 = v1;
        r1 = r2;
        u1 = u2;
        v1 = v2;
        r2 = r3 - q * r2;
        u2 = u3 - q * u2;
        v2 = v3 - q * v2;
    }
    return u1;
}

bigint Rsa::modpow(const bigint& base, const bigint& exp, const bigint& m)
{
    bigint res = 1;
    bigint exp_b = bop::tobin(exp);
    bigint num = base;
    while (exp_b != 0)
    {
        bigint r = (exp_b % 10);
        if (r == 1)
        {
            res = (res * num) % m;
        }
        exp_b /= 10;
        num = (num * num) % m;
    }

    return res;
}

bigint Rsa::exposant_code(const bigint& m)
{
    bigint tab[35] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149 };
    for (int i = 0; i < 25; i++)
    {
        if (m % tab[i] != 0)
            return tab[i];
    }
    return -1;
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
    return modpow(source, ((RealKey*)kp->b)->value, ((RealKey*)kp->a)->value);
}
