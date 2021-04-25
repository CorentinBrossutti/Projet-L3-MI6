#pragma once

#include "global.h"
#include "key.h"
#include "engine.h"

#define KSIZE 32


// Clé publique RSA, une paire composée de deux clés numériques
class MI6_CRYPT_API PublicKey : public KeyPair
{
public:
	RealKey* n;
	RealKey* e;

    PublicKey();
	PublicKey(const bigint& n, const bigint& e);

    static PublicKey* from_cptr(const char* stringrep, unsigned int base = STR_KEY_BASE);
    static PublicKey* from_str(const std::string& stringrep, unsigned int base = STR_KEY_BASE);
};

// Clé privée RSA, une paire composée de deux clés numériques
class MI6_CRYPT_API PrivateKey : public KeyPair
{
public:
	RealKey* n;
	RealKey* d;

    PrivateKey();
	PrivateKey(const bigint& n, const bigint& d);

    static PrivateKey* from_cptr(const char* stringrep, unsigned int base = STR_KEY_BASE);
    static PrivateKey* from_str(const std::string& stringrep, unsigned int base = STR_KEY_BASE);
};

// Clé "trousseau" RSA, composée d'une clé publique et d'une clé privée (design composite donc)
class MI6_CRYPT_API RsaKey : public KeyPair
{
public:
	PublicKey* publ;
	PrivateKey* priv;

    RsaKey();
	RsaKey(const bigint& n, const bigint& e, const bigint& d);

    virtual std::string tostr() const;

    static RsaKey* from_cptr(const char* stringrep, unsigned int base = STR_KEY_BASE);
    static RsaKey* from_str(const std::string& stringrep, unsigned int base = STR_KEY_BASE);
};


// Moteur de cryptage asymétrique RSA
class MI6_CRYPT_API Rsa : public Engine
{
public:
	virtual bigint encode(const bigint& source, Key* key, unsigned int padsize = PADSIZE_BYTES);
	virtual bigint decode(const bigint& source, Key* key, unsigned int padsize = PADSIZE_BYTES);

	virtual RsaKey* generate();

    virtual bigint run_crypt(const bigint& source, Key* key);
    virtual bigint run_decrypt(const bigint& source, Key* key);
};
