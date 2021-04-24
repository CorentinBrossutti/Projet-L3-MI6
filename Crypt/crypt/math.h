#pragma once

#include "global.h"
#include "random.h"

#include <math.h>
#include <bitset>
#include <vector>


// BIGINT operations
namespace bop
{
	// Retourne le nombre d'octets d'un big int
    unsigned int count_bytes(const bigint& number);

    MI6_CRYPT_API bigint from_cptr(const char* val, uint8_t(*converter)(char) = ascii_convert_from);
    MI6_CRYPT_API bigint from_str(const std::string& str, uint8_t(*converter)(char) = ascii_convert_from);
    MI6_CRYPT_API std::string to_str(const bigint& val, char(*converter)(uint8_t) = ascii_convert_to);

    std::vector<bigint> decompose_vec(const bigint& val, unsigned int blocksz, bool inverted = false);
    unsigned int decompose(const bigint& val, bigint*& recp, unsigned int blocksz);
    bigint recompose(const bigint* from, unsigned int count);
}


bigint random_plike_int(const Randomizer& rand, unsigned int bytes);
bool prime(const bigint& num);
bigint euclide(const bigint& a, const bigint& b);
bigint modpow(const bigint& base, const bigint& e, const bigint& num);
bigint exposant_code(const bigint& num);


// Ensemble d'octets (et non de bits...) liés à un bigint
struct MI6_CRYPT_API byteset
{
public:
	byteset(const bigint& from);
	~byteset();

	unsigned int size() const;
	// Retourne l'octet à l'indice donné
	std::bitset<8> get(unsigned int index) const;

	std::bitset<8> operator [](int index) const;
    MI6_CRYPT_API friend std::ostream& operator <<(std::ostream& output, const byteset& bytes);
protected:
	unsigned int _size;
	std::bitset<8>* _bytes;
};
