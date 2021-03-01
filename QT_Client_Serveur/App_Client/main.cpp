#include <QApplication>
#include "clienttcp.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ClientTcp fenetre;
    fenetre.show();
    return app.exec();
}
