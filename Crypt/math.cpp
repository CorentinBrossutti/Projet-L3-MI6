#include "pch.h"
#include "crypt/math.h"

#include <sstream>
#include <string>

using namespace std;


unsigned int bop::sizebin(const bigint& number)
{
	return mpz_sizeinbase(number.get_mpz_t(), 2);
}

unsigned int bop::count_bytes(const bigint& number)
{
	return unsigned int(ceil(sizebin(number) / 8.0));
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
	{
		_bytes[i] = bitset<8>(str.substr(i * 8, 8));
	}

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