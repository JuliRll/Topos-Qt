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
    QPushButton *ledPruebaR;
    QPushButton *ledPruebaA;
    QPushButton *ledPruebaAm;
    QPushButton *ledPruebaV;
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
        comboBox->setObjectName(QString::fromUtf8("comboBox"));

        gridLayout->addWidget(comboBox, 0, 0, 1, 1);

        pushButtonEnviar = new QPushButton(groupBox_2);
        pushButtonEnviar->setObjectName(QString::fromUtf8("pushButtonEnviar"));

        gridLayout->addWidget(pushButtonEnviar, 1, 0, 1, 1);

        ledPruebaR = new QPushButton(centralwidget);
        ledPruebaR->setObjectName(QString::fromUtf8("ledPruebaR"));
        ledPruebaR->setGeometry(QRect(40, 130, 21, 21));
        QPalette palette;
        QBrush brush(QColor(255, 0, 0, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush);
        QBrush brush1(QColor(255, 0, 4, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Light, brush1);
        QBrush brush2(QColor(255, 255, 255, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Base, brush2);
        QBrush brush3(QColor(217, 0, 4, 255));
        brush3.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Window, brush3);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush3);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush3);
        ledPruebaR->setPalette(palette);
        ledPruebaR->setAutoFillBackground(true);
        ledPruebaR->setStyleSheet(QString::fromUtf8("in rgb(217, 0, 4)"));
        ledPruebaR->setCheckable(true);
        ledPruebaR->setAutoDefault(false);
        ledPruebaA = new QPushButton(centralwidget);
        ledPruebaA->setObjectName(QString::fromUtf8("ledPruebaA"));
        ledPruebaA->setGeometry(QRect(80, 130, 21, 21));
        QPalette palette1;
        QBrush brush4(QColor(0, 0, 0, 255));
        brush4.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        QBrush brush5(QColor(0, 0, 255, 255));
        brush5.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush5);
        QBrush brush6(QColor(127, 127, 255, 255));
        brush6.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Light, brush6);
        QBrush brush7(QColor(63, 63, 255, 255));
        brush7.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Midlight, brush7);
        QBrush brush8(QColor(0, 0, 127, 255));
        brush8.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Dark, brush8);
        QBrush brush9(QColor(0, 0, 170, 255));
        brush9.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::Mid, brush9);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush4);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush5);
        palette1.setBrush(QPalette::Active, QPalette::Shadow, brush4);
        palette1.setBrush(QPalette::Active, QPalette::AlternateBase, brush6);
        QBrush brush10(QColor(255, 255, 220, 255));
        brush10.setStyle(Qt::SolidPattern);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipBase, brush10);
        palette1.setBrush(QPalette::Active, QPalette::ToolTipText, brush4);
        QBrush brush11(QColor(0, 0, 0, 128));
        brush11.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush11);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Light, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::Midlight, brush7);
        palette1.setBrush(QPalette::Inactive, QPalette::Dark, brush8);
        palette1.setBrush(QPalette::Inactive, QPalette::Mid, brush9);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush5);
        palette1.setBrush(QPalette::Inactive, QPalette::Shadow, brush4);
        palette1.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush6);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush10);
        palette1.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush11);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Light, brush6);
        palette1.setBrush(QPalette::Disabled, QPalette::Midlight, brush7);
        palette1.setBrush(QPalette::Disabled, QPalette::Dark, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Mid, brush9);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush8);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::Shadow, brush4);
        palette1.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush5);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush10);
        palette1.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush11);
