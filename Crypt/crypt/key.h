#pragma once

#include "global.h"


// Une cl� de cryptage g�n�rique
extern struct CAPI Key
{
};

// Cl� de cryptage encapsulant un entier
extern struct CAPI RealKey : public Key
{
public:
	bigint value;

	RealKey(const RealKey& source);
	RealKey(const bigint& value);
};

// Une paire de cl� de cryptage. Permet le polymorphisme et un design composite
extern struct CAPI KeyPair : public Key
{
public:
	Key* a;
	Key* b;
	// Supprimer automatiquement les cl�s allou�es ?
	bool autodelete;

	KeyPair();
	KeyPair(const bigint& aval, const bigint& bval);
	KeyPair(Key* a, Key* b, bool autodelete = true);
	~KeyPair();
};