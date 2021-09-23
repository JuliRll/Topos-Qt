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
    estado->setText("Desconectado............");
    ui->statusbar->addWidget(estado);
    ui->actionDesconectar->setEnabled(false);
    //ui->widget->setVisible(false);
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
//    delete paint;
//    delete myTimer;
//    delete mySerial;
//    delete estado;
//    delete mySettings;
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
        estado->setText("Desconectado................");
        ui->pushButtonEnviar->setEnabled(false);
    }
    else{
         estado->setText("Desconectado................");
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

    ui->textBrowser->append("MBED-->PC (" + str + ")");

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
                if (incomingBuffer[i]=='N')
                   estadoProtocolo=HEADER_2;
                else{
                    i--;
                    estadoProtocolo=START;
                }
                break;
            case HEADER_2:
                if (incomingBuffer[i]=='E')
                    estadoProtocolo=HEADER_3;
                else{
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
                        ui->textBrowser->append("MBED-->PC DECODE-DATA");
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
    QString str="";
    for(int a=1; a < rxData.index; a++){
        switch (rxData.payLoad[1]) {
            case ALIVE:
                str = "MBED-->PC ¡ESTOY VIVO!";
                break;
            case GETBUTTONSTATE:
                str = "MBED-->PC ESTADO DE LOS BOTONES";
                myWord.ui8[0]=rxData.payLoad[2];
                myWord.ui8[1]=rxData.payLoad[3];
//                fondo();
                break;
            case LEDPRUEBA:
                str = "MBED-->PC LED DE PRUEBA ENCENDIDO  ";
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
            break;
        case GETBUTTONSTATE:
            txData.payLoad[txData.index++]=GETBUTTONSTATE;
            txData.payLoad[NBYTES]=0x02;
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
    default:
        break;
    }
}

void MainWindow::fondo(){

    QPen pen;
    int16_t posx = 0,posy = 0;
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
        switch(nBoton[i]){
            case 1:
                pen.setWidth(1);
                paint.setPen(pen);
                paint.setBrush(Qt::red);
                paint.drawEllipse(posx,posy,radio,radio);
            break;
            case 2:
                pen.setWidth(1);
                paint.setPen(pen);
                paint.setBrush(Qt::yellow);
                paint.drawEllipse(posx,posy,radio,radio);
            break;
            case 3:
                pen.setWidth(1);
                paint.setPen(pen);
                paint.setBrush(Qt::blue);
                paint.drawEllipse(posx,posy,radio,radio);
            break;
            case 4:
                pen.setWidth(1);
                paint.setPen(pen);
                paint.setBrush(Qt::green);
                paint.drawEllipse(posx,posy,radio,radio);
            break;
            default:
                pen.setWidth(1);
                paint.setPen(pen);
                paint.setBrush(Qt::gray);
                paint.drawEllipse(posx,posy,radio,radio);
            break;
        }

        pen.setWidth(3);
        paint.setPen(pen);
        paint.setBrush(Qt::gray);
        paint.drawRect(posx-10,posy+60,lado,lado);
        paint.setBrush(Qt::black);
        paint.drawEllipse(posx+5,posy+75,radio-10,radio-10);
        posx +=172;
    }

    myPaintBox->update();
}

//**************************************************************************//
            //*******************BOTNOES*******************//

void MainWindow::on_ledPruebaR_toggled(bool checked)
{
        if(checked){
            estadoComandos = LEDPRUEBA;
            nBoton[0] = 1;
            fondo();
            on_pushButtonEnviar_clicked();
        }else{
            estadoComandos = LEDPRUEBA;
            nBoton[0] = 0;
            fondo();
            on_pushButtonEnviar_clicked();
        }
}

void MainWindow::on_ledPruebaA_toggled(bool checked)
{
    if(checked){
        estadoComandos = LEDPRUEBA;
        nBoton[1] = 2;
        fondo();
        on_pushButtonEnviar_clicked();
    }else{
        estadoComandos = LEDPRUEBA;
        nBoton[1] = 0;
        fondo();
        on_pushButtonEnviar_clicked();
    }
}

void MainWindow::on_ledPruebaAm_toggled(bool checked)
{
    if(checked){
        estadoComandos = LEDPRUEBA;
        nBoton[2] = 3;
        fondo();
        on_pushButtonEnviar_clicked();
    }else{
        estadoComandos = LEDPRUEBA;
        nBoton[2] = 0;
        fondo();
        on_pushButtonEnviar_clicked();
    }
}

void MainWindow::on_ledPruebaV_toggled(bool checked)
{
    if(checked){
        estadoComandos = LEDPRUEBA;
        nBoton[3] = 4;
        fondo();
        on_pushButtonEnviar_clicked();
    }else{
        estadoComandos = LEDPRUEBA;
        nBoton[3] = 0;
        fondo();
        on_pushButtonEnviar_clicked();
    }
}

