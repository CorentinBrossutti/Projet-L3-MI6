#pragma once

#include "global.h"
#include "rsa.h"


namespace engines
{
	extern "C" CAPI Engine* resolve(char* arg);
}

namespace keys
{
	extern "C" CAPI Key* parse_stream(std::istream & stream, uint8_t(*converter)(char) = ascii_convert_from);
	extern "C" CAPI Key* parse_raw(const char* data, uint8_t(*converter)(char) = ascii_convert_from);
	extern "C" CAPI Key* parse_file(const char* filepath, uint8_t(*converter)(char) = ascii_convert_from);
}

namespace messages
{
	extern "C" CAPI Message* retrieve(const char* filepath, uint8_t(*converter)(char) = ascii_convert_from);
}