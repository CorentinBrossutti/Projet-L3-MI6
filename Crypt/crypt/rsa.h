#pragma once

#include "global.h"
#include "key.h"
#include "engine.h"


// Cl� publique RSA, une paire compos�e de deux cl�s num�riques
extern class CAPI PublicKey : public KeyPair
{
public:
	RealKey* n;
	RealKey* e;

	PublicKey(const bigint& n, const bigint& e);
};

// Cl� priv�e RSA, une paire compos�e de deux cl�s num�riques
extern class CAPI PrivateKey : public KeyPair
{
public:
	RealKey* n;
	RealKey* d;

	PrivateKey(const bigint& n, const bigint& d);
};

// Cl� "trousseau" RSA, compos�e d'une cl� publique et d'une cl� priv�e (design composite donc)
extern class CAPI RsaKey : public KeyPair
{
public:
	PublicKey* publ;
	PrivateKey* priv;

	RsaKey(const bigint& n, const bigint& e, const bigint& d);
};


// Moteur de cryptage asym�trique RSA
extern class CAPI Rsa : public Engine
{
public:
	virtual bigint encode(const bigint& source, Key* key, unsigned int padsize = PADSIZE);
	virtual bigint decode(const bigint& source, Key* key, unsigned int padsize = PADSIZE);

	virtual RsaKey* generate();

	virtual bigint run(const bigint& source, Key* key);
};