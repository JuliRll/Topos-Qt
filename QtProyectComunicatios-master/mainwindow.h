#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QtSerialPort/QSerialPort>
#include <QTimer>
#include <QLabel>
#include <qpaintbox.h>
#include <QMessageBox>

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

    void fondo();

    void juego();

    void on_pushButton_clicked();

    void on_pushButton_2_clicked();

    void on_pushButton_3_clicked();

private:
    Ui::MainWindow *ui;
    QSerialPort *mySerial;
    QTimer *myTimer;
    QPaintBox *myPaintBox;
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
        GETBUTTONS = 0xFD,
        GETLEDS=0xFB,
        SETLEDS=0xFC,
    }_eID;

    _eID estadoComandos;

    typedef enum{
        WAIT,
        INTRO,
        PLAY,
    }_eGame;

    _eGame estadoJuego;

    uint16_t state, globalCount = 0;

    int8_t angulo = 0;

    typedef struct{
        uint8_t timeOut;
        uint8_t cheksum;
        uint8_t payLoad[50];
        uint8_t nBytes;
        uint8_t index;
    }_sDatos ;

    _sDatos rxData, txData;

    uint8_t boton[4] = {0,0,0,0};
    uint8_t num[6] = {1,2,4,8,0,15};
    uint8_t auxState = 1,auxNum = 0;
    uint16_t ledsAux,buttonsAux;
    uint32_t timeRead = 0;
    int enabled = 0;

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
