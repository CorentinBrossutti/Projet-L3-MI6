NOM du projet : MI6 Projet
NOM du groupe : MI6
Membres-contributeurs : BROSSUTTI Corentin - FORESTIER Ryan - DEMEERSSEMAN Daniel - FORISSIER Benjamin
Description du projet : Ce projet est une mise en application du cryptage RSA par l'intermédiaire d'un chat en réseau par système client/serveur.

--------------------------------------------------------------------------------------------------------------------------------------------------------------------------

Prérequis à la compilation : Si le paquet "qt5-default" n'est pas installé sur votre machine, taper la commande suivante pour l'installer : "sudo apt install qt5-default"


Compilation sous Linux :
    - Ouvrir un terminal de commande
    - Se placer dans le répertoire contenant le makefile
    - taper la commande "make" dans le terminal


Execution sous Linux :
    - Ouvrir un terminal de commande
    - Se rendre dans le dossier "deploy" ou taper la commande : "cd deploy", si vous êtes dans le répertoire contenant le makefile
    - taper la commande : ./MI6.[NOM], en remplaçant [NOM] par le nom de l'executable que vous voulez lancer (taper la commande ls dans le répertoire pour voir le nom des exécutables)


Recommandation -- Si vous voulez utiliser le chat, vous devez :
    - lancer l'executable MI6.ChatClient mais aussi l'executable MI6.ChatServer pour que le serveur puisse retransmettre les messsages.
    - Sur l'application MI6.ChatClient, dans le champ "IP", taper soit 'localhost' si le serveur est lancé sur votre machine, soit l'IP de la machine qui fait touner le serveur.
    - Sur l'application MI6.ChatClient, dans le champ "port", taper 50885. Le serveur se lancera toujours sur ce port.
