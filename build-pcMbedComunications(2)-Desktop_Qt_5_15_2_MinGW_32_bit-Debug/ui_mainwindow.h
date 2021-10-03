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
#include <QtWidgets/QGroupBox>
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
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
    QAction *Conectar;
    QWidget *centralwidget;
    QWidget *widget;
    QGroupBox *groupBox;
    QTextBrowser *textBrowser;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLCDNumber *puntaje_2;
    QLCDNumber *aciertos_2;
    QLCDNumber *errores_2;
    QLCDNumber *fallos_2;
    QLabel *aciertos;
    QLabel *errores;
    QLabel *fallos;
    QLabel *estado1;
    QLabel *puntaje;
    QMenuBar *menubar;
    QMenu *menuMenu;
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
        Conectar = new QAction(MainWindow);
        Conectar->setObjectName(QString::fromUtf8("Conectar"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(20, 210, 860, 191));
        groupBox = new QGroupBox(centralwidget);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        groupBox->setGeometry(QRect(410, 0, 481, 151));
        textBrowser = new QTextBrowser(groupBox);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));
        textBrowser->setGeometry(QRect(70, 20, 401, 121));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(720, 160, 80, 21));
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName(QString::fromUtf8("pushButton_2"));
        pushButton_2->setGeometry(QRect(620, 160, 80, 21));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName(QString::fromUtf8("pushButton_3"));
        pushButton_3->setGeometry(QRect(520, 160, 80, 21));
        puntaje_2 = new QLCDNumber(centralwidget);
        puntaje_2->setObjectName(QString::fromUtf8("puntaje_2"));
        puntaje_2->setGeometry(QRect(280, 10, 64, 23));
        puntaje_2->setAutoFillBackground(false);
        puntaje_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        puntaje_2->setFrameShadow(QFrame::Plain);
        aciertos_2 = new QLCDNumber(centralwidget);
        aciertos_2->setObjectName(QString::fromUtf8("aciertos_2"));
        aciertos_2->setGeometry(QRect(280, 40, 64, 23));
        aciertos_2->setAutoFillBackground(false);
        aciertos_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        errores_2 = new QLCDNumber(centralwidget);
        errores_2->setObjectName(QString::fromUtf8("errores_2"));
        errores_2->setGeometry(QRect(280, 70, 64, 23));
        errores_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        fallos_2 = new QLCDNumber(centralwidget);
        fallos_2->setObjectName(QString::fromUtf8("fallos_2"));
        fallos_2->setGeometry(QRect(280, 100, 64, 23));
        fallos_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        aciertos = new QLabel(centralwidget);
        aciertos->setObjectName(QString::fromUtf8("aciertos"));
        aciertos->setGeometry(QRect(220, 40, 71, 20));
        errores = new QLabel(centralwidget);
        errores->setObjectName(QString::fromUtf8("errores"));
        errores->setGeometry(QRect(220, 70, 71, 20));
        fallos = new QLabel(centralwidget);
        fallos->setObjectName(QString::fromUtf8("fallos"));
        fallos->setGeometry(QRect(220, 100, 71, 20));
        estado1 = new QLabel(centralwidget);
        estado1->setObjectName(QString::fromUtf8("estado1"));
        estado1->setGeometry(QRect(10, 10, 181, 20));
        puntaje = new QLabel(centralwidget);
        puntaje->setObjectName(QString::fromUtf8("puntaje"));
        puntaje->setGeometry(QRect(220, 10, 71, 20));
        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 900, 20));
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);

        menubar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionSalir);
        menuMenu->addAction(Conectar);

        retranslateUi(MainWindow);

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
        Conectar->setText(QCoreApplication::translate("MainWindow", "Conectar", nullptr));
        groupBox->setTitle(QCoreApplication::translate("MainWindow", "Flujo de Datos", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "SET LEDS", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "GET LEDS", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "GET BUTTONS", nullptr));
        aciertos->setText(QCoreApplication::translate("MainWindow", "ACIERTOS", nullptr));
        errores->setText(QCoreApplication::translate("MainWindow", "ERRORES", nullptr));
        fallos->setText(QCoreApplication::translate("MainWindow", "FALLOS", nullptr));
        estado1->setText(QCoreApplication::translate("MainWindow", "Estado: ", nullptr));
        puntaje->setText(QCoreApplication::translate("MainWindow", "PUNTAJE", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
