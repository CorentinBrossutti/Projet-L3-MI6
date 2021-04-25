#include "crypt/util.h"

#include <fstream>
#include <sstream>

using namespace std;

string files::fread_str(const char* filepath)
{
    ostringstream temp;
    ifstream reader;
    reader.open(filepath, ios::in);

    if (reader.fail())
        return "";

    temp << reader.rdbuf();
    reader.close();

    return temp.str();
}

bool files::fwrite_str(const char* filepath, const string& content)
{
    ofstream ofs;
    ofs.open(filepath, ios::out);
    if (ofs.fail())
        return false;

    ofs << content;
    ofs.close();

    return true;
}
