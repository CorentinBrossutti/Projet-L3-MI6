#include "crypt/std.h"
#include "crypt/random.h"
#include "crypt/engine.h"

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;


int main(int argc, char** argv)
{
    Randomizer r;
    cout << r.rand(1) << endl;
    cout << r.rand(5) << endl;

    /*Engine* temp = new Rsa;
    Key* k = temp->generate();

    Message m("tg");
    cout << m.value() << endl;
    temp->encrypt(m, k);
    cout << m.value() << endl;
    temp->decrypt(m, k);
    cout << m.value() << endl;

    delete temp;
    delete k;*/

    int ret = EXIT_FAILURE;
    Engine* engine = nullptr;
    Key* key = nullptr;
    Message* msg = nullptr;

    if (argc < 6)
    {
        cout << "Usage : <SDPE> <moteur> <operation> <fichier_cle> <fichier_message_source> <fichier_message_cible>" << endl;
        cout << "Exemples de moteurs : rsa, aes" << endl;
        cout << "Exemples d'opération : encrypt, decrypt, sign, verify" << endl;
        ret = EXIT_SUCCESS;
    }
    else if (!(engine = engines::resolve(argv[1])))
        cout << "Moteur de cryptage \"" << argv[1] << "\" non reconnu." << endl;
    else if (!(key = keys::parse_file(argv[3])))
        cout << "La clé ne peut être lue." << endl;
    else if (!(msg = msgs::retrieve(argv[4])))
        cout << "Aucun message n'a pu être extrait du fichier donné (ou le message est vide)." << endl;
    else if (engine->operate(argv[2], *msg, key))
    {
        msg->write(argv[5]);
        cout << "Message traité et écrit dans le fichier cible." << endl;
        ret = EXIT_SUCCESS;
    }
    else
        cout << "Impossible d'effectuer l'opération donnée. Vérifiez que l'opération existe et est valide." << endl;

    if (engine)
        delete engine;
    if (key)
        delete key;
    if (msg)
        delete msg;
    return ret;
}
