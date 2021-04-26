#include "crypt/cesar.h"

using namespace std;


Key* Cesar::generate() const
{
    return new RealKey(28475);
}

bigint Cesar::run_crypt(const bigint &source, Key *key) const
{
    return source + ((RealKey*)key)->value;
}

bigint Cesar::run_decrypt(const bigint &source, Key *key) const
{
    return source - ((RealKey*)key)->value;
}

Key* Cesar::parse_default_key(const std::string& str, unsigned int base) const
{
    try
    {
        return RealKey::from_str(str, base);
    }
    catch (invalid_argument iarg)
    {
        return nullptr;
    }
}
