#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myTimer = new QTimer(this);

    myPaintBox = new QPaintBox(0,0,ui->widget);
    estado = new QLabel;
    estado->setText("Desconectado...");
    ui->statusbar->addWidget(estado);
    ui->estado1->setText("Estado: Desconectado");
    ui->puntaje_2->display(2);
    estadoProtocolo=START;
    estadoComandos=ALIVE;
    estadoJuego = WAIT;

    mySerial = new QSerialPort(this);
    mySerial->setPortName("COM5");
    mySerial->setBaudRate(115200);
    mySerial->setDataBits(QSerialPort::Data8);
    mySerial->setParity(QSerialPort::NoParity);
    mySerial->setFlowControl(QSerialPort::NoFlowControl);
    connect(mySerial,&QSerialPort::readyRead,this, &MainWindow::dataRecived);

    connect(myTimer, &QTimer::timeout,this, &MainWindow::myTimerOnTime);
    connect(ui->Conectar,&QAction::triggered,this, &MainWindow::openSerialPort);
    connect(ui->Conectar,&QAction::triggered,this, &MainWindow::fondo);
    connect(ui->Conectar,&QAction::triggered,this, &MainWindow::Send);
    connect(ui->actionSalir,&QAction::triggered,this,&MainWindow::close );

    myTimer->start(50);


}

MainWindow::~MainWindow()
{
    delete ui;
    delete myTimer;
    delete mySerial;
    delete estado;
}

void MainWindow::openSerialPort()
{
    mySerial->open(QSerialPort::ReadWrite);
    if(mySerial->isOpen()){
        estado->setText("Conectado");
        ui->estado1->setText("Estado: Conectado");
    }
    else{
        QMessageBox::warning(this,"Menu Conectar","No se pudo abrir el puerto Serie");
    }
}

void MainWindow::closeSerialPort()
{
    if(mySerial->isOpen()){
        mySerial->close();
        ui->actionDesconectar->setEnabled(false);
        ui->actionConectar->setEnabled(true);
        estado->setText("Desconectado...");
    }
    else{
         estado->setText("Desconectado...");
    }

}

void MainWindow::myTimerOnTime()
{
    if(rxData.timeOut!=0){
        rxData.timeOut--;
    }else{
        estadoProtocolo=START;
    }
}

void MainWindow::dataRecived()
{
    unsigned char *incomingBuffer;
    int count;

    count = mySerial->bytesAvailable();

    if(count<=0)
        return;

    incomingBuffer = new unsigned char[count];

    mySerial->read((char *)incomingBuffer,count);

    QString str="";

    for(int i=0; i<=count; i++){
        if(isalnum(incomingBuffer[i]))
            str = str + QString("%1").arg((char)incomingBuffer[i]);
        else
            str = str +"{" + QString("%1").arg(incomingBuffer[i],2,16,QChar('0')) + "}";
    }

    rxData.timeOut=5;

    for(int i=0;i<count; i++){
        switch (estadoProtocolo) {
            case START:
                if (incomingBuffer[i]=='U'){
                    estadoProtocolo=HEADER_1;
                    rxData.cheksum=0;
                }
                break;
            case HEADER_1:
                if (incomingBuffer[i]=='N'){
                    estadoProtocolo=HEADER_2;
                }else{
                    i--;
                    estadoProtocolo=START;
                }
                break;
            case HEADER_2:
                if (incomingBuffer[i]=='E'){
                    estadoProtocolo=HEADER_3;
                }else{
                    i--;
                   estadoProtocolo=START;
                }
                break;
        case HEADER_3:
            if (incomingBuffer[i]=='R')
                estadoProtocolo=NBYTES;
            else{
                i--;
               estadoProtocolo=START;
            }
            break;
            case NBYTES:
                rxData.nBytes=incomingBuffer[i];
                estadoProtocolo=TOKEN;
                break;
            case TOKEN:
                if (incomingBuffer[i]==':'){
                    estadoProtocolo=PAYLOAD;
                    rxData.cheksum='U'^'N'^'E'^'R'^ rxData.nBytes^':';
                    rxData.payLoad[0]=rxData.nBytes;
                    rxData.index=1;
                }
                else{
                    i--;
                    estadoProtocolo=START;
                }
                break;
            case PAYLOAD:
                if (rxData.nBytes>1){
                    rxData.payLoad[rxData.index++]=incomingBuffer[i];
                    rxData.cheksum^=incomingBuffer[i];
                }
                rxData.nBytes--;
                if(rxData.nBytes==0){
                    estadoProtocolo=START;
                    if(rxData.cheksum==incomingBuffer[i]){
                        decodeData();
                    }
                }
                break;
            default:
                estadoProtocolo=START;
                break;
        }
    }
    delete [] incomingBuffer;
    if((timeRead > 1000) && (enabled == 1)){
        enabled = 0;
        return juego();
        timeRead = 0;
    }
}

