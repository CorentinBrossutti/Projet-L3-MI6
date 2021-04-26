#pragma once

#include "global.h"
#include "math.h"
#include "key.h"
#include "random.h"

#include <ostream>

// Taille en octets du padding (du nonce)
#define PADSIZE_BYTES 1
// Taille des blocs (pour le découpage) en octets
#define BSIZE_BYTES 8
// Valeur de bigint indiquant qu'il est invalide
#define INVALID_VALUE -1


class Engine;

// Un message à transmettre, contient un bigint encrypté ou non correspondant au message
// Supporte le découpage
class MI6_CRYPT_API Message
{
	friend class Engine;
public:
	Message();
    // Constructeur de copie
    Message(const Message& source);
    // Construit un message depuis un bigint quelconque, utilie pour transmettre des données numériques
    Message(const bigint& content, bool encrypted = false, unsigned int blocksz = BSIZE_BYTES);
	// Construit un message depuis du texte, avec une fonction de conversion optionnelle (défaut ASCII)
    Message(const char* content, unsigned int blocksz = BSIZE_BYTES, uint8_t(*converter)(char) = ascii_convert_from);
    Message(std::string content, unsigned int blocksz = BSIZE_BYTES, uint8_t(*converter)(char) = ascii_convert_from);
    ~Message();

    // Le message est-il encrypté ?
	bool encrypted() const;
    // Nombre de parties du message
    unsigned int count() const;
    // Bigint unitaire représentatif des données
    bigint value();
    // Obtenir une partie découpée
    bigint part(unsigned int index) const;
	// Permet d'obtenir la représentation textuelle (si pertinent) du message, utilisant une fonction de conversion optionelle (défaut ASCII)
	// Noter que si le message n'est pas textuel, ou encrypté, cette représentation est inutile
	std::string get(char (*converter)(uint8_t) = ascii_convert_to);

    // Ecrit le contenu textuel du message dans un fichier
    void write_str(const char* filepath, char (*converter)(uint8_t) = ascii_convert_to);
    // Ecrit la valeur numérique dans la base spécifiée du message dans un fichier
    void write_num(const char* filepath, unsigned int base = 62);

    MI6_CRYPT_API friend std::ostream& operator <<(std::ostream& output, Message& msg);
protected:
    size_t _count;
	bool _encrypted;
    bigint* _content;
    bigint _value;
	std::string _strcontent;
};


// Un moteur de cryptage générique (classe abstraite parente)
class MI6_CRYPT_API Engine
{
public:
    virtual ~Engine();

	// Génère une clé de cryptage
    virtual Key* generate() const = 0;

    // Applique l'algorithme de cryptage avec une clé donnée et un nombre à encoder
    virtual bigint run_crypt(const bigint& source, Key* key) const = 0;
    // Applique l'algorithme de cryptage avec une clé donnée et un nombre à décoder
    virtual bigint run_decrypt(const bigint& source, Key* key) const = 0;

    // Ajoute un nonce au nombre donné (padsize est le nombre d'octets à ajouter)
    virtual bigint pad(const bigint& number, unsigned int padsize = PADSIZE_BYTES) const;
    // Retire le nonce du nombre donné (padsize est le nombre d'octets à retirer)
    virtual bigint unpad(const bigint& number, unsigned int padsize = PADSIZE_BYTES) const;

	// Encode un nombre avec une clé donnée
    virtual bigint encode(const bigint& source, Key* key, unsigned int padsize = PADSIZE_BYTES) const;
	// Décode un nombre avec une clé donnée
    virtual bigint decode(const bigint& source, Key* key, unsigned int padsize = PADSIZE_BYTES) const;

	// Encrypte un message avec une clé donnée
    // Le booléen parts définit si le chiffrement se fait sur les parties du message ou sur le message globalement
    void encrypt(Message& message, Key* key, bool parts = true, unsigned int blocksz = BSIZE_BYTES, unsigned int padsize = PADSIZE_BYTES) const;
	// Décrypte une message avec une clé donnée
    // Le booléen parts définit si le chiffrement se fait sur les parties du message ou sur le message globalement
    void decrypt(Message& message, Key* key, bool parts = true, unsigned int blocksz = BSIZE_BYTES, unsigned int padsize = PADSIZE_BYTES) const;

    // Construit un message reçu chiffré depuis un nombre
    virtual Message* msgprep(const bigint& stack, unsigned int blocksz = BSIZE_BYTES, unsigned int padsize = PADSIZE_BYTES) const;
    // Construit un message reçu chiffré depuis une représentation textuelle
    virtual Message* msgprep(const std::string& stack_str, unsigned int blocksz = BSIZE_BYTES, unsigned int padsize = PADSIZE_BYTES, uint8_t (*converter)(char) = ascii_convert_from) const;
    // Construit un message reçu chiffré depuis ses parties numériques (vector)
    virtual Message* msgprep(const std::vector<bigint>& parts) const;
    // Construit un message reçu chiffré depuis ses parties numériques (tableau)
    virtual Message* msgprep(const bigint* parts, unsigned int length) const;

    // Traite une chaîne de caractères et renvoie la clé par défaut pour ce moteur
    // Si le format n'est pas bon, erreur
    virtual Key* parse_default_key(const std::string& str, unsigned int base = STR_KEY_BASE) const;
protected:
    Randomizer _rand;
};
