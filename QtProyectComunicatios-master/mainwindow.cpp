#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myTimer = new QTimer(this);
    mySerial = new QSerialPort(this);
    mySettings = new SettingsDialog();
    myPaintBox = new QPaintBox(0,0,ui->widget);
    estado = new QLabel;
    estado->setText("Desconectado...");
    ui->statusbar->addWidget(estado);
    ui->actionDesconectar->setEnabled(false);
    estadoProtocolo=START;
    ui->pushButtonEnviar->setEnabled(false);
    estadoComandos=ALIVE;

    ///Conexión de eventos
    connect(mySerial,&QSerialPort::readyRead,this, &MainWindow::dataRecived );
    connect(myTimer, &QTimer::timeout,this, &MainWindow::myTimerOnTime);
    connect(ui->actionEscaneo_de_Puertos, &QAction::triggered, mySettings, &SettingsDialog::show);
    connect(ui->actionConectar,&QAction::triggered,this, &MainWindow::openSerialPort);
    connect(ui->actionConectar,&QAction::triggered,this, &MainWindow::fondo);
    connect(ui->actionDesconectar, &QAction::triggered, this, &MainWindow::closeSerialPort);
    connect(ui->actionSalir,&QAction::triggered,this,&MainWindow::close );

    myTimer->start(50);

}

MainWindow::~MainWindow()
{
    delete ui;
    delete myTimer;
    delete mySerial;
    delete estado;
    delete mySettings;
}

void MainWindow::openSerialPort()
{
    SettingsDialog::Settings p = mySettings->settings();
    mySerial->setPortName(p.name);
    mySerial->setBaudRate(p.baudRate);
    mySerial->setDataBits(p.dataBits);
    mySerial->setParity(p.parity);
    mySerial->setStopBits(p.stopBits);
    mySerial->setFlowControl(p.flowControl);
    mySerial->open(QSerialPort::ReadWrite);
    if(mySerial->isOpen()){
        ui->actionConectar->setEnabled(false);
        ui->actionDesconectar->setEnabled(true);
        ui->pushButtonEnviar->setEnabled(true);
        estado->setText(tr("Conectado a  %1 : %2, %3, %4, %5, %6  %7")
                                         .arg(p.name).arg(p.stringBaudRate).arg(p.stringDataBits)
                                         .arg(p.stringParity).arg(p.stringStopBits).arg(p.stringFlowControl).arg(p.fabricante));
    }
    else{
        QMessageBox::warning(this,"Menu Conectar","No se pudo abrir el puerto Serie!!!!");
    }


}

