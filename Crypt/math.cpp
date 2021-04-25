#include "crypt/math.h"
#include "crypt/global.h"

#include <sstream>

using namespace std;


size_t bop::count_bytes(const bigint& number, bool exact)
{
    return ceil(getsize(number, 2, exact) / 8.0);
}

size_t bop::getsize(const bigint& val, unsigned int base, bool exact)
{
    // Si exact, l'on est obligé de retourner la taille de la représentation textuelle
    // Sinon mpz_sizeinbase suffit malgré sa marge d'erreur de 0/+1
    return exact ?
                val.get_str(base).size() :
                mpz_sizeinbase(val.get_mpz_t(), base);
}

bigint bop::from_cptr(const char* val, uint8_t(*converter)(char))
{
    bigint b;
    // On transforme le message en entier, pour ça on itère sur les caractères... et on les convertit
    for (unsigned int i = 0; val[i] != '\0'; i++)
        b = b * 256 + converter(val[i]);

    return b;
}

bigint bop::from_str(const string& str, uint8_t(*converter)(char))
{
    return from_cptr(str.c_str(), converter);
}

std::string bop::to_str(const bigint& val, char(*converter)(uint8_t))
{
	stringstream sstream;
    bigint temp = val;
    bigint modt;
    for (unsigned int i = 0; i < count_bytes(val); i++)
    {
        // On obtient le dernier octet en faisant le nombre modulo 256 (2^8)
        modt = temp % 256;
        // On convertit l'octet en son caractère et on le renvoie
        sstream << converter(modt.get_ui());
        // On divise le nombre par 256 pour retirer le dernier octet
        mpz_fdiv_q_ui(temp.get_mpz_t(), temp.get_mpz_t(), 256);
    }

    string out = sstream.str();
    // On inverse la représentation car elle commence par la fin
    reverse(out.begin(), out.end());

    return out;
}

vector<bigint> bop::decompose_vec(const bigint& val, unsigned int blocksz, bool inverted)
{
    vector<bigint> v;
    bigint b = val, mod;
    mpz_ui_pow_ui(mod.get_mpz_t(), 2, blocksz * 8);

    while(b > 0)
    {
        v.push_back(b % mod);
        b /= mod;
    }

    // Vieille version du découpage
    /*bigint b = val, mask;
    mpz_ui_pow_ui(mask.get_mpz_t(), 2, blocksz * 8);
    mask -= 1;

    size_t bcount = count_bytes(val);

    for(size_t i = 0;i < bcount;i+=blocksz)
    {
        v.push_back((bcount - i) >= blocksz ? b & mask : b);
        b >>= blocksz * 8;
    }*/

    if(!inverted)
        reverse(v.begin(), v.end());

    return v;
}

size_t bop::decompose(const bigint& val, bigint*& recp, unsigned int blocksz)
{
    // On le garde inversé car on va itérer dans l'autre sens, optimisation
    vector<bigint> temp = decompose_vec(val, blocksz, true);

    recp = new bigint[temp.size()];
    unsigned int idx = temp.size();
    for(bigint bi : temp)
        recp[--idx] = bi;

    return temp.size();
}

bigint bop::recompose_vec(const vector<bigint>& from)
{
    if(from.size() == 0)
        return 0;

    bigint temp;
    bigint mult;
    for(bigint part : from)
    {
        mpz_ui_pow_ui(mult.get_mpz_t(), 16, getsize(part, 16, true));
        temp = temp * mult + part;
    }

    return temp;
}

bigint bop::recompose(const bigint* from, unsigned int count)
{
    if(count == 0)
        return 0;

    bigint temp;
    bigint mult;
    for(unsigned int i = 0;i < count;i++)
    {
        mpz_ui_pow_ui(mult.get_mpz_t(), 16, getsize(from[i], 16, true));
        temp = temp * mult + from[i];
    }

    return temp;
}


bool isprime(const bigint& num, const bigint& rn)
{
    bigint x;
    x = rn % num;
    bigint temp = num - 1;

    return modpow(x, temp, num) == 1;
}

bigint euclide(const bigint& a, const bigint& b)
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

bigint modpow(const bigint& base, const bigint& exp, const bigint& num)
{
    bigint res = 1;
    bigint exp_bin = exp;
    bigint temp = base;
    while (exp_bin != 0)
    {
        bigint r = (exp_bin % 2);
        if (r == 1)
            res = (res * temp) % num;

        exp_bin /= 2;
        temp = (temp * temp) % num;
    }

    return res;
}

bigint expcode(const bigint& num)
{
    bigint tab[35] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149 };
    for (int i = 0; i < 25; i++)
    {
        if (num % tab[i] != 0)
            return tab[i];
    }

    return -1;
}
