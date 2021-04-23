#include "crypt/random.h"

#include <time.h>
#include <sstream>

using namespace std;


int RandOther::randb(uint8_t*& buf, const size_t& blen) const
{
    if(!buf)
        buf = new uint8_t[blen];

    for(unsigned int i = 0; i < blen; i++)
        buf[i] = rand() % 256;

    return GEN_SUCCESS;
}

#if defined (WIN)
int RandWin::randb(uint8_t*& buf, const size_t& blen) const
{
    random_device rd;
    mt19937_64 gen(rd());
    uniform_int_distribution<> dist(0, 255);

    if(!buf)
        buf = new uint8_t[blen];

    for(unsigned int i = 0;i < blen;i++)
        buf[i] = dist(gen);

    return GEN_SUCCESS;
}
#elif defined (UNIX)
int RandUnix::randb(uint8_t*& buf, const size_t& blen) const
{
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd < 0)
        return GEN_ERR_UNKNOWN;
    int rd_len = 0;
    if(!buf)
        buf = new uint8_t[blen];

    while(rd_len < blen) {
        int n = read(fd, buf, blen);
        if (n < 0){
            stringstream ss;
            ss << "RandUnix::rand(): erreur (n=" << n << ") " << "(rd_len=" << rd_len << ")";
            return GEN_ERR_ENTROPY;
        }
        rd_len += n;
    }

    close(fd);
    return GEN_SUCCESS;
}
#endif


Randomizer::Randomizer()
{
#if defined (WIN)
    _impl = new RandWin;
#elif defined (UNIX)
    _impl = new RandUnix;
#else
    if(!init_rand_other){
        init_rand_other = true;
        srand(time(NULL));
    }
    _impl = new RandOther;
#endif
}

Randomizer::~Randomizer()
{
    if(_impl)
        delete _impl;
}

bigint Randomizer::rand(unsigned int bytes) const
{
    if(bytes == 0)
        return 0;

    uint8_t* buf = nullptr;
    bigint out = _impl->randb(buf, bytes);

    if(out == GEN_SUCCESS)
    {
        for(unsigned int i = 0;i < bytes;i++)
            out = (out * 256) + buf[i];
    }
    else
        out *= -1;

    if(buf)
        delete buf;

    return out;
}
