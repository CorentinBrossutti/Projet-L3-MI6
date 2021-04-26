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
    QWidget *group_message;
    QGridLayout *groupe_message;
    QLabel *label_message;
    QPushButton *boutonEnvoyer;
    QLineEdit *boxMessage;
    QWidget *group_titre_image;
    QGridLayout *gridLayout_2;
    QWidget *group_nom;
    QGridLayout *gridLayout_3;
    QLabel *label_nom;
    QLabel *label_image;
    QWidget *zone_pseudo_2;
    QGridLayout *zone_pseudo;
    QLineEdit *boxPseudo;
    QPushButton *boutonPseudo;
    QSpacerItem *horizontalSpacer;
    QTextBrowser *displayMessage;

    void setupUi(QMainWindow *ClientTcp)
    {
        if (ClientTcp->objectName().isEmpty())
            ClientTcp->setObjectName(QString::fromUtf8("ClientTcp"));
        ClientTcp->resize(950, 600);
        QIcon icon;
        icon.addFile(QString::fromUtf8("../build/win/chat/client/conversation_102940.png"), QSize(), QIcon::Normal, QIcon::Off);
        ClientTcp->setWindowIcon(icon);
        ClientTcp->setLayoutDirection(Qt::LeftToRight);
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
        group_message = new QWidget(mainwindow2);
        group_message->setObjectName(QString::fromUtf8("group_message"));
        groupe_message = new QGridLayout(group_message);
        groupe_message->setObjectName(QString::fromUtf8("groupe_message"));
        groupe_message->setContentsMargins(-1, -1, -1, 1);
        label_message = new QLabel(group_message);
        label_message->setObjectName(QString::fromUtf8("label_message"));

        groupe_message->addWidget(label_message, 0, 2, 1, 1);

        boutonEnvoyer = new QPushButton(group_message);
        boutonEnvoyer->setObjectName(QString::fromUtf8("boutonEnvoyer"));

        groupe_message->addWidget(boutonEnvoyer, 0, 5, 1, 1);

        boxMessage = new QLineEdit(group_message);
        boxMessage->setObjectName(QString::fromUtf8("boxMessage"));

        groupe_message->addWidget(boxMessage, 0, 3, 1, 1);

        groupe_message->setColumnStretch(3, 1);

        gridLayout->addWidget(group_message, 5, 0, 1, 1);

        group_titre_image = new QWidget(mainwindow2);
        group_titre_image->setObjectName(QString::fromUtf8("group_titre_image"));
        group_titre_image->setEnabled(true);
        group_titre_image->setMaximumSize(QSize(16777215, 150));
        gridLayout_2 = new QGridLayout(group_titre_image);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        gridLayout_2->setContentsMargins(9, -1, -1, -1);
        group_nom = new QWidget(group_titre_image);
        group_nom->setObjectName(QString::fromUtf8("group_nom"));
        group_nom->setEnabled(true);
        group_nom->setMaximumSize(QSize(500, 150));
        group_nom->setLayoutDirection(Qt::LeftToRight);
        gridLayout_3 = new QGridLayout(group_nom);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        gridLayout_3->setSizeConstraint(QLayout::SetDefaultConstraint);
        gridLayout_3->setContentsMargins(9, -1, 9, -1);
        label_nom = new QLabel(group_nom);
        label_nom->setObjectName(QString::fromUtf8("label_nom"));
        label_nom->setMaximumSize(QSize(500, 200));
        QFont font;
        font.setFamily(QString::fromUtf8("Arial"));
        font.setPointSize(14);
        label_nom->setFont(font);

        gridLayout_3->addWidget(label_nom, 2, 1, 1, 1);

        label_image = new QLabel(group_nom);
        label_image->setObjectName(QString::fromUtf8("label_image"));
        label_image->setMaximumSize(QSize(150, 150));
        label_image->setPixmap(QPixmap(QString::fromUtf8(":/conversation_102940.png")));
        label_image->setAlignment(Qt::AlignCenter);

        gridLayout_3->addWidget(label_image, 2, 0, 1, 1);


        gridLayout_2->addWidget(group_nom, 0, 3, 1, 1);

        zone_pseudo_2 = new QWidget(group_titre_image);
        zone_pseudo_2->setObjectName(QString::fromUtf8("zone_pseudo_2"));
        zone_pseudo_2->setMaximumSize(QSize(250, 16777215));
        zone_pseudo = new QGridLayout(zone_pseudo_2);
        zone_pseudo->setObjectName(QString::fromUtf8("zone_pseudo"));
        boxPseudo = new QLineEdit(zone_pseudo_2);
        boxPseudo->setObjectName(QString::fromUtf8("boxPseudo"));
        boxPseudo->setMaximumSize(QSize(100, 16777215));
        boxPseudo->setLayoutDirection(Qt::LeftToRight);
        boxPseudo->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);

        zone_pseudo->addWidget(boxPseudo, 0, 0, 1, 1);

        boutonPseudo = new QPushButton(zone_pseudo_2);
        boutonPseudo->setObjectName(QString::fromUtf8("boutonPseudo"));

        zone_pseudo->addWidget(boutonPseudo, 0, 1, 1, 1);


        gridLayout_2->addWidget(zone_pseudo_2, 0, 1, 1, 1);

        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        gridLayout_2->addItem(horizontalSpacer, 0, 2, 1, 1);


        gridLayout->addWidget(group_titre_image, 0, 0, 1, 1);

        displayMessage = new QTextBrowser(mainwindow2);
        displayMessage->setObjectName(QString::fromUtf8("displayMessage"));

        gridLayout->addWidget(displayMessage, 3, 0, 1, 1);


        horizontalLayout->addWidget(mainwindow2);

        ClientTcp->setCentralWidget(mainwindow1);

        retranslateUi(ClientTcp);

        QMetaObject::connectSlotsByName(ClientTcp);
    } // setupUi

    void retranslateUi(QMainWindow *ClientTcp)
    {
        ClientTcp->setWindowTitle(QCoreApplication::translate("ClientTcp", "ClientTcp", nullptr));
        label_message->setText(QCoreApplication::translate("ClientTcp", "Message :", nullptr));
        boutonEnvoyer->setText(QCoreApplication::translate("ClientTcp", "Envoyer", nullptr));
        boxMessage->setPlaceholderText(QCoreApplication::translate("ClientTcp", "Votre message ici", nullptr));
        label_nom->setText(QCoreApplication::translate("ClientTcp", "<html><head/><body><p><span style=\" font-size:48pt;\">MI6 Chat</span></p></body></html>", nullptr));
        label_image->setText(QString());
        boutonPseudo->setText(QCoreApplication::translate("ClientTcp", "Changer Pseudo", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientTcp: public Ui_ClientTcp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTTCP_H