#endif
        ledPruebaA->setPalette(palette1);
        ledPruebaA->setAutoFillBackground(true);
        ledPruebaA->setCheckable(true);
        ledPruebaA->setAutoDefault(false);
        ledPruebaAm = new QPushButton(centralwidget);
        ledPruebaAm->setObjectName(QString::fromUtf8("ledPruebaAm"));
        ledPruebaAm->setGeometry(QRect(120, 130, 21, 21));
        QPalette palette2;
        QBrush brush12(QColor(0, 198, 0, 255));
        brush12.setStyle(Qt::SolidPattern);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush12);
        palette2.setBrush(QPalette::Active, QPalette::Light, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush12);
        palette2.setBrush(QPalette::Inactive, QPalette::Light, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush12);
        palette2.setBrush(QPalette::Disabled, QPalette::Light, brush1);
        ledPruebaAm->setPalette(palette2);
        ledPruebaAm->setAutoFillBackground(true);
        ledPruebaAm->setCheckable(true);
        ledPruebaAm->setAutoDefault(false);
        ledPruebaV = new QPushButton(centralwidget);
        ledPruebaV->setObjectName(QString::fromUtf8("ledPruebaV"));
        ledPruebaV->setGeometry(QRect(160, 130, 21, 21));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush4);
        QBrush brush13(QColor(255, 255, 0, 255));
        brush13.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush13);
        QBrush brush14(QColor(255, 255, 127, 255));
        brush14.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Light, brush14);
        QBrush brush15(QColor(255, 255, 63, 255));
        brush15.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Midlight, brush15);
        QBrush brush16(QColor(127, 127, 0, 255));
        brush16.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Dark, brush16);
        QBrush brush17(QColor(170, 170, 0, 255));
        brush17.setStyle(Qt::SolidPattern);
        palette3.setBrush(QPalette::Active, QPalette::Mid, brush17);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush4);
        palette3.setBrush(QPalette::Active, QPalette::BrightText, brush2);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush4);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush2);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush13);
        palette3.setBrush(QPalette::Active, QPalette::Shadow, brush4);
        palette3.setBrush(QPalette::Active, QPalette::AlternateBase, brush14);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipBase, brush10);
        palette3.setBrush(QPalette::Active, QPalette::ToolTipText, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Active, QPalette::PlaceholderText, brush11);
#endif
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush13);
        palette3.setBrush(QPalette::Inactive, QPalette::Light, brush14);
        palette3.setBrush(QPalette::Inactive, QPalette::Midlight, brush15);
        palette3.setBrush(QPalette::Inactive, QPalette::Dark, brush16);
        palette3.setBrush(QPalette::Inactive, QPalette::Mid, brush17);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::BrightText, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush2);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush13);
        palette3.setBrush(QPalette::Inactive, QPalette::Shadow, brush4);
        palette3.setBrush(QPalette::Inactive, QPalette::AlternateBase, brush14);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipBase, brush10);
        palette3.setBrush(QPalette::Inactive, QPalette::ToolTipText, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush11);
#endif
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush16);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush13);
        palette3.setBrush(QPalette::Disabled, QPalette::Light, brush14);
        palette3.setBrush(QPalette::Disabled, QPalette::Midlight, brush15);
        palette3.setBrush(QPalette::Disabled, QPalette::Dark, brush16);
        palette3.setBrush(QPalette::Disabled, QPalette::Mid, brush17);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush16);
        palette3.setBrush(QPalette::Disabled, QPalette::BrightText, brush2);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush16);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush13);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush13);
        palette3.setBrush(QPalette::Disabled, QPalette::Shadow, brush4);
        palette3.setBrush(QPalette::Disabled, QPalette::AlternateBase, brush13);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipBase, brush10);
        palette3.setBrush(QPalette::Disabled, QPalette::ToolTipText, brush4);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush11);
#endif
        ledPruebaV->setPalette(palette3);
        ledPruebaV->setAutoFillBackground(true);
        ledPruebaV->setCheckable(true);
        ledPruebaV->setAutoDefault(false);
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
        ledPruebaR->setDefault(true);
        ledPruebaA->setDefault(true);
        ledPruebaAm->setDefault(true);
        ledPruebaV->setDefault(true);


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
        comboBox->setItemText(0, QCoreApplication::translate("MainWindow", "ALIVE", nullptr));
        comboBox->setItemText(1, QCoreApplication::translate("MainWindow", "GET_LEDS", nullptr));
        comboBox->setItemText(2, QString());
        comboBox->setItemText(3, QString());

        comboBox->setCurrentText(QCoreApplication::translate("MainWindow", "ALIVE", nullptr));
        pushButtonEnviar->setText(QCoreApplication::translate("MainWindow", "Enviar", nullptr));
        ledPruebaR->setText(QString());
        ledPruebaA->setText(QString());
        ledPruebaAm->setText(QString());
        ledPruebaV->setText(QString());
        menuMenu->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
        menuComunicaci_n->setTitle(QCoreApplication::translate("MainWindow", "Comunicaci\303\263n", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
