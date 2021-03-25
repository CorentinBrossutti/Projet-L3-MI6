#include <QApplication>
#include "clienttcp.h"
#include "xmldoc.h"
#include "fenetreConnexion.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
   // ClientTcp fenetre;
    //fenetre.show();
    fenetreConnexion fenetre;
    fenetre.setWindowTitle("Voici la fenêtre de connexion !");
    fenetre.show();
    //Doc->show();

    return app.exec();
}
