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
#include <QtWidgets/QApplication>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QHBoxLayout>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QSlider>
#include <QtWidgets/QSpinBox>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_ClientTcp
{
public:
    QWidget *centralwidget;
    QHBoxLayout *horizontalLayout;
    QWidget *Widget;
    QGridLayout *gridLayout_4;
    QGridLayout *gridLayout;
    QLabel *label;
    QSpinBox *spinBox;
    QSlider *verticalSlider;
    QGridLayout *gridLayout_2;
    QSpinBox *spinBox_2;
    QSlider *verticalSlider_2;
    QLabel *label_2;
    QGridLayout *gridLayout_3;
    QLabel *label_3;
    QSpinBox *spinBox_3;
    QSlider *verticalSlider_3;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *ClientTcp)
    {
        if (ClientTcp->objectName().isEmpty())
            ClientTcp->setObjectName(QString::fromUtf8("ClientTcp"));
        ClientTcp->resize(549, 419);
        centralwidget = new QWidget(ClientTcp);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        horizontalLayout = new QHBoxLayout(centralwidget);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        Widget = new QWidget(centralwidget);
        Widget->setObjectName(QString::fromUtf8("Widget"));
        gridLayout_4 = new QGridLayout(Widget);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        gridLayout = new QGridLayout();
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        label = new QLabel(Widget);
        label->setObjectName(QString::fromUtf8("label"));

        gridLayout->addWidget(label, 0, 0, 1, 1);

        spinBox = new QSpinBox(Widget);
        spinBox->setObjectName(QString::fromUtf8("spinBox"));
        spinBox->setMaximum(255);

        gridLayout->addWidget(spinBox, 1, 0, 1, 1);

        verticalSlider = new QSlider(Widget);
        verticalSlider->setObjectName(QString::fromUtf8("verticalSlider"));
        verticalSlider->setMaximum(255);
        verticalSlider->setOrientation(Qt::Vertical);

        gridLayout->addWidget(verticalSlider, 2, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout, 0, 0, 1, 1);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        spinBox_2 = new QSpinBox(Widget);
        spinBox_2->setObjectName(QString::fromUtf8("spinBox_2"));
        spinBox_2->setMaximum(255);

        gridLayout_2->addWidget(spinBox_2, 2, 0, 1, 1);

        verticalSlider_2 = new QSlider(Widget);
        verticalSlider_2->setObjectName(QString::fromUtf8("verticalSlider_2"));
        verticalSlider_2->setMaximum(255);
        verticalSlider_2->setOrientation(Qt::Vertical);

        gridLayout_2->addWidget(verticalSlider_2, 3, 0, 1, 1);

        label_2 = new QLabel(Widget);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        gridLayout_2->addWidget(label_2, 1, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_2, 0, 1, 1, 1);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        label_3 = new QLabel(Widget);
        label_3->setObjectName(QString::fromUtf8("label_3"));

        gridLayout_3->addWidget(label_3, 0, 0, 1, 1);

        spinBox_3 = new QSpinBox(Widget);
        spinBox_3->setObjectName(QString::fromUtf8("spinBox_3"));
        spinBox_3->setMaximum(255);

        gridLayout_3->addWidget(spinBox_3, 1, 0, 1, 1);

        verticalSlider_3 = new QSlider(Widget);
        verticalSlider_3->setObjectName(QString::fromUtf8("verticalSlider_3"));
        verticalSlider_3->setMaximum(255);
        verticalSlider_3->setOrientation(Qt::Vertical);

        gridLayout_3->addWidget(verticalSlider_3, 2, 0, 1, 1);


        gridLayout_4->addLayout(gridLayout_3, 0, 2, 1, 1);


        horizontalLayout->addWidget(Widget);

        ClientTcp->setCentralWidget(centralwidget);
        statusbar = new QStatusBar(ClientTcp);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        ClientTcp->setStatusBar(statusbar);

        retranslateUi(ClientTcp);
        QObject::connect(verticalSlider, SIGNAL(valueChanged(int)), spinBox, SLOT(setValue(int)));
        QObject::connect(spinBox, SIGNAL(valueChanged(int)), verticalSlider, SLOT(setValue(int)));
        QObject::connect(verticalSlider_2, SIGNAL(valueChanged(int)), spinBox_2, SLOT(setValue(int)));
        QObject::connect(spinBox_2, SIGNAL(valueChanged(int)), verticalSlider_2, SLOT(setValue(int)));
        QObject::connect(verticalSlider_3, SIGNAL(valueChanged(int)), spinBox_3, SLOT(setValue(int)));
        QObject::connect(spinBox_3, SIGNAL(valueChanged(int)), verticalSlider_3, SLOT(setValue(int)));

        QMetaObject::connectSlotsByName(ClientTcp);
    } // setupUi

    void retranslateUi(QMainWindow *ClientTcp)
    {
        ClientTcp->setWindowTitle(QCoreApplication::translate("ClientTcp", "ClientTcp", nullptr));
        label->setText(QCoreApplication::translate("ClientTcp", "RED", nullptr));
        label_2->setText(QCoreApplication::translate("ClientTcp", "GREEN", nullptr));
        label_3->setText(QCoreApplication::translate("ClientTcp", "BLUE", nullptr));
    } // retranslateUi

};

namespace Ui {
    class ClientTcp: public Ui_ClientTcp {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_CLIENTTCP_H
