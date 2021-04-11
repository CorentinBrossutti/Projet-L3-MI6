#ifndef XMLDOC_H
#define XMLDOC_H

#include <QWidget>
#include <QtGui>
#include <QtXml>
#include <QTextStream>
#include <QMessageBox>

class XmlDoc : public QWidget
{
    Q_OBJECT

    public:
        XmlDoc();
        ~XmlDoc();
        QString chargerPseudo(QString nomFichier);
        void sauvegarderPseudo(QString nomFichier, QString pseudo);
        QString chargerCle(QString nomFichier);
        void sauvegarderCle(QString nomFichier, QString cle);

    private slots :
        void chargerFichierConfig(QString nomFichier);

    private :
        QDomDocument doc;
        QDomElement docElement;
        QDomElement element;
        QDomNode noeud;
};

#endif // XMLDOC_H
