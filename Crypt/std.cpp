#include "crypt/std.h"
#include "crypt/util.h"

using namespace std;


Engine* engines::resolve(char* arg)
{   
    if (!strcmp(arg, "rsa"))
		return new Rsa();
    else if(!strcmp(arg, "cesar"))
        return new Cesar();
	//AES ?
	else
		return nullptr;
}

bool engines::operate(Engine* engine, const string& arg, Message& message, Key*& key, unsigned int padsize)
{
    if (arg == "encrypt")
        engine->encrypt(message, key, padsize);
    else if (arg == "decrypt")
        engine->decrypt(message, key, padsize);
    else if(arg == "gkey")
       key = engine->generate();
    else
        return false;

    return true;
}


Key* keys::fparse(Engine* engine, const char* filepath, unsigned int base)
{
    string s = files::fread_str(filepath);

    return s.empty() ? nullptr : engine->parse_default_key(s, base);
}


Message* msgs::retrieve(const char* filepath, bool encrypted, unsigned int nbase)
{
    string s = files::fread_str(filepath);

    return s.empty() ? nullptr : (
                           encrypted ?
                               new Message(bigint(s, nbase), true) :
                               new Message(s)
                           );
}
