/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 5.15.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QAction>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QGridLayout>
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QTextBrowser>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *actionSalir;
    QAction *actionEscaneo_de_Puertos;
    QAction *actionDesconectar;
    QAction *actionConectar;
    QWidget *centralwidget;
    QWidget *widget;
    QGroupBox *groupBox;
    QTextBrowser *textBrowser;
    QGroupBox *groupBox_2;
    QGridLayout *gridLayout;
    QComboBox *comboBox;
    QPushButton *pushButtonEnviar;
    QMenuBar *menubar;
    QMenu *menuMenu;
    QMenu *menuComunicaci_n;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(900, 550);
        MainWindow->setTabShape(QTabWidget::Triangular);
        actionSalir = new QAction(MainWindow);
        actionSalir->setObjectName(QString::fromUtf8("actionSalir"));
        actionEscaneo_de_Puertos = new QAction(MainWindow);
        actionEscaneo_de_Puertos->setObjectName(QString::fromUtf8("actionEscaneo_de_Puertos"));
        actionDesconectar = new QAction(MainWindow);
        actionDesconectar->setObjectName(QString::fromUtf8("actionDesconectar"));
        actionConectar = new QAction(MainWindow);
        actionConectar->setObjectName(QString::fromUtf8("actionConectar"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 189, 860, 191));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(200, 10, 691, 151));
        textBrowser = new QTextBrowser(groupBox);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(20, 20, 661, 121));
        groupBox_2 = new QGroupBox(centralwidget);
        groupBox_2->setObjectName(QString::fromUtf8("groupBox_2"));
        groupBox_2->setGeometry(QRect(30, 30, 162, 97));
        gridLayout = new QGridLayout(groupBox_2);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        comboBox = new QComboBox(groupBox_2);
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->addItem(QString());
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 0, 1, 1);

        pushButtonEnviar = new QPushButton(groupBox_2);
        pushButtonEnviar->setObjectName(QString::fromUtf8("pushButtonEnviar"));

        gridLayout->addWidget(pushButtonEnviar, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 20));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        menuComunicaci_n = new QMenu(menuMenu);
        menuComunicaci_n->setObjectName(QString::fromUtf8("menuComunicaci_n"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());
        menuMenu->addAction(menuComunicaci_n->menuAction());
        menuMenu->addAction(actionSalir);
        menuComunicaci_n->addAction(actionEscaneo_de_Puertos);
        menuComunicaci_n->addAction(actionDesconectar);
        menuComunicaci_n->addAction(actionConectar);

        retranslateUi(MainWindow);

        comboBox->setCurrentIndex(0);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "Comunicaci\303\263n entre PC - Mbed", nullptr));
        actionSalir->setText(QCoreApplication::translate("MainWindow", "Salir", nullptr));
        actionEscaneo_de_Puertos->setText(QCoreApplication::translate("MainWindow", "Escaneo de Puertos", nullptr));
        actionDesconectar->setText(QCoreApplication::translate("MainWindow", "Desconectar", nullptr));
#if QT_CONFIG(tooltip)
        actionDesconectar->setToolTip(QCoreApplication::translate("MainWindow", "Desconectar", nullptr));
#endif // QT_CONFIG(tooltip)
        actionConectar->setText(QCoreApplication::translate("MainWindow", "Conectar", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Flujo de Datos", nullptr));
        groupBox_2->setTitle(QCoreApplication::translate("MainWindow", "Comunicaciones", nullptr));
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "Selector de comandos", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "ALIVE", nullptr));
        comboBox->setItemText(2, QCoreApplication::translate("MainWindow", "GETBUTTONSTATE", nullptr));
        comboBox->setItemText(3, QCoreApplication::translate("MainWindow", "SETLEDS", nullptr));
        comboBox->setItemText(4, QString());
        comboBox->setItemText(5, QString());

        comboBox->setCurrentText(QCoreApplication::translate("MainWindow", "Selector de comandos", nullptr));
        pushButtonEnviar->setText(QCoreApplication::translate("MainWindow", "Enviar", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        menuComunicaci_n->setTitle(QCoreApplication::translate("MainWindow", "Comunicaci\303\263n", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
