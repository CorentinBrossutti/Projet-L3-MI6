#pragma once

#include "global.h"
#include "key.h"
#include "engine.h"

// Moteur de cryptage César
class CAPI Cesar : public Engine
{
public:
    // Ajoute un nonce au nombre donné
    virtual bigint pad(const bigint& number, unsigned int padsize = PADSIZE_BYTES);
    // Retire le nonce du nombre donné
    virtual bigint unpad(const bigint& number, unsigned int padsize = PADSIZE_BYTES);

    virtual Key* generate();

    virtual bigint run_crypt(const bigint& source, Key* key);
    virtual bigint run_decrypt(const bigint& source, Key* key);
};
