#include "clienttcp.h"
#include "serveurtcp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ServeurTCP fenetre;
    ClientTCP w;

    fenetre.show();
    w.show();
    return app.exec();
}
