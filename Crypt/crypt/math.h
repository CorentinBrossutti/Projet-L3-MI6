#pragma once

#include "global.h"

#include <cstdint>
#include <math.h>
#include <bitset>


// BIGINT operations
namespace bop
{
	// Retourne le nombre de bits d'un big int
	unsigned int sizebin(const bigint& number);
	// Retourne le nombre d'octets d'un big int
	unsigned int count_bytes(const bigint& number);
	CAPI bigint from(const char* val, uint8_t(*converter)(char) = ascii_convert_from);
	CAPI std::string to(const bigint & val, char(*converter)(uint8_t) = ascii_convert_to);
}


// Ensemble d'octets (et non de bits...) li�s � un bigint
extern struct CAPI byteset
{
public:
	byteset(const bigint& from);
	~byteset();

	unsigned int size() const;
	// Retourne l'octet � l'indice donn�
	std::bitset<8> get(unsigned int index) const;

	std::bitset<8> operator [](int index) const;
	CAPI friend std::ostream& operator <<(std::ostream& output, const byteset& bytes);
protected:
	unsigned int _size;
	std::bitset<8>* _bytes;
};