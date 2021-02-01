#pragma once

#include "math.h"
#include "global.h"
#include "key.h"

#include <string>

#define PADSIZE 64


class Engine;

// Un message � transmettre, contient un bigint encrypt� ou non correspondant au message
extern class CAPI Message
{
	friend class Engine;
public:
	Message();
	Message(const Message& source);
	Message(const bigint& content, bool encrypted = false);
	// Construit un message depuis du texte, avec une fonction de conversion optionnelle (d�faut ASCII)
	Message(const char* content, uint8_t(*converter)(char) = ascii_convert_from);

	bool encrypted() const;
	// Permet d'obtenir la repr�sentation textuelle (si pertinent) du message, utilisant une fonction de conversion optionelle (d�faut ASCII)
	// Noter que si le message n'est pas textuel, ou encrypt�, cette repr�sentation est inutile
	std::string get(char (*converter)(uint8_t) = ascii_convert_to);

	void write(const char* filepath, char (*converter)(uint8_t) = ascii_convert_to);

	extern CAPI friend std::ostream& operator <<(std::ostream& output, Message& msg);
protected:
	bool _encrypted;
	bigint _content;
	std::string _strcontent;
};


// Un moteur de cryptage g�n�rique
extern class CAPI Engine
{
public:
	// G�n�re une cl� de cryptage
	virtual Key* generate() = 0;

	// Applique l'algorithme de cryptage avec une cl� donn� et un nombre � encoder / d�coder
	virtual bigint run(const bigint& source, Key* key) = 0;

	// Ajoute un nonce au nombre donn�
	virtual bigint pad(const bigint& number, unsigned int padsize = PADSIZE);
	// Retire le nonce du nombre donn�
	virtual bigint unpad(const bigint& number, unsigned int padsize = PADSIZE);

	// Encode un nombre avec une cl� donn�e
	virtual bigint encode(const bigint& source, Key* key, unsigned int padsize = PADSIZE);
	// D�code un nombre avec une cl� donn�e
	virtual bigint decode(const bigint& source, Key* key, unsigned int padsize = PADSIZE);

	// Encrypte un message avec une cl� donn�e
	void encrypt(Message& message, Key* key, unsigned int padsize = PADSIZE);
	// D�crypte une message avec une cl� donn�e
	void decrypt(Message& message, Key* key, unsigned int padsize = PADSIZE);

	// Op�ration dynamique bas�e sur un argument textuel
	bool operate(const char* arg, Message& message, Key* key, unsigned int padsize = PADSIZE);
};
