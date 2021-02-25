/********************************************************************************
** Form generated from reading UI file 'clienttcp.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_CLIENTTCP_H
#define UI_CLIENTTCP_H

#include <QtCore/QVariant>
#include <QtGui/QIcon>
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpacerItem>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientTcp
{
public:
    QWidget *mainwindow1;
    QHBoxLayout *horizontalLayout;
    QWidget *mainwindow2;
    QGridLayout *gridLayout;
    QWidget *group_connexion;
    QGridLayout *gridLayout_2;
    QLabel *label_ip;
    QPushButton *boutonConnexion;
    QLabel *label_port;
    QSpinBox *boxPort;
    QLineEdit *boxIp;
    QSpacerItem *horizontalSpacer;
    QWidget *group_nom;
    QGridLayout *gridLayout_3;
    QLabel *label_image;
    QLabel *label_nom;
    QWidget *group_message;
    QGridLayout *groupe_message;
    QLabel *label_pseudo;
    QLineEdit *boxPseudo;
    QLabel *label_message;
    QLineEdit *boxMessage;
    QPushButton *boutonEnvoyer;
    QTextBrowser *displayMessage;

    void setupUi(QMainWindow *ClientTcp)
    {
        if (ClientTcp->objectName().isEmpty())
            ClientTcp->setObjectName(QString::fromUtf8("ClientTcp"));
        ClientTcp->resize(950, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../../../../Pictures/bulle dialogue 2.jpg"), QSize(), QIcon::Normal, QIcon::Off);
        ClientTcp->setWindowIcon(icon);
        mainwindow1 = new QWidget(ClientTcp);
        mainwindow1->setObjectName(QString::fromUtf8("mainwindow1"));
        horizontalLayout = new QHBoxLayout(mainwindow1);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        mainwindow2 = new QWidget(mainwindow1);
        mainwindow2->setObjectName(QString::fromUtf8("mainwindow2"));
        mainwindow2->setEnabled(true);
        mainwindow2->setToolTipDuration(-1);
        gridLayout = new QGridLayout(mainwindow2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        group_connexion = new QWidget(mainwindow2);
        group_connexion->setObjectName(QString::fromUtf8("group_connexion"));
        group_connexion->setMaximumSize(QSize(16777215, 150));
        gridLayout_2 = new QGridLayout(group_connexion);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        label_ip = new QLabel(group_connexion);
        label_ip->setObjectName(QString::fromUtf8("label_ip"));

        gridLayout_2->addWidget(label_ip, 0, 0, 1, 1);

        boutonConnexion = new QPushButton(group_connexion);
        boutonConnexion->setObjectName(QString::fromUtf8("boutonConnexion"));

        gridLayout_2->addWidget(boutonConnexion, 0, 4, 1, 1);

        label_port = new QLabel(group_connexion);
        label_port->setObjectName(QString::fromUtf8("label_port"));

        gridLayout_2->addWidget(label_port, 0, 2, 1, 1);

        boxPort = new QSpinBox(group_connexion);
        boxPort->setObjectName(QString::fromUtf8("boxPort"));
        boxPort->setMaximum(100000);

        gridLayout_2->addWidget(boxPort, 0, 3, 1, 1);

        boxIp = new QLineEdit(group_connexion);
        boxIp->setObjectName(QString::fromUtf8("boxIp"));

        gridLayout_2->addWidget(boxIp, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(33, 381, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 6, 1, 1);

        group_nom = new QWidget(group_connexion);
        group_nom->setObjectName(QString::fromUtf8("group_nom"));
        group_nom->setMaximumSize(QSize(300, 150));
        gridLayout_3 = new QGridLayout(group_nom);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_image = new QLabel(group_nom);
        label_image->setObjectName(QString::fromUtf8("label_image"));
        label_image->setMaximumSize(QSize(300, 100));
        label_image->setPixmap(QPixmap(QString::fromUtf8("../../../../Pictures/discuter.jpg")));

        gridLayout_3->addWidget(label_image, 0, 0, 1, 1);

        label_nom = new QLabel(group_nom);
        label_nom->setObjectName(QString::fromUtf8("label_nom"));
        label_nom->setMaximumSize(QSize(100, 30));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        label_nom->setFont(font);

        gridLayout_3->addWidget(label_nom, 1, 0, 1, 1, Qt::AlignHCenter);


        gridLayout_2->addWidget(group_nom, 0, 7, 1, 1);


        gridLayout->addWidget(group_connexion, 0, 0, 1, 1);

        group_message = new QWidget(mainwindow2);
        group_message->setObjectName(QString::fromUtf8("group_message"));
        groupe_message = new QGridLayout(group_message);
        groupe_message->setObjectName(QString::fromUtf8("groupe_message"));
        groupe_message->setContentsMargins(-1, -1, -1, 1);
        label_pseudo = new QLabel(group_message);
        label_pseudo->setObjectName(QString::fromUtf8("label_pseudo"));

        groupe_message->addWidget(label_pseudo, 0, 0, 1, 1);

        boxPseudo = new QLineEdit(group_message);
        boxPseudo->setObjectName(QString::fromUtf8("boxPseudo"));
        boxPseudo->setMaxLength(3640);

        groupe_message->addWidget(boxPseudo, 0, 1, 1, 1);

        label_message = new QLabel(group_message);
        label_message->setObjectName(QString::fromUtf8("label_message"));

        groupe_message->addWidget(label_message, 0, 2, 1, 1);

        boxMessage = new QLineEdit(group_message);
        boxMessage->setObjectName(QString::fromUtf8("boxMessage"));

        groupe_message->addWidget(boxMessage, 0, 3, 1, 1);

        boutonEnvoyer = new QPushButton(group_message);
        boutonEnvoyer->setObjectName(QString::fromUtf8("boutonEnvoyer"));

        groupe_message->addWidget(boutonEnvoyer, 0, 4, 1, 1);

        groupe_message->setColumnStretch(3, 1);

        gridLayout->addWidget(group_message, 2, 0, 1, 1);

        displayMessage = new QTextBrowser(mainwindow2);
        displayMessage->setObjectName(QString::fromUtf8("displayMessage"));

        gridLayout->addWidget(displayMessage, 1, 0, 1, 1);


        horizontalLayout->addWidget(mainwindow2);

        ClientTcp->setCentralWidget(mainwindow1);

        retranslateUi(ClientTcp);

        QMetaObject::connectSlotsByName(ClientTcp);
    } // setupUi

    void retranslateUi(QMainWindow *ClientTcp)
    {
        ClientTcp->setWindowTitle(QCoreApplication::translate("ClientTcp", "ClientTcp", nullptr));
        label_ip->setText(QCoreApplication::translate("ClientTcp", "IP du serveur :", nullptr));
        boutonConnexion->setText(QCoreApplication::translate("ClientTcp", "Connexion", nullptr));
        label_port->setText(QCoreApplication::translate("ClientTcp", "Port du serveur :", nullptr));
        boxIp->setPlaceholderText(QCoreApplication::translate("ClientTcp", "255.255.255.255", nullptr));
        label_image->setText(QString());
        label_nom->setText(QCoreApplication::translate("ClientTcp", "MI6 Chat", nullptr));
        label_pseudo->setText(QCoreApplication::translate("ClientTcp", "Pseudo :", nullptr));
        boxPseudo->setText(QString());
        boxPseudo->setPlaceholderText(QCoreApplication::translate("ClientTcp", "Votre pseudo ici", nullptr));
        label_message->setText(QCoreApplication::translate("ClientTcp", "message :", nullptr));
        boxMessage->setPlaceholderText(QCoreApplication::translate("ClientTcp", "Votre message ici", nullptr));
        boutonEnvoyer->setText(QCoreApplication::translate("ClientTcp", "Envoyer", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientTcp: public Ui_ClientTcp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTTCP_H
