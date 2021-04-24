#pragma once

#include "global.h"
#include "rsa.h"
#include "cesar.h"


namespace engines
{
	MI6_CRYPT_API Engine* resolve(char* arg);
}

namespace keys
{
	MI6_CRYPT_API Key* parse_stream(std::istream & stream, uint8_t(*converter)(char) = ascii_convert_from);
	MI6_CRYPT_API Key* parse_raw(const char* data, uint8_t(*converter)(char) = ascii_convert_from);
	MI6_CRYPT_API Key* parse_file(const char* filepath, uint8_t(*converter)(char) = ascii_convert_from);
}

namespace msgs
{
	MI6_CRYPT_API Message* retrieve(const char* filepath, uint8_t(*converter)(char) = ascii_convert_from);
}
