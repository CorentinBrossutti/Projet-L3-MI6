#pragma once

#include "global.h"


// Une clé de cryptage générique
struct CAPI Key
{
	virtual void save(const char* filepath) = 0;
};

// Clé de cryptage encapsulant un entier
struct CAPI RealKey : public Key
{
public:
	bigint value;

	RealKey(const RealKey& source);
	RealKey(const bigint& value);
	RealKey(const char* textval, uint8_t(*converter)(char) = ascii_convert_from);

	virtual void save(const char* filepath);
	virtual void save(const char* filepath, char (*converter)(uint8_t));
};

// Une paire de clés de cryptage. Permet le polymorphisme et un design composite
struct CAPI KeyPair : public Key
{
public:
	Key* a;
	Key* b;
	// Supprimer automatiquement les clés allouées ?
	bool autodelete;

	KeyPair();
	KeyPair(const bigint& aval, const bigint& bval);
	KeyPair(Key* a, Key* b, bool autodelete = true);
	~KeyPair();

	virtual void save(const char* filepath);
};