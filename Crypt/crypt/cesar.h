#pragma once

#include "global.h"
#include "key.h"
#include "engine.h"


// Moteur de cryptage César
class CAPI Cesar : public Engine
{
public:
    virtual Key* generate();

    virtual bigint run_crypt(const bigint& source, Key* key);
    virtual bigint run_decrypt(const bigint& source, Key* key);
};
