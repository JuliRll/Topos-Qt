#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include <QLabel>
#include <qpaintbox.h>
#include <QMessageBox>
#include <QDateTime>
#include "settings.h"

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

    void Send();

    void paintLeds();

    void paintButtons();

    void juego();
    void on_pushButton_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *mySerial;
    QTimer *myTimer;
    QTimer *gameTimer;
    QPaintBox *myPaintBox;
    QLabel *estado;
    SettingsDialog *settings;

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
        BUTTONEVENT=0xFA,
        GETBUTTONS = 0xFD,
        GETLEDS=0xFB,
        SETLEDS=0xFC,
    }_eID;

    _eID estadoComandos;

    typedef enum{
        BEGIN,
        BUTTONS,
        INTRO,
        PLAY,
        END,
        DEFAULT,
    }_eGame;

    _eGame estadoJuego;

    uint8_t state;

    int8_t angulo = 0;

    typedef struct{
        uint8_t timeOut;
        uint8_t cheksum;
        uint8_t payLoad[50];
        uint8_t nBytes;
        uint8_t index;
    }_sDatos ;

    _sDatos rxData, txData;



    short checked = 0;
    uint16_t boton[4] = {0,0,0,0};
    uint8_t indice, partidaN = 1;
    uint32_t contTime, timeLeds[4], randsOut[4];
    uint8_t indiceLeds = 15;
    uint8_t auxState = 0;
    int32_t fallos = 0, aciertos = 0, errores = 0, puntaje = 0, record = -400;
    uint16_t ledsAux,buttonsAux, auxMask = 0;
    uint32_t timeRead = 0;
    uint32_t timeManager = 40;

    typedef struct {
        bool b1: 1;
        bool b2: 1;
        bool b3: 1;
        bool b4: 1;
        bool b5: 1;
        bool b6: 1;
        bool b7: 1;
    }Flags;

    Flags flags, flags2;

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
#endif
