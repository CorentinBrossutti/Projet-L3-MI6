#include "crypt/random.h"

#include <time.h>
#include <sstream>

using namespace std;


RandImpl::~RandImpl() {}


int RandPseudo::randb(uint8_t*& buf, const size_t& blen) const
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
    // Initialisation (si nécessaire) du pseudo-aléatoire
    Randomizer::pseudo();
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
        // On concatène les octets pour obtenir le nombre de la taille désirée
        for(unsigned int i = 0;i < bytes;i++)
            out = (out * 256) + buf[i];
    }
    else
        out *= -1;

    if(buf)
        delete buf;

    return out;
}

bigint Randomizer::rand() const
{
    if(dynamic_cast<RandPseudo*>(_impl))
        return std::rand();

    // Complètement arbitraire, on fait juste des multiplications statiques sur un octet aléatoire
    bigint b = rand(1);
    mpz_pow_ui(b.get_mpz_t(), rand(1).get_mpz_t(), 4);

    return 10 * b + 32767;
}

bigint Randomizer::rand(unsigned int digits, unsigned int base) const
{
    // Found est le modulo supérieur pour obtenir la partie désirée du nombre aléatoire
    bigint found;
    mpz_ui_pow_ui(found.get_mpz_t(), base, digits);

    // On obtient le nombre minimal d'octets que prendrait un nombre avec le nombre de chiffres désiré
    bigint temp = bop::getsize(bigint(found - 1), 2);
    mpz_cdiv_q_ui(temp.get_mpz_t(), temp.get_mpz_t(), 8);
    // On obtient un nombre aléatoire de cette taille
    temp = rand(temp.get_ui());

    // Puis on lui applique le modulo supérieur pour obtenir la partie intéréssante
    // Par exemple, si l'on veut quatre chiffres, le modulo supérieur est 10000 et ainsi lorsque la génération produit par exemple 65321, le modulo renvoie 5321
    bigint out = temp % found;
    // On s'assure que le nombre soit de la bonne taille (cas d'un nombre tel que 30077
    size_t sz = bop::getsize(out, base, true);
    // Sinon on le multiplie par la base puissance le nombre de chiffres manquants
    if(sz < digits){
        mpz_ui_pow_ui(found.get_mpz_t(), base, digits - sz);
        out *= found;
    }

    return out;
}

bool Randomizer::__psinit = false;
Randomizer& Randomizer::pseudo()
{
    static Randomizer pseudo;
    if(!__psinit)
    {
        delete pseudo._impl;
        srand(time(NULL));
        pseudo._impl = new RandPseudo;
        __psinit = true;
    }

    return pseudo;
}


bigint random_prime(const Randomizer& rand, unsigned int bytes)
{
    bigint num;
    bigint x;
    do
    {
        num = rand.rand(bytes);
        // On retire le dernier chiffre en base 10
        num -= num % 10;

        // On ajoute un chiffre aléatoire qui soit impair et ne soit pas un multiple de 5 pour augmenter la probabilité qu'il soit premier
        do
        {
            x = rand.rand(1, 10);
        } while (x % 2 == 0 || x == 5);

        num += x;

    } while (!isprime(num, Randomizer::pseudo().rand()));

    return num;
}
