#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include <QLabel>
#include "settingsdialog.h"
#include "qpaintbox.h"

QT_BEGIN_NAMESPACE
namespace Ui { class MainWindow; }
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

private slots:
    void openSerialPort();

    void closeSerialPort();

    void myTimerOnTime();

    void dataRecived();

    void decodeData();

    void on_pushButtonEnviar_clicked();

    void on_comboBox_currentIndexChanged(int index);

    void fondo();

    void on_ledPruebaR_toggled(bool checked);
    void on_ledPruebaA_toggled(bool checked);
    void on_ledPruebaAm_toggled(bool checked);
    void on_ledPruebaV_toggled(bool checked);

private:
    Ui::MainWindow *ui;
    QSerialPort *mySerial;
    QTimer *myTimer;
    QPaintBox *myPaintBox;
    SettingsDialog *mySettings;
    QLabel *estado;

    typedef enum{
        START,
        HEADER_1,
        HEADER_2,
        HEADER_3,
        NBYTES,
        TOKEN,
        PAYLOAD
    }_eProtocolo;

    _eProtocolo estadoProtocolo;

    typedef enum{
        ALIVE=0xF0,
        GETBUTTONSTATE=0xF1,
        LEDPRUEBA=0xF2,
    }_eID;

    _eID estadoComandos;

    uint16_t nBoton[4];

    typedef struct{
        uint8_t timeOut;
        uint8_t cheksum;
        uint8_t payLoad[50];
        uint8_t nBytes;
        uint8_t index;
    }_sDatos ;

    _sDatos rxData, txData;

    typedef union {
        float f32;
        int i32;
        unsigned int ui32;
        unsigned short ui16[2];
        short i16[2];
        uint8_t ui8[4];
        char chr[4];
        unsigned char uchr[4];
    }_udat;

    _udat myWord;

};
#endif // MAINWINDOW_H
