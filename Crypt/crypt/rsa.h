#pragma once

#include "global.h"
#include "key.h"
#include "engine.h"


// Clé publique RSA, une paire composée de deux clés numériques
class CAPI PublicKey : public KeyPair
{
public:
	RealKey* n;
	RealKey* e;

	PublicKey(const bigint& n, const bigint& e);
};

// Clé privée RSA, une paire composée de deux clés numériques
class CAPI PrivateKey : public KeyPair
{
public:
	RealKey* n;
	RealKey* d;

	PrivateKey(const bigint& n, const bigint& d);
};

// Clé "trousseau" RSA, composée d'une clé publique et d'une clé privée (design composite donc)
class CAPI RsaKey : public KeyPair
{
public:
	PublicKey* publ;
	PrivateKey* priv;

	RsaKey(const bigint& n, const bigint& e, const bigint& d);
};


// Moteur de cryptage asymétrique RSA
class CAPI Rsa : public Engine
{
public:
	virtual bigint encode(const bigint& source, Key* key, unsigned int padsize = PADSIZE);
	virtual bigint decode(const bigint& source, Key* key, unsigned int padsize = PADSIZE);

	virtual bigint random_integer();
	virtual bool prime(const bigint& num);
	virtual bigint euclide(const bigint& a, bigint& b);
	virtual bigint modpow(const bigint& base, bigint& e, bigint& m);
	virtual bigint toBinary(const bigint& m);
	virtual bigint exposant_code(const bigint& m);
	
	virtual RsaKey* generate();

	virtual bigint run(const bigint& source, Key* key);
};