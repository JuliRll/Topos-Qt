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
#include <QtWidgets/QLCDNumber>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenu>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QProgressBar>
#include <QtWidgets/QPushButton>
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
    QAction *Desconectar;
    QAction *Escaneo_de_puertos;
    QWidget *centralwidget;
    QWidget *widget;
    QLCDNumber *puntaje_2;
    QLCDNumber *aciertos_2;
    QLCDNumber *errores_2;
    QLCDNumber *fallos_2;
    QLabel *aciertos;
    QLabel *errores;
    QLabel *fallos;
    QLabel *estado1;
    QLabel *puntaje;
    QProgressBar *progressBar;
    QLCDNumber *record_2;
    QLabel *record;
    QPushButton *pushButton;
    QLCDNumber *partida_2;
    QLabel *partida;
    QMenuBar *menubar;
    QMenu *menuMenu;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(840, 330);
        MainWindow->setStyleSheet(QString::fromUtf8("background-color: rgb(52, 52, 52);"));
        MainWindow->setTabShape(QTabWidget::Triangular);
        MainWindow->setDockNestingEnabled(false);
        MainWindow->setDockOptions(QMainWindow::AllowTabbedDocks|QMainWindow::AnimatedDocks);
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
        Desconectar = new QAction(MainWindow);
        Desconectar->setObjectName(QString::fromUtf8("Desconectar"));
        Escaneo_de_puertos = new QAction(MainWindow);
        Escaneo_de_puertos->setObjectName(QString::fromUtf8("Escaneo_de_puertos"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        widget = new QWidget(centralwidget);
        widget->setObjectName(QString::fromUtf8("widget"));
        widget->setGeometry(QRect(120, 10, 730, 300));
        widget->setAutoFillBackground(false);
        widget->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);"));
        puntaje_2 = new QLCDNumber(centralwidget);
        puntaje_2->setObjectName(QString::fromUtf8("puntaje_2"));
        puntaje_2->setGeometry(QRect(60, 10, 60, 30));
        puntaje_2->setMaximumSize(QSize(60, 30));
        puntaje_2->setLayoutDirection(Qt::LeftToRight);
        puntaje_2->setAutoFillBackground(false);
        puntaje_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"background-color: rgb(0, 0, 0);"));
        puntaje_2->setFrameShape(QFrame::NoFrame);
        puntaje_2->setFrameShadow(QFrame::Raised);
        puntaje_2->setSmallDecimalPoint(false);
        puntaje_2->setDigitCount(5);
        puntaje_2->setSegmentStyle(QLCDNumber::Filled);
        aciertos_2 = new QLCDNumber(centralwidget);
        aciertos_2->setObjectName(QString::fromUtf8("aciertos_2"));
        aciertos_2->setGeometry(QRect(60, 40, 60, 30));
        aciertos_2->setMaximumSize(QSize(60, 16777215));
        aciertos_2->setAutoFillBackground(false);
        aciertos_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"background-color: rgb(0, 0, 0);"));
        aciertos_2->setFrameShape(QFrame::NoFrame);
        aciertos_2->setFrameShadow(QFrame::Raised);
        errores_2 = new QLCDNumber(centralwidget);
        errores_2->setObjectName(QString::fromUtf8("errores_2"));
        errores_2->setGeometry(QRect(60, 100, 60, 30));
        errores_2->setMaximumSize(QSize(60, 16777215));
        errores_2->setAutoFillBackground(false);
        errores_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"background-color: rgb(0, 0, 0);"));
        errores_2->setFrameShape(QFrame::NoFrame);
        errores_2->setFrameShadow(QFrame::Raised);
        fallos_2 = new QLCDNumber(centralwidget);
        fallos_2->setObjectName(QString::fromUtf8("fallos_2"));
        fallos_2->setGeometry(QRect(60, 70, 60, 30));
        fallos_2->setMaximumSize(QSize(60, 16777215));
        fallos_2->setAutoFillBackground(false);
        fallos_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"background-color: rgb(0, 0, 0);"));
        fallos_2->setFrameShape(QFrame::NoFrame);
        fallos_2->setFrameShadow(QFrame::Raised);
        aciertos = new QLabel(centralwidget);
        aciertos->setObjectName(QString::fromUtf8("aciertos"));
        aciertos->setGeometry(QRect(0, 40, 60, 30));
        aciertos->setMaximumSize(QSize(60, 16777215));
        QPalette palette;
        QBrush brush(QColor(255, 255, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::WindowText, brush);
        QBrush brush1(QColor(0, 0, 0, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        palette.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette.setBrush(QPalette::Active, QPalette::Window, brush1);
        QBrush brush2(QColor(255, 255, 255, 128));
        brush2.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette.setBrush(QPalette::Disabled, QPalette::Window, brush1);
        QBrush brush3(QColor(0, 0, 0, 128));
        brush3.setStyle(Qt::SolidPattern);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
#endif
        aciertos->setPalette(palette);
        aciertos->setAutoFillBackground(false);
        aciertos->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        errores = new QLabel(centralwidget);
        errores->setObjectName(QString::fromUtf8("errores"));
        errores->setGeometry(QRect(0, 100, 60, 30));
        errores->setMaximumSize(QSize(60, 16777215));
        QPalette palette1;
        palette1.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Text, brush);
        palette1.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Active, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette1.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette1.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette1.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette1.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette1.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
#endif
        errores->setPalette(palette1);
        errores->setAutoFillBackground(false);
        errores->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        fallos = new QLabel(centralwidget);
        fallos->setObjectName(QString::fromUtf8("fallos"));
        fallos->setGeometry(QRect(0, 70, 60, 30));
        fallos->setMaximumSize(QSize(60, 16777215));
        QPalette palette2;
        palette2.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Text, brush);
        palette2.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Active, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette2.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette2.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette2.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette2.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette2.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
#endif
        fallos->setPalette(palette2);
        fallos->setAutoFillBackground(false);
        fallos->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        estado1 = new QLabel(centralwidget);
        estado1->setObjectName(QString::fromUtf8("estado1"));
        estado1->setGeometry(QRect(0, 290, 120, 20));
        estado1->setAutoFillBackground(false);
        estado1->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);"));
        estado1->setFrameShape(QFrame::NoFrame);
        estado1->setFrameShadow(QFrame::Raised);
        estado1->setTextFormat(Qt::AutoText);
        estado1->setAlignment(Qt::AlignCenter);
        puntaje = new QLabel(centralwidget);
        puntaje->setObjectName(QString::fromUtf8("puntaje"));
        puntaje->setGeometry(QRect(0, 10, 60, 30));
        puntaje->setMaximumSize(QSize(60, 16777215));
        QPalette palette3;
        palette3.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Text, brush);
        palette3.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Active, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette3.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette3.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette3.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette3.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette3.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
