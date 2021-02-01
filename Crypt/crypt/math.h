#pragma once

#include "global.h"

#include <cstdint>
#include <math.h>
#include <bitset>


// Retourne le nombre de bits d'un big int
unsigned int sizeb(const bigint& number);
// Retourne le nombre d'octets d'un big int
unsigned int countb(const bigint& number);
extern "C" CAPI bigint bigint_from(const char* val, uint8_t(*converter)(char) = ascii_convert_from);


// Ensemble d'octets (et non de bits...) liés à un bigint
extern struct CAPI byteset
{
public:
	byteset(bigint from);
	~byteset();

	unsigned int size() const;
	// Retourne l'octet à l'indice donné
	std::bitset<8> get(unsigned int index) const;

	std::bitset<8> operator [](int index) const;
	extern CAPI friend std::ostream& operator <<(std::ostream& output, const byteset& bytes);
protected:
	unsigned int _size;
	std::bitset<8>* _bytes;
};