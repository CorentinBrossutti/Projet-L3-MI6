#pragma once

#include "math.h"
#include "global.h"
#include "key.h"

#include <string>

#define PADSIZE 64


class Engine;

// Un message à transmettre, contient un bigint encrypté ou non correspondant au message
extern class CAPI Message
{
	friend class Engine;
public:
	Message();
	Message(const Message& source);
	Message(const bigint& content, bool encrypted = false);
	// Construit un message depuis du texte, avec une fonction de conversion optionnelle (défaut ASCII)
	Message(const char* content, uint8_t(*converter)(char) = ascii_convert_from);

	bool encrypted() const;
	// Permet d'obtenir la représentation textuelle (si pertinent) du message, utilisant une fonction de conversion optionelle (défaut ASCII)
	// Noter que si le message n'est pas textuel, ou encrypté, cette représentation est inutile
	std::string get(char (*converter)(uint8_t) = ascii_convert_to);

	void write(const char* filepath, char (*converter)(uint8_t) = ascii_convert_to);

	extern CAPI friend std::ostream& operator <<(std::ostream& output, Message& msg);
protected:
	bool _encrypted;
	bigint _content;
	std::string _strcontent;
};


// Un moteur de cryptage générique
extern class CAPI Engine
{
public:
	// Génère une clé de cryptage
	virtual Key* generate() = 0;

	// Applique l'algorithme de cryptage avec une clé donné et un nombre à encoder / décoder
	virtual bigint run(const bigint& source, Key* key) = 0;

	// Ajoute un nonce au nombre donné
	virtual bigint pad(const bigint& number, unsigned int padsize = PADSIZE);
	// Retire le nonce du nombre donné
	virtual bigint unpad(const bigint& number, unsigned int padsize = PADSIZE);

	// Encode un nombre avec une clé donnée
	virtual bigint encode(const bigint& source, Key* key, unsigned int padsize = PADSIZE);
	// Décode un nombre avec une clé donnée
	virtual bigint decode(const bigint& source, Key* key, unsigned int padsize = PADSIZE);

	// Encrypte un message avec une clé donnée
	void encrypt(Message& message, Key* key, unsigned int padsize = PADSIZE);
	// Décrypte une message avec une clé donnée
	void decrypt(Message& message, Key* key, unsigned int padsize = PADSIZE);

	// Opération dynamique basée sur un argument textuel
	bool operate(const char* arg, Message& message, Key* key, unsigned int padsize = PADSIZE);
};