#endif
        puntaje->setPalette(palette3);
        puntaje->setAutoFillBackground(false);
        puntaje->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setEnabled(true);
        progressBar->setGeometry(QRect(-1, 0, 851, 10));
        progressBar->setFocusPolicy(Qt::NoFocus);
        progressBar->setContextMenuPolicy(Qt::NoContextMenu);
        progressBar->setAcceptDrops(true);
#if QT_CONFIG(tooltip)
        progressBar->setToolTip(QString::fromUtf8(""));
#endif // QT_CONFIG(tooltip)
        progressBar->setAutoFillBackground(false);
        progressBar->setStyleSheet(QString::fromUtf8("QProgressBar {\n"
"	background-color: rgb(40, 40, 40);\n"
"	border: 0px solid black;\n"
"	border-radius: 0px\n"
"}\n"
"\n"
"QProgressBar::chunk {\n"
"	background-color: #a70006;\n"
"	width: 10px;\n"
"}"));
        progressBar->setMaximum(2990);
        progressBar->setValue(0);
        progressBar->setAlignment(Qt::AlignLeading|Qt::AlignLeft|Qt::AlignVCenter);
        progressBar->setTextVisible(false);
        progressBar->setInvertedAppearance(false);
        record_2 = new QLCDNumber(centralwidget);
        record_2->setObjectName(QString::fromUtf8("record_2"));
        record_2->setGeometry(QRect(60, 132, 60, 30));
        record_2->setMaximumSize(QSize(60, 16777215));
        record_2->setLayoutDirection(Qt::LeftToRight);
        record_2->setAutoFillBackground(false);
        record_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"background-color: rgb(0, 0, 0);"));
        record_2->setFrameShape(QFrame::NoFrame);
        record_2->setFrameShadow(QFrame::Raised);
        record_2->setSmallDecimalPoint(false);
        record_2->setDigitCount(5);
        record_2->setSegmentStyle(QLCDNumber::Filled);
        record = new QLabel(centralwidget);
        record->setObjectName(QString::fromUtf8("record"));
        record->setGeometry(QRect(0, 132, 60, 30));
        record->setMaximumSize(QSize(60, 16777215));
        QPalette palette4;
        palette4.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Text, brush);
        palette4.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Active, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette4.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette4.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette4.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette4.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette4.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
