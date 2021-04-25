#pragma once

#include "global.h"
#include "key.h"
#include "engine.h"


// Moteur de cryptage César
// Le "chiffrement" se fait uniquement par ajout ou retrait d'un nombre arbitraire
class MI6_CRYPT_API Cesar : public Engine
{
public:
    virtual Key* generate() const;

    virtual bigint run_crypt(const bigint& source, Key* key) const;
    virtual bigint run_decrypt(const bigint& source, Key* key) const;

    virtual Key* parse_default_key(const std::string& str, unsigned int base) const;
};
