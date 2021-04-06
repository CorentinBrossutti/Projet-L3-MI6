#pragma once

#include "global.h"

#define STR_KEY_DELIMITER "::"
#define STR_KEY_DELIMSIZE 2

// Une clé de cryptage générique
struct CAPI Key
{
    virtual std::string tostr() const = 0;
    virtual void save(const char* filepath) const = 0;
};

// Clé de cryptage encapsulant un entier
struct CAPI RealKey : public Key
{
public:
	bigint value;

    RealKey();
	RealKey(const RealKey& source);
	RealKey(const bigint& value);
	RealKey(const char* textval, uint8_t(*converter)(char) = ascii_convert_from);

    virtual std::string tostr() const;
    virtual void save(const char* filepath) const;
    virtual void save(const char* filepath, char (*converter)(uint8_t)) const;

    static RealKey* from_cptr(const char* stringrep);
    static RealKey* from_str(const std::string& stringrep);
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

    virtual std::string tostr() const;
    virtual void save(const char* filepath) const;

    static KeyPair* from_cptr(const char* stringrep);
    static KeyPair* from_str(const std::string& stringrep);
};
