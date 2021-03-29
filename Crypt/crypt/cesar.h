#pragma once

#include "global.h"
#include "key.h"
#include "engine.h"

// Moteur de cryptage César
class CAPI Cesar : public Engine
{
public:
    virtual Key* generate();

    virtual bigint run(const bigint& source, Key* key);
};
