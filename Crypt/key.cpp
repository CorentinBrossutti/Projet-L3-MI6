#include "pch.h"
#include "crypt/key.h"
#include "crypt/math.h"


RealKey::RealKey(const RealKey& source)
{
	value = source.value;
}

RealKey::RealKey(const bigint& value)
{
	this->value = value;
}

RealKey::RealKey(const char* textval, uint8_t(*converter)(char)) : RealKey(bigint_from(textval, converter))
{
}

void RealKey::save(const char* filepath, char(*converter)(uint8_t))
{
	// TODO
}


KeyPair::KeyPair()
{
	a = nullptr;
	b = nullptr;
	autodelete = false;
}

KeyPair::KeyPair(const bigint& aval, const bigint& bval) : KeyPair(new RealKey(aval), new RealKey(bval))
{
}

KeyPair::KeyPair(Key* a, Key* b, bool autodelete)
{
	this->a = a;
	this->b = b;
	this->autodelete = autodelete;
}

KeyPair::~KeyPair()
{
	if (autodelete)
	{
		delete a;
		delete b;
	}
}