void MainWindow::decodeData()
{
    QString str="", s;
    uint8_t indice;

    for(int a=1; a < rxData.index; a++){
        switch (rxData.payLoad[1]) {
            case ALIVE:
                str = "MBED-->PC ¡ESTOY VIVO!";
                ui->textBrowser->setTextColor(Qt::red);
                break;
            case GETBUTTONSTATE:
                indice = rxData.payLoad[2];
                s.setNum(indice);
                state = rxData.payLoad[3];
                myWord.ui8[0]=rxData.payLoad[4];
                myWord.ui8[1]=rxData.payLoad[5];
                myWord.ui8[2]=rxData.payLoad[6];
                myWord.ui8[3]=rxData.payLoad[7];
                timeRead = myWord.ui32;
                if(state == 0){
                    str = "MBED-->PC DOWN";
                    ui->textBrowser->setTextColor(Qt::darkYellow);
                    boton[indice] = 1;
                    fondo();
                }
                if(state == 1){
                    str = "MBED-->PC UP";
                    ui->textBrowser->setTextColor(Qt::darkYellow);
                    boton[indice] = 0;
                    fondo();
                }
                if(timeRead > 1000){
                    enabled = 1;
                    s.setNum(timeRead);
                    str = str + "TIME "+ s +"";
                }
                break;
            case GETBUTTONS:
                myWord.ui8[0] = rxData.payLoad[2];
                myWord.ui8[1] = rxData.payLoad[3];
                buttonsAux = myWord.ui16[0];
                s.setNum(buttonsAux);
                str = "MBED-->PC GETBUTTONS RECIBIDO   "+ s +" ";
                ui->textBrowser->setTextColor(Qt::darkCyan);
                break;
            case GETLEDS:
                myWord.ui8[0] = rxData.payLoad[2];
                myWord.ui8[1] = rxData.payLoad[3];
                ledsAux = myWord.ui16[0];
                s.setNum(ledsAux);
                str = "MBED-->PC GETLEDS RECIBIDO    "+ s +"";
                ui->textBrowser->setTextColor(Qt::darkCyan);
                fondo();
                break;
            case SETLEDS:
                str = "MBED-->PC SETLEDS RECIBIDO";
                ui->textBrowser->setTextColor(Qt::darkCyan);
            break;

            default:
                str=((char *)rxData.payLoad);
                str= ("MBED-->PC *ID Invalido * (" + str + ")");
                ui->textBrowser->setTextColor(Qt::darkRed);
                break;
        }
    }
    ui->textBrowser->append(str);
}

