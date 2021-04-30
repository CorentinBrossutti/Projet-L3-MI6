#include <QApplication>
#include "clienttcp.h"
#include "xmldoc.h"
#include "fenetreConnexion.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    fenetreConnexion fenetre;
    fenetre.show();

    return app.exec();
}
