#include "crypt/global.h"
#include "crypt/key.h"
#include "crypt/math.h"
#include "crypt/util.h"

using namespace std;


Key::~Key() {}

void Key::save(const char* filepath) const
{
    files::fwrite_str(filepath, tostr());
}

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

RealKey::RealKey(const char* textval, uint8_t(*converter)(char)) : RealKey(bop::from_cptr(textval, converter))
{
}

RealKey::~RealKey(){}

string RealKey::tostr() const
{
    return value.get_str(STR_KEY_BASE);
}

RealKey* RealKey::from_cptr(const char *stringrep, unsigned int base)
{
    return from_str(string(stringrep), base);
}

RealKey* RealKey::from_str(const string &stringrep, unsigned int base)
{
    return new RealKey(bigint(stringrep, base));
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

KeyPair* KeyPair::from_cptr(const char *stringrep, unsigned int base)
{
    return from_str(string(stringrep), base);
}

KeyPair* KeyPair::from_str(const string &stringrep, unsigned int base)
{
    size_t delimpos = stringrep.find(STR_KEY_DELIMITER);
    if(delimpos == string::npos)
        throw invalid_argument("KeyPair::from_str : impossible d'analyser la chaîne");
    string a = stringrep.substr(0, delimpos), b = stringrep.substr(delimpos + STR_KEY_DELIMSIZE);

    return new KeyPair(bigint(a, base), bigint(b, base));
}
