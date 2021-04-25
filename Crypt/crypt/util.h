#pragma once

#include "crypt/global.h"

namespace files
{
    MI6_CRYPT_API std::string fread_str(const char* filepath);
    MI6_CRYPT_API bool fwrite_str(const char* filepath, const std::string& content);
}
