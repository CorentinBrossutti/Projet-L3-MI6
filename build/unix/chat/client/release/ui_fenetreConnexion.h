/********************************************************************************
** Form generated from reading UI file 'fenetreConnexion.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_FENETRECONNEXION_H
#define UI_FENETRECONNEXION_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QDialog>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QTextEdit>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_fenetreConnexion
{
public:
    QWidget *widget;
    QSpinBox *boxPort;
    QLineEdit *boxIp;
    QPushButton *boutonConnexion;
    QLabel *label;
    QLabel *label_2;
    QLabel *label_3;
    QLineEdit *boxPseudo;
    QTextEdit *displayMessage;
    QLabel *label_4;

    void setupUi(QDialog *fenetreConnexion)
    {
        if (fenetreConnexion->objectName().isEmpty())
            fenetreConnexion->setObjectName(QString::fromUtf8("fenetreConnexion"));
        fenetreConnexion->resize(530, 420);
        widget = new QWidget(fenetreConnexion);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(10, 10, 510, 400));
        boxPort = new QSpinBox(widget);
        boxPort->setObjectName(QString::fromUtf8("boxPort"));
        boxPort->setEnabled(true);
        boxPort->setGeometry(QRect(390, 50, 111, 26));
        boxPort->setMouseTracking(true);
        boxPort->setFocusPolicy(Qt::StrongFocus);
        boxPort->setKeyboardTracking(true);
        boxPort->setMaximum(100000);
        boxIp = new QLineEdit(widget);
        boxIp->setObjectName(QString::fromUtf8("boxIp"));
        boxIp->setGeometry(QRect(120, 50, 120, 25));
        boxIp->setTabletTracking(false);
        boxIp->setFocusPolicy(Qt::StrongFocus);
        boxIp->setContextMenuPolicy(Qt::DefaultContextMenu);
        boxIp->setAutoFillBackground(false);
        boxIp->setReadOnly(false);
        boutonConnexion = new QPushButton(widget);
        boutonConnexion->setObjectName(QString::fromUtf8("boutonConnexion"));
        boutonConnexion->setGeometry(QRect(340, 115, 89, 25));
        boutonConnexion->setMouseTracking(true);
        boutonConnexion->setFocusPolicy(Qt::StrongFocus);
        label = new QLabel(widget);
        label->setObjectName(QString::fromUtf8("label"));
        label->setGeometry(QRect(10, 35, 100, 50));
        label_2 = new QLabel(widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));
        label_2->setGeometry(QRect(260, 35, 120, 50));
        label_3 = new QLabel(widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));
        label_3->setGeometry(QRect(10, 100, 100, 50));
        boxPseudo = new QLineEdit(widget);
        boxPseudo->setObjectName(QString::fromUtf8("boxPseudo"));
        boxPseudo->setGeometry(QRect(130, 115, 181, 25));
        boxPseudo->setMouseTracking(true);
        boxPseudo->setFocusPolicy(Qt::StrongFocus);
        displayMessage = new QTextEdit(widget);
        displayMessage->setObjectName(QString::fromUtf8("displayMessage"));
        displayMessage->setGeometry(QRect(10, 240, 490, 150));
        displayMessage->setMouseTracking(true);
        displayMessage->setFocusPolicy(Qt::NoFocus);
        label_4 = new QLabel(widget);
        label_4->setObjectName(QString::fromUtf8("label_4"));
        label_4->setGeometry(QRect(10, 190, 490, 40));
        label_4->setScaledContents(false);
        label_4->setAlignment(Qt::AlignCenter);
        label_4->setWordWrap(false);
        QWidget::setTabOrder(boxIp, boxPort);
        QWidget::setTabOrder(boxPort, boxPseudo);
        QWidget::setTabOrder(boxPseudo, boutonConnexion);

        retranslateUi(fenetreConnexion);

        QMetaObject::connectSlotsByName(fenetreConnexion);
    } // setupUi

    void retranslateUi(QDialog *fenetreConnexion)
    {
        fenetreConnexion->setWindowTitle(QCoreApplication::translate("fenetreConnexion", "Dialog", nullptr));
        boxIp->setInputMask(QString());
        boxIp->setText(QString());
        boxIp->setPlaceholderText(QCoreApplication::translate("fenetreConnexion", "255.255.255.255", nullptr));
        boutonConnexion->setText(QCoreApplication::translate("fenetreConnexion", "Connexion", nullptr));
        label->setText(QCoreApplication::translate("fenetreConnexion", "IP du serveur :", nullptr));
        label_2->setText(QCoreApplication::translate("fenetreConnexion", "Port du serveur :", nullptr));
        label_3->setText(QCoreApplication::translate("fenetreConnexion", "Votre pseudo :", nullptr));
        boxPseudo->setPlaceholderText(QCoreApplication::translate("fenetreConnexion", "Votre pseudo ici", nullptr));
        label_4->setText(QCoreApplication::translate("fenetreConnexion", "Logs :", nullptr));
    } // retranslateUi

};

namespace Ui {
    class fenetreConnexion: public Ui_fenetreConnexion {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_FENETRECONNEXION_H
