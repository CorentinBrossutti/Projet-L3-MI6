#include "crypt/global.h"
#include "crypt/key.h"
#include "crypt/math.h"

#include <fstream>

using namespace std;

RealKey::RealKey()
{
}

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

string RealKey::tostr() const
{
    return value.get_str();
}

void RealKey::save(const char* filepath) const
{
	save(filepath, ascii_convert_to);
}

void RealKey::save(const char* filepath, char(*converter)(uint8_t)) const
{
	ofstream ofs;
	ofs.open(filepath, ios::out);
	if (ofs.fail())
		return;

	ofs << bop::to(value, converter);
	ofs.close();
}

RealKey* RealKey::from_cptr(const char *stringrep)
{
    return from_str(string(stringrep));
}

RealKey* RealKey::from_str(const string &stringrep)
{
    return new RealKey(bigint(stringrep));
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

string KeyPair::tostr() const
{
    return a->tostr() + STR_KEY_DELIMITER + b->tostr();
}

void KeyPair::save(const char* filepath) const
{
    a->save(filepath);
    b->save(filepath);
}

KeyPair* KeyPair::from_cptr(const char *stringrep)
{
    return from_str(string(stringrep));
}

KeyPair* KeyPair::from_str(const string &stringrep)
{
    int delimpos = stringrep.find(STR_KEY_DELIMITER, -1);
    if(delimpos == -1)
        throw invalid_argument("KeyPair::from_str : impossible d'analyser la chaîne");
    string a = stringrep.substr(0, delimpos), b = stringrep.substr(delimpos + STR_KEY_DELIMSIZE);

    return new KeyPair(bigint(a), bigint(b));
}
