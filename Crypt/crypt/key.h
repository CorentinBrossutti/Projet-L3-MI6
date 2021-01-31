#pragma once

#include "global.h"


// Une clé de cryptage générique
extern struct CAPI Key
{
};

// Clé de cryptage encapsulant un entier
extern struct CAPI RealKey : public Key
{
public:
	bigint value;

	RealKey(const RealKey& source);
	RealKey(const bigint& value);
};

// Une paire de clé de cryptage. Permet le polymorphisme et un design composite
extern struct CAPI KeyPair : public Key
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
};