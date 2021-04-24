#include "crypt/global.h"


char ascii_convert_to(uint8_t val)
{
	return char(val);
}

uint8_t ascii_convert_from(char val)
{
	return int(val);
}
