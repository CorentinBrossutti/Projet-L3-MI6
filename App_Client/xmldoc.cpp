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
            if(element.tagName() == "pseudo" && (element.text()!="")) { //On trouve le noeud contenant le pseudo
                return element.text(); //On retourne son contenu
            }
            noeud = noeud.nextSibling();
        }
    }
    return ("Pseudo par défaut"); //Si il n'y a pas de Pseudo on retourne un pseudo par défaut
}

//Méthode de sauvegarde du pseudo dans le fichier XML
void XmlDoc::sauvegarderPseudo(QString nomFichier, QString pseudo) {
    chargerFichierConfig(nomFichier);

    QDomElement newPseudo = doc.createElement(QString("Pseudo")); //On crée notre nouveau Noeud
    QDomText textPseudo = doc.createTextNode(QString(pseudo)); //On y met le pseudo voulu
    newPseudo.appendChild(textPseudo);

    docElement = doc.documentElement(); //On récupère le document chargé
    noeud = docElement.firstChild();

    while(!noeud.isNull()) { //On parcourt notre Noeud
        element = noeud.toElement();
        if (!element.isNull()) {
            if (element.tagName() == "pseudo") { //Si on trouve notre noeud qui contient le pseudo
                docElement.replaceChild(newPseudo, noeud); //Alors on le remplace par le nouveau Noeud qui continent notre nouveau Pseudo
            }
            noeud = noeud.nextSibling();
        }
    }

    QFile xmlDoc("config.txt");
    if(xmlDoc.open(QFile::WriteOnly)) {
        xmlDoc.resize(0); //On écrase notre fichier sans modifications
        QTextStream stream;
        stream.setDevice(&xmlDoc);
        doc.save(stream, 4); //On le réécris avec les modifications

        xmlDoc.close();
    }
}















