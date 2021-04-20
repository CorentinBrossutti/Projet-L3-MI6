#pragma once

#include "global.h"
#include <cstdint>

#define GEN_SUCCESS 0
#define GEN_ERR_UNKNOWN 1
#define GEN_ERR_CONTEXT 2
#define GEN_ERR_ENTROPY 3


class RandImpl
{
public:
    virtual int randb(uint8_t*& buf, const size_t& blen) const = 0;
};

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
#include <fctl.h>
class RandUnix : public RandImpl
{
public:
    virtual int randb(uint8_t*& buf, const size_t& blen) const;
};
#endif


class CAPI Randomizer
{
public:
    Randomizer();
    ~Randomizer();

    bigint rand(unsigned int bytes) const;
protected:
    RandImpl* _impl;
};
