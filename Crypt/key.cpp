#include "crypt/global.h"
#include "crypt/key.h"
#include "crypt/math.h"

#include <fstream>

using namespace std;

RealKey::RealKey(const RealKey& source)
{
	value = source.value;
}

RealKey::RealKey(const bigint& value)
{
	this->value = value;
}

RealKey::RealKey(const char* textval, uint8_t(*converter)(char)) : RealKey(bop::from(textval, converter))
{
}

void RealKey::save(const char* filepath)
{
	save(filepath, ascii_convert_to);
}

void RealKey::save(const char* filepath, char(*converter)(uint8_t))
{
	ofstream ofs;
	ofs.open(filepath, ios::out);
	if (ofs.fail())
		return;

	ofs << bop::to(value, converter);
	ofs.close();
}


KeyPair::KeyPair()
{
	a = nullptr;
	b = nullptr;
	autodelete = true;
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
		if (a)
			delete a;
		if (b)
			delete b;
	}
}

void KeyPair::save(const char* filepath)
{
	a->save(filepath);
	b->save(filepath);
}
