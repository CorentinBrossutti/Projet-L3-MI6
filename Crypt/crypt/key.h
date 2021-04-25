#pragma once

#include "global.h"

// Délimiteur par défaut des parties d'une clé dans sa représentation textuelle
#define STR_KEY_DELIMITER "::"
// Taille du délimiteur par défaut
#define STR_KEY_DELIMSIZE 2
// Base à utiliser pour les valeurs réelles des clés à stocker sous forme textuelle (de 2 à 62)
#define STR_KEY_BASE 62

// Une clé de cryptage générique
struct MI6_CRYPT_API Key
{
public:
    virtual ~Key();

    // Renvoie une représentation textuelle de cette clé
    virtual std::string tostr() const = 0;
    // Sauvegarde la clé dans un fichier
    virtual void save(const char* filepath) const;
};

// Clé de cryptage encapsulant un entier
struct MI6_CRYPT_API RealKey : public Key
{
public:
    // L'entier représenté
	bigint value;

    RealKey();
	RealKey(const RealKey& source);
	RealKey(const bigint& value);
	RealKey(const char* textval, uint8_t(*converter)(char) = ascii_convert_from);
    virtual ~RealKey();

    virtual std::string tostr() const;

    // Ces deux méthodes renvoient une clé réelle depuis sa représentation textuelle
    static RealKey* from_cptr(const char* stringrep, unsigned int base = STR_KEY_BASE);
    static RealKey* from_str(const std::string& stringrep, unsigned int base = STR_KEY_BASE);
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

    // Ces deux méthodes renvoient une paire de clés depuis sa représentation textuelle
    static KeyPair* from_cptr(const char* stringrep, unsigned int base = STR_KEY_BASE);
    static KeyPair* from_str(const std::string& stringrep, unsigned int base = STR_KEY_BASE);
};
