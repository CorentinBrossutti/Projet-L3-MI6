#include "crypt/std.h"

#include <sstream>
#include <string>
#include <fstream>

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


Key* keys::parse_stream(istream& stream, uint8_t(*converter)(char))
{
	string engine, info, buf;

	if (!getline(stream, engine))
		throw invalid_argument("Invalid data passed at keys::parse_raw ; engine specifier couldn't be read");
	if (!getline(stream, info))
		throw invalid_argument("Invalid data passed at keys::parse_raw ; informations couldn't be read");
	if (!getline(stream, buf))
		throw invalid_argument("Invalid data passed at keys::parse_raw ; key data couldn't be read");

	if (engine == "RSA")
	{
		bigint n = bop::from(buf.c_str(), converter);
		if (!getline(stream, buf))
			throw invalid_argument("Invalid data passed at keys::parse_raw ; key data couldn't be read");
		// E ou D en fonction de ce qu'on traite. Dans le cas d'une paire il s'agit de e
		bigint ed = bop::from(buf.c_str(), converter);
		if (info == "PUBLIC KEY")
			return new PublicKey(n, ed);
		else if (info == "PRIVATE KEY")
			return new PrivateKey(n, ed);
		else if (info == "KEY PAIR")
		{
			if (!getline(stream, buf))
				throw invalid_argument("Invalid data passed at keys::parse_raw ; key data couldn't be read");
			bigint d = bop::from(buf.c_str(), converter);
			return new RsaKey(n, ed, d);
		}
		else
			throw invalid_argument("keys::parse_raw : informations present but couldn't be resolved for data");
	}
	// AES ?
	else
		throw invalid_argument("keys::parse_raw : engine specifier present but couldn't be resolved");
}

Key* keys::parse_raw(const char* data, uint8_t(*converter)(char))
{
	stringstream ss(data);

	return parse_stream(ss, converter);
}

Key* keys::parse_file(const char* filepath, uint8_t(*converter)(char))
{
	ifstream ifs;
	ifs.open(filepath, ios::in);
	if(ifs.fail())
		throw invalid_argument("keys::parse_file ; file couldn't be opened");
		

	Key* ret = parse_stream(ifs, converter);
	ifs.close();

	return ret;
}


Message* msgs::retrieve(const char* filepath, uint8_t(*converter)(char))
{
	ostringstream temp;
	ifstream reader;
	reader.open(filepath, ios::in);

	if (reader.fail())
		throw invalid_argument("messages::retrieve ; file could not be opened");

	temp << reader.rdbuf();
	reader.close();

    return temp.str().empty() ? nullptr : new Message(temp.str().c_str(), BSIZE_BYTES, converter);
}
