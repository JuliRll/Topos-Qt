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

//    void manejadorLed(uint8_t numLed, uint8_t ledState);


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
        PAYLOAD,
        BUTTON_DOWN,
        BUTTON_UP
    }_eProtocolo;

    _eProtocolo estadoProtocolo;

    typedef enum{
        ALIVE=0xF0,
        GETBUTTONSTATE=0xFA,
        STATELEDS=0xFB,
        SETLEDS=0xFC,
        ANGULO = 0xA2,
    }_eID;

    _eID estadoComandos;

    uint16_t state;

    int8_t angulo = 0;

    typedef struct{
        uint8_t timeOut;
        uint8_t cheksum;
        uint8_t payLoad[50];
        uint8_t nBytes;
        uint8_t index;
    }_sDatos ;

    _sDatos rxData, txData;

    uint8_t boton[4];
    uint8_t num[4] = {1,2,4,8};
    uint8_t auxstate = 1;
    uint16_t ledsAux;

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
