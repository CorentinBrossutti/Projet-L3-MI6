#pragma once

#include "global.h"
#include "rsa.h"


namespace engines
{
	CAPI Engine* resolve(char* arg);
}

namespace keys
{
	CAPI Key* parse_stream(std::istream & stream, uint8_t(*converter)(char) = ascii_convert_from);
	CAPI Key* parse_raw(const char* data, uint8_t(*converter)(char) = ascii_convert_from);
	CAPI Key* parse_file(const char* filepath, uint8_t(*converter)(char) = ascii_convert_from);
}

namespace messages
{
	CAPI Message* retrieve(const char* filepath, uint8_t(*converter)(char) = ascii_convert_from);
}