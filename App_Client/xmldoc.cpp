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
        creerFichier(nomFichier);
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

void XmlDoc::creerFichier(QString monFichier) {
    QDomDocument doc;
    QDomElement infoClient = doc.createElement("infoClient");
    doc.appendChild(infoClient);
    QDomElement pseudo = doc.createElement("pseudo");
    infoClient.appendChild(pseudo);
    QDomElement age = doc.createElement("age");
    QDomElement ip = doc.createElement("ip");
    QDomElement port = doc.createElement("port");
    QDomText valeurAge = doc.createTextNode("25 ans");
    age.appendChild(valeurAge);
    infoClient.appendChild(age);
    infoClient.appendChild(ip);
    infoClient.appendChild(port);

    QFile file(monFichier);
    if(file.open(QIODevice::ReadWrite)) {
        QTextStream out(&file);
        doc.save(out,4,QDomDocument::EncodingFromDocument);
        file.close();
    }
    else {
    QMessageBox::warning(this, "Erreur de la création du fichier", "Le fichier config.txt n'a pas pu être crée  .");
    file.close();
    }
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

QString XmlDoc::chargerIp(QString nomFichier) {
    chargerFichierConfig(nomFichier);

    docElement = doc.documentElement();
    noeud = docElement.firstChild();

    while(!noeud.isNull()) {
        element = noeud.toElement();
        if(!element.isNull()) {
            if(element.tagName() == "ip" && (element.text()!="")) {
                return element.text(); //On retourne son contenu
            }
            noeud = noeud.nextSibling();
        }
    }
    return ("192.168.0.1");
}

QString XmlDoc::chargerPort(QString nomFichier) {
    chargerFichierConfig(nomFichier);

    docElement = doc.documentElement();
    noeud = docElement.firstChild();

    while(!noeud.isNull()) {
        element = noeud.toElement();
        if(!element.isNull()) {
            if(element.tagName() == "port" && (element.text()!="")) {
                return element.text(); //On retourne son contenu
            }
            noeud = noeud.nextSibling();
        }
    }
    return ("10554");
}

//Méthode de sauvegarde du pseudo dans le fichier XML
void XmlDoc::sauvegarderPseudo(QString nomFichier, QString pseudo, QString ip, QString port) {
    chargerFichierConfig(nomFichier);

    QDomElement newPseudo = doc.createElement(QString("pseudo")); //On crée notre nouveau Noeud
    QDomText textPseudo = doc.createTextNode(QString(pseudo)); //On y met le pseudo voulu
    newPseudo.appendChild(textPseudo);
    QDomElement newIp = doc.createElement(QString("ip")); //On crée notre nouveau Noeud
    QDomText textIp = doc.createTextNode(QString(ip)); //On y met l'ip voulu
    newIp.appendChild(textIp);
    QDomElement newPort = doc.createElement(QString("port")); //On crée notre nouveau Noeud
    QDomText textPort = doc.createTextNode(QString(port)); //On y met le port voulu
    newPort.appendChild(textPort);

    docElement = doc.documentElement(); //On récupère le document chargé
    noeud = docElement.firstChildElement("pseudo");
    docElement.replaceChild(newPseudo,noeud);
    noeud = docElement.firstChildElement("ip");
    docElement.replaceChild(newIp,noeud);
    noeud = docElement.firstChildElement("port");
    docElement.replaceChild(newPort,noeud);

    /*while(!noeud.isNull()) { //On parcourt notre Noeud
        element = noeud.toElement();
        if (!element.isNull()) {
            if (element.tagName() == "pseudo") { //Si on trouve notre noeud qui contient le pseudo
                docElement.replaceChild(newPseudo, noeud); //Alors on le remplace par le nouveau Noeud qui continent notre nouveau Pseudo
            }
            if (element.tagName() == "ip") {
                docElement.replaceChild(newIp, noeud);
            }
            if (element.tagName() == "port") {
                docElement.replaceChild(newPort, noeud);

            }
            noeud = noeud.nextSibling();
        }
    }*/

    QFile xmlDoc("config.txt");
    if(xmlDoc.open(QFile::WriteOnly)) {
        xmlDoc.resize(0); //On écrase notre fichier sans modifications
        QTextStream stream;
        stream.setDevice(&xmlDoc);
        doc.save(stream, 4); //On le réécris avec les modifications

        xmlDoc.close();
    }
}















