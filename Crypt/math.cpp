#include "crypt/global.h"
#include "crypt/math.h"

#include <sstream>

using namespace std;


unsigned int bop::sizebin(const bigint& number)
{
	return mpz_sizeinbase(number.get_mpz_t(), 2);
}

unsigned int bop::count_bytes(const bigint& number)
{
    return (unsigned int)(ceil(sizebin(number) / 8.0));
}

string bop::padto(const bigint& from)
{
    string str = from.get_str(2);
    str.insert(0, bop::count_bytes(from) * 8 - bop::sizebin(from), '0');

    return str;
}

bigint bop::from(const char* val, uint8_t(*converter)(char))
{
	stringstream sstream;
	// On transforme le message en entier, pour ça on itère sur les caractères...
    for (unsigned int i = 0; val[i] != '\0'; i++)
        sstream << bitset<8>(converter(val[i])).to_string();

    return bigint(sstream.str(), 2);
}

std::string bop::to(const bigint& val, char(*converter)(uint8_t))
{
	stringstream sstream;

	byteset bytes(val);
	for (unsigned int i = 0; i < bytes.size(); i++)
		sstream << converter(bytes[i].to_ulong());

	return sstream.str();
}

vector<bigint> bop::decompose_vec(const bigint& val, unsigned int blocksz)
{
    vector<bigint> v;
    bigint b = val, mask;
    mpz_ui_pow_ui(mask.get_mpz_t(), 2, blocksz * 8);
    mask -= 1;

    unsigned long long int bcount = count_bytes(val);

    for(unsigned long long int i = 0;i < bcount;i+=blocksz){
        v.push_back((bcount - i) >= blocksz ? b & mask : b);
        b >>= blocksz * 8;
    }

    return v;
}

unsigned int bop::decompose(const bigint& val, bigint*& recp, unsigned int blocksz)
{
    vector<bigint> temp = decompose_vec(val, blocksz);

    recp = new bigint[temp.size()];
    unsigned int idx = temp.size();
    for(bigint bi : temp)
        recp[--idx] = bi;

    return temp.size();
}

bigint bop::recompose(const bigint* from, unsigned int count)
{
    if(count == 0)
        return 0;

    string temp;
    for(unsigned int i = 0;i < count;i++)
        temp += padto(from[i]);

    return bigint(temp.c_str(), 2);
}

bigint random_plike_int(const Randomizer& rand, unsigned int bytes)
{
    bigint b = rand.rand(bytes);
    b -= b % 10;

    bigint x;
    do
    {
        x = rand.rand(1, 10);
    } while (x % 2 == 0 || x == 5);

    return b + x;
}

bool prime(const bigint& num)
{
    bigint x;
    x = rand() % num;
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
        {
            res = (res * temp) % num;
        }
        exp_bin /= 2;
        temp = (temp * temp) % num;
    }

    return res;
}

bigint exposant_code(const bigint& num)
{
    bigint tab[35] = { 2,3,5,7,11,13,17,19,23,29,31,37,41,43,47,53,59,61,67,71,73,79,83,89,97,101,103,107,109,113,127,131,137,139,149 };
    for (int i = 0; i < 25; i++)
    {
        if (num % tab[i] != 0)
            return tab[i];
    }
    return -1;
}


byteset::byteset(const bigint& from)
{
	unsigned int count = bop::count_bytes(from);

	_bytes = new bitset<8>[count];
	/*for (unsigned int i = 0; i < count; i++)
	{
		// Cela fonctionne car get_ui retourne le nombre constitué des bits de poids faible
		// Et bitset prend aussi les bits de poids faible si le nombre en constructeur est trop grand
		_bytes[count - i - 1] = bitset<8>(from.get_ui());
		// Couplé avec le right shift on arrive donc à itérer octet par octet
		from >>= 8;
	}*/
	string str = from.get_str(2);
	str.insert(0, count * 8 - bop::sizebin(from), '0');
    for (unsigned int i = 0; i < count; i++)
        _bytes[i] = bitset<8>(str.substr(i * 8, 8));

    _size = count;
}

byteset::~byteset()
{
	delete[] _bytes;
}

unsigned int byteset::size() const
{
	return _size;
}

bitset<8> byteset::get(unsigned int index) const
{
	if (index >= _size)
		throw invalid_argument("L'indice spécifié est trop grand pour le byteset.");

	return _bytes[index];
}

std::bitset<8> byteset::operator[](int index) const
{
	return get(index);
}

std::ostream& operator<<(std::ostream& output, const byteset& bytes)
{
	for (unsigned int i = 0; i < bytes.size(); i++)
		output << bytes.get(i) << " ";

	return output;
}
