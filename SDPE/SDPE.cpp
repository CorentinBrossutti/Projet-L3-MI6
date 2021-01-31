#include "crypt/engine.h"
#include "crypt/rsa.h"

#include <iostream>

int main(int argc, char** argv)
{
    Message m(16706);
    Message m1("Salut mon ami, je t'invite a te promener avec moi dans l'espace grace a ma fusee radioactive !");

    std::cout << m1 << std::endl;

    return EXIT_SUCCESS;
}