#pragma once

#include "global.h"

#define GEN_SUCCESS 0
#define GEN_ERR_UNKNOWN 1
#define GEN_ERR_CONTEXT 2
#define GEN_ERR_ENTROPY 3


// Classe mère abstraite des implémentations d'aléatoire véritable (variable selon les systèmes)
class RandImpl
{
public:
    virtual int randb(uint8_t*& buf, const size_t& blen) const = 0;
};

// Pseudo-aléatoire multiplateforme
class RandOther : public RandImpl
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
class RandUnix : public RandImpl
{
public:
    virtual int randb(uint8_t*& buf, const size_t& blen) const;
};
#endif

// Classe interface pour l'aléatoire véritable
class CAPI Randomizer
{
public:
    Randomizer();
    ~Randomizer();

    // Renvoie un bigint aléatoire composé du nombre d'octets passé en paramètre
    bigint rand(unsigned int bytes) const;

    static bool init_rand_other;
protected:
    RandImpl* _impl;
};
