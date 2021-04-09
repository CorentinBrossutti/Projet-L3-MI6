#pragma once

#include "math.h"
#include "global.h"
#include "key.h"

#include <string>

#define PADSIZE_BYTES 1
#define BSIZE_BYTES 8
#define INVALID_VALUE -1


class Engine;

// Un message à transmettre, contient un bigint encrypté ou non correspondant au message
class CAPI Message
{
	friend class Engine;
public:
	Message();
    Message(const Message& source);
    Message(const bigint& content, bool encrypted = false, unsigned int blocksz = BSIZE_BYTES);
	// Construit un message depuis du texte, avec une fonction de conversion optionnelle (défaut ASCII)
    Message(const char* content, unsigned int blocksz = BSIZE_BYTES, uint8_t(*converter)(char) = ascii_convert_from);
    Message(std::string content, unsigned int blocksz = BSIZE_BYTES, uint8_t(*converter)(char) = ascii_convert_from);
    ~Message();

	bool encrypted() const;
    unsigned int count() const;
    //Bigint unitaire représentatif des données
    bigint value() const;
    //Obtenir une partie découpée
    bigint part(unsigned int index) const;
	// Permet d'obtenir la représentation textuelle (si pertinent) du message, utilisant une fonction de conversion optionelle (défaut ASCII)
	// Noter que si le message n'est pas textuel, ou encrypté, cette représentation est inutile
	std::string get(char (*converter)(uint8_t) = ascii_convert_to);

	void write(const char* filepath, char (*converter)(uint8_t) = ascii_convert_to);

	CAPI friend std::ostream& operator <<(std::ostream& output, Message& msg);
protected:
    unsigned int _count;
	bool _encrypted;
    bigint* _content;
    bigint _value;
	std::string _strcontent;
};


// Un moteur de cryptage générique
class CAPI Engine
{
public:
	// Génère une clé de cryptage
	virtual Key* generate() = 0;

    // Applique l'algorithme de cryptage avec une clé donnée et un nombre à encoder
    virtual bigint run_crypt(const bigint& source, Key* key) = 0;
    // Applique l'algorithme de cryptage avec une clé donnée et un nombre à décoder
    virtual bigint run_decrypt(const bigint& source, Key* key) = 0;

	// Ajoute un nonce au nombre donné
    virtual bigint pad(const bigint& number, unsigned int padsize = PADSIZE_BYTES);
	// Retire le nonce du nombre donné
    virtual bigint unpad(const bigint& number, unsigned int padsize = PADSIZE_BYTES);

	// Encode un nombre avec une clé donnée
    virtual bigint encode(const bigint& source, Key* key, unsigned int padsize = PADSIZE_BYTES);
	// Décode un nombre avec une clé donnée
    virtual bigint decode(const bigint& source, Key* key, unsigned int padsize = PADSIZE_BYTES);

	// Encrypte un message avec une clé donnée
    void encrypt(Message& message, Key* key, bool parts = false, unsigned int blocksz = BSIZE_BYTES, unsigned int padsize = PADSIZE_BYTES);
	// Décrypte une message avec une clé donnée
    void decrypt(Message& message, Key* key, bool parts = false, unsigned int blocksz = BSIZE_BYTES, unsigned int padsize = PADSIZE_BYTES);

	// Opération dynamique basée sur un argument textuel
    bool operate(const char* arg, Message& message, Key* key, unsigned int padsize = PADSIZE_BYTES);

    virtual Message msgprep(const bigint& stack, unsigned int blocksz = BSIZE_BYTES, unsigned int padsize = PADSIZE_BYTES);
    virtual Message msgprep(const std::string& stack_str, unsigned int blocksz = BSIZE_BYTES, unsigned int padsize = PADSIZE_BYTES, uint8_t (*converter)(char) = ascii_convert_from);
    virtual Message msgprep(const std::vector<bigint>& parts);
};