#endif
        record->setPalette(palette4);
        record->setAutoFillBackground(false);
        record->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName(QString::fromUtf8("pushButton"));
        pushButton->setGeometry(QRect(20, 170, 80, 21));
        pushButton->setStyleSheet(QString::fromUtf8("background-color: rgb(85, 85, 85);\n"
"color: rgb(255, 255, 255);"));
        pushButton->setFlat(false);
        partida_2 = new QLCDNumber(centralwidget);
        partida_2->setObjectName(QString::fromUtf8("partida_2"));
        partida_2->setGeometry(QRect(60, 258, 60, 30));
        partida_2->setMaximumSize(QSize(60, 16777215));
        partida_2->setLayoutDirection(Qt::LeftToRight);
        partida_2->setAutoFillBackground(false);
        partida_2->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"background-color: rgb(0, 0, 0);"));
        partida_2->setFrameShape(QFrame::NoFrame);
        partida_2->setFrameShadow(QFrame::Raised);
        partida_2->setSmallDecimalPoint(false);
        partida_2->setDigitCount(5);
        partida_2->setSegmentStyle(QLCDNumber::Filled);
        partida = new QLabel(centralwidget);
        partida->setObjectName(QString::fromUtf8("partida"));
        partida->setGeometry(QRect(0, 258, 60, 30));
        partida->setMaximumSize(QSize(60, 16777215));
        QPalette palette5;
        palette5.setBrush(QPalette::Active, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Active, QPalette::Button, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Text, brush);
        palette5.setBrush(QPalette::Active, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Active, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Active, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette5.setBrush(QPalette::Active, QPalette::PlaceholderText, brush2);
#endif
        palette5.setBrush(QPalette::Inactive, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Button, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Text, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Inactive, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Inactive, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette5.setBrush(QPalette::Inactive, QPalette::PlaceholderText, brush2);
#endif
        palette5.setBrush(QPalette::Disabled, QPalette::WindowText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Button, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Text, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::ButtonText, brush);
        palette5.setBrush(QPalette::Disabled, QPalette::Base, brush1);
        palette5.setBrush(QPalette::Disabled, QPalette::Window, brush1);
#if QT_VERSION >= QT_VERSION_CHECK(5, 12, 0)
        palette5.setBrush(QPalette::Disabled, QPalette::PlaceholderText, brush3);
#endif
        partida->setPalette(palette5);
        partida->setAutoFillBackground(false);
        partida->setStyleSheet(QString::fromUtf8("background-color: rgb(0, 0, 0);\n"
"color: rgb(255, 255, 255);\n"
"background-color: rgb(0, 0, 0);"));
        MainWindow->setCentralWidget(centralwidget);
        progressBar->raise();
        widget->raise();
        puntaje_2->raise();
        aciertos_2->raise();
        errores_2->raise();
        fallos_2->raise();
        aciertos->raise();
        errores->raise();
        fallos->raise();
        estado1->raise();
        puntaje->raise();
        record_2->raise();
        record->raise();
        pushButton->raise();
        partida_2->raise();
        partida->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 840, 17));
        menubar->setStyleSheet(QString::fromUtf8("QMenuBar {    \n"
"	color: rgb(255, 255, 255);\n"
"	background-color: rgb(76,74,72);\n"
"    spacing: 0px; /* spacing between menu bar items */\n"
"}\n"
"\n"
"QMenuBar::item {\n"
"    padding: 1px 4px;\n"
"    background: transparent;\n"
"}\n"
"\n"
"QMenuBar::item:selected { /* when selected using mouse or keyboard */\n"
"    background: #757575;\n"
"}"));
        menubar->setDefaultUp(false);
        menuMenu = new QMenu(menubar);
        menuMenu->setObjectName(QString::fromUtf8("menuMenu"));
        menuMenu->setContextMenuPolicy(Qt::CustomContextMenu);
        menuMenu->setAutoFillBackground(false);
        menuMenu->setStyleSheet(QString::fromUtf8("selection-background-color: rgb(117, 117, 117);\n"
"color: rgb(255, 255, 255);"));
        MainWindow->setMenuBar(menubar);

        menubar->addAction(menuMenu->menuAction());
        menuMenu->addAction(actionSalir);
        menuMenu->addAction(Conectar);
        menuMenu->addAction(Desconectar);
        menuMenu->addAction(Escaneo_de_puertos);

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
        Desconectar->setText(QCoreApplication::translate("MainWindow", "Desconectar", nullptr));
        Escaneo_de_puertos->setText(QCoreApplication::translate("MainWindow", "Escaneo de puertos", nullptr));
        aciertos->setText(QCoreApplication::translate("MainWindow", "  ACIERTOS", nullptr));
        errores->setText(QCoreApplication::translate("MainWindow", "  ERRORES", nullptr));
        fallos->setText(QCoreApplication::translate("MainWindow", "  FALLOS", nullptr));
        estado1->setText(QCoreApplication::translate("MainWindow", "Estado: ", nullptr));
        puntaje->setText(QCoreApplication::translate("MainWindow", "  PUNTAJE", nullptr));
        progressBar->setFormat(QCoreApplication::translate("MainWindow", "%v%", nullptr));
        record->setText(QCoreApplication::translate("MainWindow", "  RECORD", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "Reset record", nullptr));
        partida->setText(QCoreApplication::translate("MainWindow", "  PARTIDA", nullptr));
        menuMenu->setTitle(QCoreApplication::translate("MainWindow", "Menu", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
