#include "crypt/global.h"
#include "crypt/engine.h"

#include <sstream>
#include <fstream>

using namespace std;


Message::Message() : Message(INVALID_VALUE)
{
}

Message::Message(const Message& source)
{
    _count = source._count;
    _encrypted = source._encrypted;
	_content = source._content;
}

Message::Message(const bigint& number, bool encrypted, unsigned int blocksz)
{
    _count = bop::decompose(number, _content, blocksz);
    _value = number;
	_encrypted = encrypted;
}

Message::Message(const char* msg, unsigned int blocksz, uint8_t (*converter)(char))
{
    _value = bop::from(msg, converter);
    _count = bop::decompose(_value, _content, blocksz);
	_strcontent = string(msg);
	_encrypted = false;
}

Message::Message(string content, unsigned int blocksz, uint8_t (*converter)(char))
{
    _value = bop::from(content.c_str(), converter);
    _count = bop::decompose(_value, _content, blocksz);
    _strcontent = content;
    _encrypted = false;
}

Message::~Message()
{
    delete[] _content;
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
    return _value == INVALID_VALUE ? bop::recompose(_content, _count) : _value;
}

bigint Message::part(unsigned int index) const
{
    if(index >= _count)
        throw invalid_argument("Message::part, index invalide");
    return _content[index];
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
    bigint p;
    mpz_ui_pow_ui(p.get_mpz_t(), 2, padsize * 8);

    return number * p + _rand.rand(padsize);
    //return number;
}

bigint Engine::unpad(const bigint& number, unsigned int padsize)
{
    bigint p;
    bigint num;
    mpz_ui_pow_ui(p.get_mpz_t(), 2, padsize * 8);
    mpz_fdiv_q(num.get_mpz_t(), number.get_mpz_t(), p.get_mpz_t());

    //return number;
    return num;
}

bigint Engine::encode(const bigint& source, Key* key, unsigned int padsize)
{
    return run_crypt(pad(source, padsize), key);
}

bigint Engine::decode(const bigint& source, Key* key, unsigned int padsize)
{
    return unpad(run_decrypt(source, key), padsize);
}

void Engine::encrypt(Message& message, Key* key, bool parts, unsigned int blocksz, unsigned int padsize)
{
    if(parts)
    {
        for(unsigned int i = 0;i < message.count();i++)
            message._content[i] = encode(message._content[i], key, padsize);
        message._value = INVALID_VALUE;
    }
    else
    {
        message._value = encode(message._value, key, padsize);
        delete[] message._content;
        message._count = bop::decompose(message._value, message._content, blocksz);
    }
    message._encrypted = true;
	message._strcontent = string();
}

void Engine::decrypt(Message& message, Key* key, bool parts, unsigned int blocksz, unsigned int padsize)
{
    if(parts)
    {
        for(unsigned int i = 0;i < message.count();i++)
            message._content[i] = decode(message._content[i], key, padsize);
        message._value = INVALID_VALUE;
    }
    else
    {
        message._value = decode(message._value, key, padsize);
        delete[] message._content;
        message._count = bop::decompose(message._value, message._content, blocksz);
    }
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

Message Engine::msgprep(const bigint &stack, unsigned int blocksz, unsigned int padsize)
{
    return Message(stack, true, blocksz + padsize);
}

Message Engine::msgprep(const string& stack_str, unsigned int blocksz, unsigned int padsize, uint8_t (*converter)(char))
{
    return msgprep(bop::from(stack_str.c_str(), converter), blocksz, padsize);
}

Message Engine::msgprep(const vector<bigint>& parts)
{
    Message m;
    m._encrypted = true;
    m._count = parts.size();

    m._content = new bigint[parts.size()];
    unsigned int idx = 0;
    for(bigint bi : parts)
        m._content[idx++] = bi;

    return m;
}
