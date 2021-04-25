#include "crypt/std.h"
#include "crypt/random.h"
#include "crypt/engine.h"

#include <iostream>
#include <cstdio>
#include <string>

using namespace std;


void help()
{
    cout << "[SDPE] <moteur> <operation> <fichier_cle> (fichier_message_source) (fichier_message_cible)" << endl;
    cout << "Exemples de moteurs : rsa, aes" << endl;
    cout << "Exemples d'operation : gen, encrypt, decrypt" << endl;
}

int process(int argc, char** argv, Engine*& engine, Key*& key, Message*& msg)
{
    if(argc < 2)
    {
        cout << "Moteur de cryptage manquant. Syntaxe :" << endl;
        help();
        return EXIT_FAILURE;
    }
    else if(argc < 3)
    {
        cout << "Libelle d'operation manquant. Syntaxe :" << endl;
        help();
        return EXIT_FAILURE;
    }
    else
    {
        if(!(engine = engines::resolve(argv[1])))
        {
            cout << "Moteur de cryptage " << argv[1] << " impossible a resoudre." << endl;
            return EXIT_FAILURE;
        }
        else if(!strcmp(argv[2], "gen"))
        {
            if(argc < 4)
            {
                cout << "Fichier destination pour la generation non specifie. Syntaxe :" << endl;
                help();
                return EXIT_FAILURE;
            }
            (key = engine->generate())->save(argv[3]);
            cout << "Cle generee et sauvegardee dans le fichier specifie." << endl;
            return EXIT_SUCCESS;
        }
        else if(!strcmp(argv[2], "encrypt") || !strcmp(argv[2], "decrypt"))
        {
            switch(argc)
            {
            case 3:
                cout << "Fichier de cle manquant. Peut-etre devez en generer une ?" << endl;
                return EXIT_FAILURE;
            case 4:
                cout << "Fichier message source manquant." << endl;
                return EXIT_FAILURE;
            case 5:
                cout << "Fichier destination manquant." << endl;
                return EXIT_FAILURE;
            }

            if(!(key = keys::fparse(engine, argv[3])))
            {
                cout << "Impossible d'obtenir une cle depuis le fichier specifie." << endl;
                return EXIT_FAILURE;
            }
            else if(!(msg = msgs::retrieve(argv[4], strcmp(argv[2], "encrypt"))))
            {
                cout << "Impossible d'obtenir un message coherent depuis le fichier source specifie." << endl;
                return EXIT_FAILURE;
            }

            if(!strcmp(argv[2], "encrypt")){
                engine->encrypt(*msg, key, false);
                msg->write_num(argv[5]);
            }
            else{
                engine->decrypt(*msg, key, false);
                msg->write_str(argv[5]);
            }

            cout << "Message traite avec succes." << endl;
            return EXIT_SUCCESS;
        }
        else
        {
            cout << "Operation \"" << argv[2] << "\" non reconnue." << endl;
            cout << "Operations disponibles : gen, encrypt, decrypt" << endl;
            return EXIT_FAILURE;
        }
    }

    return EXIT_FAILURE;
}

int main(int argc, char** argv)
{
    int ret = EXIT_FAILURE;
    Engine* engine = nullptr;
    Key* key = nullptr;
    Message* msg = nullptr;

    ret = process(argc, argv, engine, key, msg);

    if (engine)
        delete engine;
    if (key)
        delete key;
    if (msg)
        delete msg;
    return ret;
}