void MainWindow::closeSerialPort()
{
    if(mySerial->isOpen()){
        mySerial->close();
        ui->actionDesconectar->setEnabled(false);
        ui->actionConectar->setEnabled(true);
        estado->setText("Desconectado...");
        ui->pushButtonEnviar->setEnabled(false);
    }
    else{
         estado->setText("Desconectado...");
         ui->pushButtonEnviar->setEnabled(false);
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
}

void MainWindow::decodeData()
{
    QString str="", s;
    uint8_t indice;
    for(int a=1; a < rxData.index; a++){
        switch (rxData.payLoad[1]) {
            case ALIVE:
                str = "MBED-->PC ¡ESTOY VIVO!";
                break;
            case GETBUTTONSTATE:
                indice = rxData.payLoad[2];
                s.setNum(indice);
                state = rxData.payLoad[3];
                myWord.ui8[0]=rxData.payLoad[4];
                myWord.ui8[1]=rxData.payLoad[5];
                myWord.ui8[2]=rxData.payLoad[6];
                myWord.ui8[3]=rxData.payLoad[7];
                if(state == 0){
                    str = ("MBED-->PC DOWN "+ s +"");
                    boton[indice] = 1;
                    fondo();
                }
                if(state == 1){
                    str = "MBED-->PC UP "+ s +"";
                    boton[indice] = 0;
                    fondo();
                }
                break;
            case LEDPRUEBA:
                str = "MBED-->PC LED DE PRUEBA RECIBIDO";
                break;
            case STATELEDS:
                myWord.ui8[0] = rxData.payLoad[2];
                myWord.ui8[1] = rxData.payLoad[3];
                ledsAux = myWord.ui16[0];
                s.setNum(ledsAux);
                str = "MBED-->PC STATELEDS RECIBIDO    "+ s +"";

                break;

            default:
                str=((char *)rxData.payLoad);
                str= ("MBED-->PC *ID Invalido * (" + str + ")");
                break;
        }
    }
    ui->textBrowser->append(str);

}


void MainWindow::on_pushButtonEnviar_clicked()
{
    uint16_t auxleds=0;
    QString str="";
    txData.index=0;
    txData.payLoad[txData.index++]='U';
    txData.payLoad[txData.index++]='N';
    txData.payLoad[txData.index++]='E';
    txData.payLoad[txData.index++]='R';
    txData.payLoad[txData.index++]=0;
    txData.payLoad[txData.index++]=':';

    switch (estadoComandos) {
        case ALIVE:
            txData.payLoad[txData.index++]=ALIVE;
            txData.payLoad[NBYTES]=0x02;
            str = "Sending ALIVE  ";
            estadoComandos = GETBUTTONSTATE;
            break;
        case GETBUTTONSTATE:
            txData.payLoad[txData.index++]=GETBUTTONSTATE;
            txData.payLoad[NBYTES]=0x02;
            str = "Sending GETBUTTONSTATE  ";
            break;
        case LEDPRUEBA:
            txData.payLoad[txData.index++]=LEDPRUEBA;
            if(ui->ledPruebaR->isChecked()){
                auxleds |= 1 <<3;
            }else{
                auxleds &= ~(1<<3);
            }
            if(ui->ledPruebaA->isChecked()){
                auxleds |= 1 <<2;
            }else{
                auxleds &= ~(1<<2);
            }
            if(ui->ledPruebaAm->isChecked()){
                auxleds |= 1 <<1;
            }else{
                auxleds &= ~(1<<1);
            }
            if(ui->ledPruebaV->isChecked()){
                auxleds |= 1 <<0;
            }else{
                auxleds &= ~(1<<0);
            }
            myWord.ui16[0] = auxleds;
            txData.payLoad[txData.index++] = myWord.ui8[0];
            txData.payLoad[txData.index++] = myWord.ui8[1];
            txData.payLoad[NBYTES]=0x04;
            break;
        case ANGULO:
            txData.payLoad[txData.index++] = ANGULO;
            txData.payLoad[txData.index++] = angulo;
            txData.payLoad[NBYTES] = 0x03;
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
    ui->textBrowser->append("PC-->MBED (" + str + ")");

}

void MainWindow::on_comboBox_currentIndexChanged(int index)
{
    switch (index) {
        case 1:
            estadoComandos=ALIVE;
        break;
        case 2:
            estadoComandos=GETBUTTONSTATE;
        break;
        case 3:
            estadoComandos=ANGULO;
        break;
    default:
        break;
    }
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

        if(boton[i]){
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

        leds = 0;
    }

    myPaintBox->update();
}

//**************************************************************************//
            //*******************BOTONES*******************//

void MainWindow::on_ledPruebaR_toggled(bool checked)
{
    if(checked){
        estadoComandos = LEDPRUEBA;
        fondo();
        on_pushButtonEnviar_clicked();
    }else{
        estadoComandos = LEDPRUEBA;
        fondo();
        on_pushButtonEnviar_clicked();
    }
}

void MainWindow::on_ledPruebaA_toggled(bool checked)
{
    if(checked){
        estadoComandos = LEDPRUEBA;
        fondo();
        on_pushButtonEnviar_clicked();
    }else{
        estadoComandos = LEDPRUEBA;
        fondo();
        on_pushButtonEnviar_clicked();
    }
}

void MainWindow::on_ledPruebaAm_toggled(bool checked)
{
    if(checked){
        estadoComandos = LEDPRUEBA;
        fondo();
        on_pushButtonEnviar_clicked();
    }else{
        estadoComandos = LEDPRUEBA;
        fondo();
        on_pushButtonEnviar_clicked();
    }
}

void MainWindow::on_ledPruebaV_toggled(bool checked)
{
    if(checked){
        estadoComandos = LEDPRUEBA;
        fondo();
        on_pushButtonEnviar_clicked();
    }else{
        estadoComandos = LEDPRUEBA;
        fondo();
        on_pushButtonEnviar_clicked();
    }
}

