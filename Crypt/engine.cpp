#include "pch.h"
#include "crypt/engine.h"

#include <sstream>
#include <fstream>

using namespace std;


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
	_content = bigint_from(msg, converter);
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

void Message::write(const char* filepath, char (*converter)(uint8_t))
{
	ofstream ofs;
	ofs.open(filepath, ios::out);
	if (ofs.fail())
		return;

	ofs << get();
	ofs.close();
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

bool Engine::operate(const char* arg, Message& message, Key* key, unsigned int padsize)
{
	if (!strcmp(arg, "encrypt"))
	{
		encrypt(message, key, padsize);
		return true;
	}
	else if (!strcmp(arg, "decrypt"))
	{
		decrypt(message, key, padsize);
		return true;
	}

	return false;
	//todo sign verify
}
