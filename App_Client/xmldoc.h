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
        QString chargerIp(QString nomFichier);
        QString chargerPort(QString nomFichier);
        void sauvegarderPseudo(QString nomFichier, QString pseudo);
        void sauvegarderIp(QString nomFichier, QString ip);
        void sauvegarderPort(QString nomFichier, QString port);
        QString chargerCle(QString nomFichier);
        void sauvegarderCle(QString nomFichier, QString cle);

    private slots :
        void chargerFichierConfig(QString nomFichier);
        void creerFichier(QString nomFichier);

    private :
        QDomDocument doc;
        QDomElement docElement;
        QDomElement element;
        QDomNode noeud;
};

#endif // XMLDOC_H
