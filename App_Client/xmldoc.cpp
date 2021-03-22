#include "xmldoc.h"
#include <iostream>


XmlDoc::XmlDoc() : QWidget () {

}

XmlDoc::~XmlDoc() {

}


//Méthode de chargement du fichier
void XmlDoc::chargerFichierConfig(QString nomFichier) {
    QFile xmlDoc(nomFichier);

    if(!xmlDoc.open(QIODevice::ReadOnly)) {
        //Si on arrive pas à l'ouvrir
        QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être ouvert");
        xmlDoc.close();
        return;
    }
    if (!doc.setContent(&xmlDoc)) { // Si l'on arrive pas à assoccier le fichier XML à l'objet DOM
        xmlDoc.close();
        QMessageBox::warning(this, "Erreur à l'ouverture du document XML", "Le document XML n'a pas pu être attribué à l'objet QDomDocument.");
        xmlDoc.close();
        return;
    }
    xmlDoc.close(); //On en a finis avec le document XML, on peut le fermer
}

//Méthode de chargement du pseudo contenu dans le fichier XML
QString XmlDoc::chargerPseudo(QString nomFichier) {
    chargerFichierConfig(nomFichier);

    docElement = doc.documentElement();
    noeud = docElement.firstChild();

    while(!noeud.isNull()) {
        element = noeud.toElement();
        if(!element.isNull()) {
            if(element.tagName() == "pseudo") {
                return element.text();
            }
            noeud = noeud.nextSibling();
        }
    }
    return "Pseudo par défaut";
}

//Méthode de sauvegarde du pseudo dans le fichier XML
void XmlDoc::sauvegarderPseudo(QString nomFichier, QString pseudo) {
    chargerFichierConfig(nomFichier);

    QDomElement newPseudo = doc.createElement(QString("Pseudo"));
    QDomText textPseudo = doc.createTextNode(QString(pseudo));
    newPseudo.appendChild(textPseudo);

    docElement = doc.documentElement();
    noeud = docElement.firstChild();

    while(!noeud.isNull()) {
        element = noeud.toElement();
        if (!element.isNull()) {
            if (element.tagName() == "pseudo") {
                docElement.replaceChild(newPseudo, noeud);
            }
            noeud = noeud.nextSibling();
        }
    }

    QFile xmlDoc("config.txt");
    if(xmlDoc.open(QFile::WriteOnly)) {
        xmlDoc.resize(0);
        QTextStream stream;
        stream.setDevice(&xmlDoc);
        doc.save(stream, 4);

        xmlDoc.close();
    }
}















