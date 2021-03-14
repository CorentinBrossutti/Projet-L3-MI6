#pragma once

#include "global.h"

#include <cstdint>
#include <math.h>
#include <bitset>
#include <vector>


// BIGINT operations
namespace bop
{
	// Retourne le nombre de bits d'un big int
	unsigned int sizebin(const bigint& number);
	// Retourne le nombre d'octets d'un big int
	unsigned int count_bytes(const bigint& number);

	CAPI bigint tobin(const bigint& from);

	CAPI bigint from(const char* val, uint8_t(*converter)(char) = ascii_convert_from);
    CAPI std::string to(const bigint& val, char(*converter)(uint8_t) = ascii_convert_to);

    CAPI std::vector<bigint> decompose_vec(const bigint& val, unsigned int blocksz);
    CAPI unsigned int decompose(const bigint& val, bigint* recp, unsigned int blocksz);
    CAPI bigint recompose(const bigint* from, unsigned int count);
}


// Ensemble d'octets (et non de bits...) liés à un bigint
struct CAPI byteset
{
public:
	byteset(const bigint& from);
	~byteset();

	unsigned int size() const;
	// Retourne l'octet à l'indice donné
	std::bitset<8> get(unsigned int index) const;

	std::bitset<8> operator [](int index) const;
	CAPI friend std::ostream& operator <<(std::ostream& output, const byteset& bytes);
protected:
	unsigned int _size;
	std::bitset<8>* _bytes;
};
