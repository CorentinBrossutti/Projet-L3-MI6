#include "crypt/global.h"
#include "crypt/engine.h"

#include <sstream>
#include <fstream>

using namespace std;


Message::Message() : Message(0)
{
}

Message::Message(const Message& source)
{
    _blocksz = source._blocksz;
    _count = source._count;
    _encrypted = source._encrypted;
	_content = source._content;
}

Message::Message(const bigint& number, bool encrypted, unsigned int blocksz)
{
    bop::decompose(number, _content, blocksz);
	_encrypted = encrypted;
}

Message::Message(const char* msg, unsigned int blocksz, uint8_t (*converter)(char))
{
    bop::decompose(bop::from(msg, converter), _content, blocksz);
	_strcontent = string(msg);
	_encrypted = false;
}

bool Message::encrypted() const
{
	return _encrypted;
}

unsigned int Message::count() const
{
    return _count;
}

bigint Message::value() const
{
    return bop::recompose(_content, _count);
}

string Message::get(char (*converter)(uint8_t))
{
    return _strcontent.empty() ? (_strcontent = bop::to(value(), converter)) : _strcontent;
}

void Message::write(const char* filepath, char (*converter)(uint8_t))
{
	ofstream ofs;
	ofs.open(filepath, ios::out);
	if (ofs.fail())
		return;

	ofs << get(converter);
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
    for(unsigned int i = 0;i < message.count();i++)
        encode(message._content[i], key, padsize);
	message._encrypted = true;
	message._strcontent = string();
}

void Engine::decrypt(Message& message, Key* key, unsigned int padsize)
{
    for(unsigned int i = 0;i < message.count();i++)
        decode(message._content[i], key, padsize);
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
    else if(!strcmp(arg, "gkey"))
    {
       //TODO
    }

	return false;
	//todo sign verify
}
