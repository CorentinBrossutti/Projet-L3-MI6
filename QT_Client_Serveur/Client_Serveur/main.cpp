#include "serveurtcp.h"

#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);

    ServeurTCP fenetre;

    fenetre.show();
    return app.exec();
}
