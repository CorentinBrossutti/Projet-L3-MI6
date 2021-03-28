#include <QApplication>
#include "clienttcp.h"
#include "xmldoc.h"
#include "fenetreConnexion.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    //ClientTcp fenetre;
    //XmlDoc *Doc = new XmlDoc();
    //fenetre.show();
    //Doc->show();
    fenetreConnexion fenetre;
    fenetre.setWindowTitle("Voici la fenêtre de connexion !");
    fenetre.show();
    return app.exec();
}
