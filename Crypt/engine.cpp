#include "crypt/global.h"
#include "crypt/engine.h"

#include <sstream>
#include <fstream>

using namespace std;


Message::Message()
{
    _count = 0;
    _value = INVALID_VALUE;
    _content = nullptr;
    _encrypted = false;
    _strcontent = string();
}

Message::Message(const Message& source)
{
    _count = source._count;
    _encrypted = source._encrypted;
	_content = source._content;
}

Message::Message(const bigint& number, bool encrypted, unsigned int blocksz) : Message()
{
    _count = bop::decompose(number, _content, blocksz);
    _value = number;
	_encrypted = encrypted;
}

Message::Message(const char* msg, unsigned int blocksz, uint8_t (*converter)(char)) : Message()
{
    _value = bop::from_cptr(msg, converter);
    _count = bop::decompose(_value, _content, blocksz);
	_strcontent = string(msg);
}

Message::Message(string content, unsigned int blocksz, uint8_t (*converter)(char)) : Message()
{
    _value = bop::from_str(content, converter);
    _count = bop::decompose(_value, _content, blocksz);
    _strcontent = content;
}

Message::~Message()
{
    if(_content)
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

bigint Message::value()
{
    if(_value == INVALID_VALUE)
    {
        if(!_content || !_count)
            return INVALID_VALUE;

        return (_value = bop::recompose(_content, _count));
    }

    return _value;
}

bigint Message::part(unsigned int index) const
{
    if(index >= _count)
        throw invalid_argument("Message::part, index invalide");

    return _content[index];
}

string Message::get(char (*converter)(uint8_t))
{
    return _strcontent.empty() ? (_strcontent = bop::to_str(value(), converter)) : _strcontent;
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


Engine::~Engine() {}

bigint Engine::pad(const bigint& number, unsigned int padsize)
{
    bigint p;
    mpz_ui_pow_ui(p.get_mpz_t(), 2, padsize * 8);

    return number * p + _rand.rand(padsize);
}

bigint Engine::unpad(const bigint& number, unsigned int padsize)
{
    bigint num;
    mpz_ui_pow_ui(num.get_mpz_t(), 2, padsize * 8);
    mpz_fdiv_q(num.get_mpz_t(), number.get_mpz_t(), num.get_mpz_t());

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

bool Engine::operate(const string& arg, Message& message, Key*& key, unsigned int padsize)
{
    if (arg == "encrypt")
		encrypt(message, key, padsize);
    else if (arg == "decrypt")
		decrypt(message, key, padsize);
    else if(arg == "gkey")
       key = generate();
    else
        return false;

    return true;
}

Message* Engine::msgprep(const bigint &stack, unsigned int blocksz, unsigned int padsize)
{
    return new Message(stack, true, blocksz + padsize);
}

Message* Engine::msgprep(const string& stack_str, unsigned int blocksz, unsigned int padsize, uint8_t (*converter)(char))
{
    return msgprep(bop::from_str(stack_str, converter), blocksz, padsize);
}

Message* Engine::msgprep(const vector<bigint>& parts)
{
    Message* m = new Message;
    m->_encrypted = true;
    m->_count = parts.size();

    m->_content = new bigint[parts.size()];
    unsigned int idx = 0;
    for(bigint bi : parts)
        m->_content[idx++] = bi;

    return m;
}

Message* Engine::msgprep(const bigint *parts, unsigned int length)
{
    Message* m = new Message;
    m->_encrypted = true;
    m->_count = length;

    m->_content = new bigint[length];
    for(unsigned int i = 0;i < length;i++)
        m->_content[i] = parts[i];

    return m;
}
