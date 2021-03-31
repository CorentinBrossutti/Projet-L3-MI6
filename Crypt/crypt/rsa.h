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

    PublicKey();
	PublicKey(const bigint& n, const bigint& e);

    static PublicKey from_cptr(const char* stringrep);
    static PublicKey from_str(const std::string& stringrep);
};

// Clé privée RSA, une paire composée de deux clés numériques
class CAPI PrivateKey : public KeyPair
{
public:
	RealKey* n;
	RealKey* d;

    PrivateKey();
	PrivateKey(const bigint& n, const bigint& d);

    static PrivateKey from_cptr(const char* stringrep);
    static PrivateKey from_str(const std::string& stringrep);
};

// Clé "trousseau" RSA, composée d'une clé publique et d'une clé privée (design composite donc)
class CAPI RsaKey : public KeyPair
{
public:
	PublicKey* publ;
	PrivateKey* priv;

    RsaKey();
	RsaKey(const bigint& n, const bigint& e, const bigint& d);

    virtual std::string tostr() const;

    static RsaKey from_cptr(const char* stringrep);
    static RsaKey from_str(const std::string& stringrep);
};


// Moteur de cryptage asymétrique RSA
class CAPI Rsa : public Engine
{
public:
	virtual bigint encode(const bigint& source, Key* key, unsigned int padsize = PADSIZE_BYTES);
	virtual bigint decode(const bigint& source, Key* key, unsigned int padsize = PADSIZE_BYTES);

	virtual RsaKey* generate();

    virtual bigint run_crypt(const bigint& source, Key* key);
    virtual bigint run_decrypt(const bigint& source, Key* key);
};
