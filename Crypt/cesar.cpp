#include "crypt/cesar.h"

using namespace std;


Key* Cesar::generate()
{
    return new RealKey(5);
}

bigint Cesar::run_crypt(const bigint &source, Key *key)
{
    return source + ((RealKey*)key)->value;
}

bigint Cesar::run_decrypt(const bigint &source, Key *key)
{
    return source - ((RealKey*)key)->value;
}
