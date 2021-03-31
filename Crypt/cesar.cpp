#include "crypt/cesar.h"

using namespace std;


bigint Cesar::pad(const bigint &number, unsigned int padsize)
{
    return number;
}

bigint Cesar::unpad(const bigint &number, unsigned int padsize)
{
    return number;
}

Key* Cesar::generate()
{
    return nullptr;
}

bigint Cesar::run_crypt(const bigint &source, Key *key)
{
    return source + 5;
}

bigint Cesar::run_decrypt(const bigint &source, Key *key)
{
    return source - 5;
}
