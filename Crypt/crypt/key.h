#pragma once

#include "global.h"

#define STR_KEY_DELIMITER "::"
#define STR_KEY_DELIMSIZE 2
#define KEY_STR_BASE 62

// Une clé de cryptage générique
struct MI6_CRYPT_API Key
{
public:
    virtual ~Key();

    // Obtenir une représentation textuelle de cette clé
    virtual std::string tostr() const = 0;
    // Sauvegarder la clé dans un fichier
    virtual void save(const char* filepath) const = 0;
};

// Clé de cryptage encapsulant un entier
struct MI6_CRYPT_API RealKey : public Key
{
public:
	bigint value;

    RealKey();
	RealKey(const RealKey& source);
	RealKey(const bigint& value);
	RealKey(const char* textval, uint8_t(*converter)(char) = ascii_convert_from);
    virtual ~RealKey();

    virtual std::string tostr() const;
    virtual void save(const char* filepath) const;

    static RealKey* from_cptr(const char* stringrep, unsigned int base = KEY_STR_BASE);
    static RealKey* from_str(const std::string& stringrep, unsigned int base = KEY_STR_BASE);
};

// Une paire de clés de cryptage. Permet le polymorphisme et un design composite
struct MI6_CRYPT_API KeyPair : public Key
{
public:
	Key* a;
	Key* b;
	// Supprimer automatiquement les clés allouées ?
	bool autodelete;

	KeyPair();
	KeyPair(const bigint& aval, const bigint& bval);
	KeyPair(Key* a, Key* b, bool autodelete = true);
    virtual ~KeyPair();

    virtual std::string tostr() const;
    virtual void save(const char* filepath) const;

    static KeyPair* from_cptr(const char* stringrep, unsigned int base = KEY_STR_BASE);
    static KeyPair* from_str(const std::string& stringrep, unsigned int base = KEY_STR_BASE);
};
