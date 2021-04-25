#pragma once

#include "global.h"

#include <math.h>
#include <bitset>
#include <vector>


// BIGINT operations
namespace bop
{
    // Retourne le nombre d'octets d'un big int, arrondi supérieurement
    MI6_CRYPT_API size_t count_bytes(const bigint& number, bool exact = false);
    // Retourne la taille dans une base donnée d'un nombre, soit son nombre de chiffres dans cette base
    // Le booléen exact permet de choisir si l'on souhaite une taille exacte (moins performant) ou inexacte (soit exacte soit trop grande de 1, plus performant)
    MI6_CRYPT_API size_t getsize(const bigint& val, unsigned int base, bool exact = false);

    // Renvoie un nombre depuis sa représentation littérale
    MI6_CRYPT_API bigint from_cptr(const char* val, uint8_t(*converter)(char) = ascii_convert_from);
    MI6_CRYPT_API bigint from_str(const std::string& str, uint8_t(*converter)(char) = ascii_convert_from);
    // Renvoie la représentation littérale d'un entier
    MI6_CRYPT_API std::string to_str(const bigint& val, char(*converter)(uint8_t) = ascii_convert_to);

    // Décompose un nombre en parties de taille = blocksz, la première partie étant forcément la plus petite
    // Le booléen inverted permet de décider si oui ou non l'ordre des blocs doit être inversé
    MI6_CRYPT_API std::vector<bigint> decompose_vec(const bigint& val, unsigned int blocksz, bool inverted = false);
    // Décompose un nombre en parties de taille = blocksz, la première partie étant forcément la plus petite
    // Le résultat est adjoint dans le pointeur recp qui devient un tableau alloué. La méthode renvoie le nombre de parties.
    size_t decompose(const bigint& val, bigint*& recp, unsigned int blocksz);
    // Recompose un nombre depuis ses parties sous forme de std::vector
    bigint recompose_vec(const std::vector<bigint>& from);
    // Recompose un nombre depuis ses parties stockées dans un tableau-pointeur
    bigint recompose(const bigint* from, unsigned int count);
}


// Renvoie vrai si num est premier
// RN est un nombre aléatoire à usage unique pour effectuer l'opération probabiliste
bool isprime(const bigint& num, const bigint& rn);
// Renvoie l'euclide de a et b
bigint euclide(const bigint& a, const bigint& b);
// Renvoie l'exponentiation modulaire
bigint modpow(const bigint& base, const bigint& e, const bigint& num);
// Renvoie le code exposant de num
bigint expcode(const bigint& num);
