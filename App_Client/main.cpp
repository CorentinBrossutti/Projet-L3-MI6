#include <QApplication>
#include "clienttcp.h"
#include "xmldoc.h"

int main(int argc, char *argv[])
{
    QApplication app(argc, argv);
    ClientTcp fenetre;
    //XmlDoc *Doc = new XmlDoc();
    fenetre.show();
    //Doc->show();

    return app.exec();
}