void MainWindow::Send()
{
    QString str="";
    txData.index=0;
    txData.payLoad[txData.index++]='U';
    txData.payLoad[txData.index++]='N';
    txData.payLoad[txData.index++]='E';
    txData.payLoad[txData.index++]='R';
    txData.payLoad[txData.index++]=0;
    txData.payLoad[txData.index++]=':';

    switch (estadoComandos){
        case ALIVE:
            txData.payLoad[txData.index++]=ALIVE;
            txData.payLoad[NBYTES]=0x02;
            str = "Sending ALIVE  ";
            break;
        case GETBUTTONSTATE:
            txData.payLoad[txData.index++]=GETBUTTONSTATE;
            txData.payLoad[NBYTES]=0x02;
            str = "Sending GETBUTTONSTATE  ";
            break;
        case GETBUTTONS:
            txData.payLoad[txData.index++] = GETBUTTONS;
            txData.payLoad[NBYTES] = 0x02;
            str = "Sending GETBUTTONS";
            break;
        case SETLEDS:
            txData.payLoad[txData.index++]=SETLEDS;
            txData.payLoad[txData.index++] = num[auxNum];
            txData.payLoad[txData.index++] = auxState;
            txData.payLoad[NBYTES]=0x04;
            str = "Sending SETLEDS ";
            fondo();
            break;
        case GETLEDS:
            txData.payLoad[txData.index++] = GETLEDS;
            txData.payLoad[NBYTES] = 0x02;
            str = "Sending GETLEDS ";
            break;
        default:
            break;
    }
   txData.cheksum=0;
   for(int a=0 ;a<txData.index;a++)
       txData.cheksum ^= txData.payLoad[a];
    txData.payLoad[txData.index]=txData.cheksum;
    if(mySerial->isWritable()){
        mySerial->write((char *)txData.payLoad,txData.payLoad[NBYTES]+6);
    }


    for(int i=0; i<=txData.index; i++){
        if(isalnum(txData.payLoad[i]))
            str = str + QString("%1").arg((char)txData.payLoad[i]);
        else
            str = str +"{" + QString("%1").arg(txData.payLoad[i],2,16,QChar('0')) + "}";
    }
    ui->textBrowser->setTextColor(Qt::darkMagenta);
    ui->textBrowser->append("PC-->MBED (" + str + ")");
}

void MainWindow::fondo(){

    QPen pen;
    int16_t posx = 0,posy = 0, leds = 0;
    uint8_t radio = 30,lado = 50;
    QColor selfColor;
    QPainter paint(myPaintBox->getCanvas());
    selfColor.setRgb(60, 55, 120,255);
    myPaintBox->getCanvas()->fill(selfColor);
    posx = 172;
    posy = 40;
    pen.setColor(Qt::black);
    paint.setPen(pen);

    for(int i=0;i<4;i++){
        if((leds|=1<<i) & ledsAux){
            pen.setWidth(1);
            paint.setPen(pen);
            switch(i){
                case 0:
                    paint.setBrush(Qt::magenta);
                break;
                case 1:
                    paint.setBrush(Qt::red);
                break;
                case 2:
                    paint.setBrush(Qt::blue);
                break;
                case 3:
                    paint.setBrush(Qt::green);
                break;
                default:
                    break;
            }
            paint.drawEllipse(posx,posy,radio,radio);

        }else{
            pen.setWidth(1);
            paint.setPen(pen);
            paint.setBrush(Qt::gray);
            paint.drawEllipse(posx,posy,radio,radio);
        }

        leds = 0;

        if(boton[i] == 1){
            pen.setWidth(3);
            paint.setPen(pen);
            paint.setBrush(Qt::darkGray);
            paint.drawRect(posx-10,posy+60,lado,lado);
            paint.setBrush(Qt::black);
            paint.drawEllipse(posx+5,posy+75,radio-10,radio-10);
            posx += 172;
        }else{
            pen.setWidth(3);
            paint.setPen(pen);
            paint.setBrush(Qt::gray);
            paint.drawRect(posx-10,posy+60,lado,lado);
            paint.setBrush(Qt::black);
            paint.drawEllipse(posx+5,posy+75,radio-10,radio-10);
            posx += 172;
        }
    }

    myPaintBox->update();
}

void MainWindow::juego()
{
    while(true){
        switch (estadoJuego) {
        case WAIT:
            ui->textBrowser->setTextColor(Qt::darkBlue);
            ui->estado1->setText("Estado: WAIT");
            auxNum = 5;
            estadoComandos = SETLEDS;
            Send();
            estadoComandos = GETLEDS;
            Send();
            estadoJuego = INTRO;
        case INTRO:
            ui->textBrowser->setTextColor(Qt::darkBlue);
            ui->estado1->setText("Estado: INTRO");
            break;
        case PLAY:
            ui->textBrowser->setTextColor(Qt::darkBlue);
            ui->estado1->setText("Estado: PLAY");
            break;

        default:
            break;
        }
    }

}



void MainWindow::on_pushButton_clicked()
{
   estadoComandos = SETLEDS;
   Send();
}

void MainWindow::on_pushButton_2_clicked()
{
    estadoComandos = GETLEDS;
    Send();
}

void MainWindow::on_pushButton_3_clicked()
{
    estadoComandos = GETBUTTONS;
    Send();
}


