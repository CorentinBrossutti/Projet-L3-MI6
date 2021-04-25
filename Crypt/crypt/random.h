#pragma once

#include "global.h"
#include "math.h"

#define GEN_SUCCESS 0
#define GEN_ERR_UNKNOWN 1
#define GEN_ERR_CONTEXT 2
#define GEN_ERR_ENTROPY 3


// Classe mère abstraite des implémentations d'aléatoire véritable (variable selon les systèmes)
class RandImpl
{
public:
    virtual ~RandImpl();

    virtual int randb(uint8_t*& buf, const size_t& blen) const = 0;
};

// Pseudo-aléatoire multiplateforme
class RandPseudo : public RandImpl
{
public:
    virtual int randb(uint8_t*& buf, const size_t& blen) const;
};

#if defined (WIN)
#include <random>
class RandWin : public RandImpl
{
public:
    virtual int randb(uint8_t*& buf, const size_t& blen) const;
};
#elif defined (UNIX)
#include <fcntl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
class RandUnix : public RandImpl
{
public:
    virtual int randb(uint8_t*& buf, const size_t& blen) const;
};
#endif

// Classe interface pour l'aléatoire véritable
class MI6_CRYPT_API Randomizer
{
public:
    Randomizer();
    ~Randomizer();

    // Renvoie un grand nombre aléatoire arbitraire, similaire à la fonction std::rand
    bigint rand() const;
    // Renvoie un bigint aléatoire composé du nombre d'octets passé en paramètre
    bigint rand(unsigned int bytes) const;
    // Renvoie un bigint aléatoire avec le digits chiffres dans la base base
    bigint rand(unsigned int digits, unsigned int base) const;

    // Renvoie, quel que soit le système, un randomizer pseudo-aléatoire
    static Randomizer& pseudo();

protected:
    RandImpl* _impl;

private:
    static bool __psinit;
};


// Renvoie un nombre premier aléatoire constitué de bytes octets
bigint random_prime(const Randomizer& rand, unsigned int bytes);
