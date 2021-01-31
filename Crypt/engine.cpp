#include "pch.h"
#include "crypt/engine.h"

#include <sstream>

using namespace std;


char ascii_convert_to(uint8_t val)
{
	return char(val);
}

uint8_t ascii_convert_from(char val)
{
	return int(val);
}


Message::Message() : Message(0)
{
}

Message::Message(const Message& source)
{
	_content = source._content;
}

Message::Message(const bigint& number, bool encrypted)
{
	_content = number;
	_encrypted = encrypted;
}

Message::Message(const char* msg, uint8_t (*converter)(char))
{
	stringstream sstream;
	// On transforme le message en entier, pour ça on itère sur les caractères...
	for (unsigned int i = 0; msg[i] != '\0'; i++)
		sstream << bitset<8>(converter(msg[i])).to_string();
	
	_content = bigint(sstream.str(), 2);
	_strcontent = string(msg);
	_encrypted = false;
}

bool Message::encrypted() const
{
	return _encrypted;
}

string Message::get(char (*converter)(uint8_t))
{
	if (!_strcontent.empty())
		return _strcontent;

	stringstream sstream;

	byteset bytes(_content);
	for (unsigned int i = 0; i < bytes.size(); i++)
		sstream << converter(bytes[i].to_ulong());

	return (_strcontent = sstream.str());
}

std::ostream& operator <<(std::ostream& output, Message& msg)
{
	output << msg.get();

	return output;
}


bigint Engine::pad(const bigint& number, unsigned int padsize)
{
	// TODO
	return bigint();
}

bigint Engine::unpad(const bigint& number, unsigned int padsize)
{
	return number >> padsize;
}

bigint Engine::encode(const bigint& source, Key* key, unsigned int padsize)
{
	return run(pad(source, padsize), key);
}

bigint Engine::decode(const bigint& source, Key* key, unsigned int padsize)
{
	return unpad(run(source, key), padsize);
}

void Engine::encrypt(Message& message, Key* key, unsigned int padsize)
{
	encode(message._content, key, padsize);
	message._encrypted = true;
	message._strcontent = string();
}

void Engine::decrypt(Message& message, Key* key, unsigned int padsize)
{
	decode(message._content, key, padsize);
	message._encrypted = false;
	message._strcontent = string();
}
