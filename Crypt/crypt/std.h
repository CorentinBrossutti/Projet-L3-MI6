#pragma once

#include "global.h"
#include "rsa.h"
#include "cesar.h"


namespace engines
{
    // Renvoie un moteur de cryptage basé sur son nom (arg) si existant, sinon nullptr
	MI6_CRYPT_API Engine* resolve(char* arg);
    // Opération dynamique basée sur un argument textuel
    MI6_CRYPT_API bool operate(Engine* engine, const std::string& arg, Message& message, Key*& key, unsigned int padsize = PADSIZE_BYTES);
}

namespace keys
{
    MI6_CRYPT_API Key* fparse(Engine* engine, const char* filepath, unsigned int base = STR_KEY_BASE);
}

namespace msgs
{
    MI6_CRYPT_API Message* retrieve(const char* filepath, bool encrypted = false, unsigned int nbase = 62);
}
