#pragma once

// Le fichier global.h contient des constantes globales
#include "mpirxx.h"

#include <string>

// Définit les constantes d'import/export DLL/SO (librairie)
#if defined(_MSC_VER)
//  Compilateur Windows
#define EXPORT __declspec(dllexport)
#define IMPORT __declspec(dllimport)
#define WIN
#elif defined(__GNUC__)
//  GCC
#define EXPORT __attribute__((visibility("default")))
#define IMPORT
#define UNIX
#else
//  Inconnu
#define EXPORT
#define IMPORT
#pragma warning Compilateur inconnu ?
#endif

// Définit si l'API est en mode export/import, permet d'optimiser dans certains cas
// CRYPT_LIBRARY est une variable globale à définir lors de la compilation
#ifdef CRYPT_LIBRARY
#define MI6_CRYPT_API EXPORT
#else
#define MI6_CRYPT_API IMPORT
#endif

using bigint = mpz_class;


MI6_CRYPT_API char ascii_convert_to(uint8_t val);
MI6_CRYPT_API uint8_t ascii_convert_from(char val);
