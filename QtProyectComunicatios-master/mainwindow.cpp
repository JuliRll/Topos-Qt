#include "mainwindow.h"
#include "ui_mainwindow.h"
#include <QMessageBox>
#define MAXTIMEOUTSIDE 200
#define MAXTIMEINSIDE 600
#define MINTIMEOUTSIDE 50
#define MINTIMEINSIDE 100

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    myTimer = new QTimer(this);
    myPaintBox = new QPaintBox(0,0,ui->widget);
    estado = new QLabel;
    gameTimer = new QTimer();
    settings = new SettingsDialog();
    ui->estado1->setText("Estado: Desconectado");
    estadoProtocolo = START;
    estadoJuego = BEGIN;
    srand(time(NULL));
    mySerial = new QSerialPort(this);

    connect(mySerial,&QSerialPort::readyRead,this, &MainWindow::dataRecived);
    connect(myTimer, &QTimer::timeout,this, &MainWindow::myTimerOnTime);
    connect(ui->Escaneo_de_puertos, &QAction::triggered, settings, &SettingsDialog::show);
    connect(ui->Conectar,&QAction::triggered,this, &MainWindow::openSerialPort);
    connect(ui->Desconectar,&QAction::triggered,this,&MainWindow::closeSerialPort);
    connect(ui->Conectar,&QAction::triggered,this,&MainWindow::juego);
    connect(gameTimer, &QTimer::timeout,this, &MainWindow::juego);
    connect(ui->actionSalir,&QAction::triggered,this,&MainWindow::close );

    myTimer->start(50);
    gameTimer->start(10);

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
    SettingsDialog::Settings p = settings->settings();
    mySerial->setPortName(p.name);
    mySerial->setBaudRate(p.baudRate);
    mySerial->setDataBits(p.dataBits);
    mySerial->setParity(p.parity);
    mySerial->setStopBits(p.stopBits);
    mySerial->setFlowControl(p.flowControl);
    mySerial->open(QSerialPort::ReadWrite);
    if(mySerial->isOpen()){
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
        myPaintBox->getCanvas()->fill(Qt::black);
        myPaintBox->update();
    }
    else{
        QMessageBox::warning(this,"Menu Conectar","No se pudo cerrar el puerto Serie");
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
    QColor selfColor;
    switch (rxData.payLoad[1]) {
        case ALIVE:
            selfColor.setRgb(6, 33, 77,255);
            myPaintBox->getCanvas()->fill(selfColor);
            myPaintBox->update();
            checked = 1;
            break;
        case BUTTONEVENT:
            indice = rxData.payLoad[2];
            state = rxData.payLoad[3];
            myWord.ui8[0]=rxData.payLoad[4];
            myWord.ui8[1]=rxData.payLoad[5];
            myWord.ui8[2]=rxData.payLoad[6];
            myWord.ui8[3]=rxData.payLoad[7];
            timeRead = myWord.ui32;
            if(state == 0){
                boton[indice] = 1;
                flags2.b1 = 1;
                flags2.b2 = 1;
                flags2.b3 = 1;
                flags2.b4 = 1;
                paintButtons();
            }
            if(state == 1){
                boton[indice] = 0;
                paintButtons();
            }
            checked = 2;
            break;
        case GETBUTTONS:
            myWord.ui8[0] = rxData.payLoad[2];
            myWord.ui8[1] = rxData.payLoad[3];
            buttonsAux = myWord.ui16[0];
            break;
        case GETLEDS:
            myWord.ui8[0] = rxData.payLoad[2];
            myWord.ui8[1] = rxData.payLoad[3];
            ledsAux = myWord.ui16[0];
            paintLeds();
            break;
        case SETLEDS:
        break;
        default:
            ui->estado1->setText("ID INVALIDO!!");
            break;
    }
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
            break;
        case BUTTONEVENT:
            txData.payLoad[txData.index++]=BUTTONEVENT;
            txData.payLoad[NBYTES]=0x02;
            break;
        case GETBUTTONS:
            txData.payLoad[txData.index++] = GETBUTTONS;
            txData.payLoad[NBYTES] = 0x02;
            break;
        case SETLEDS:
            txData.payLoad[txData.index++]=SETLEDS;
            txData.payLoad[txData.index++] = indiceLeds;
            txData.payLoad[txData.index++] = auxState;
            txData.payLoad[NBYTES]=0x04;
            break;
        case GETLEDS:
            txData.payLoad[txData.index++] = GETLEDS;
            txData.payLoad[NBYTES] = 0x02;
            paintLeds();
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
}

void MainWindow::paintLeds(){

    QPen pen;
    int16_t posx = 0,x ,posy = 0, width, height;
    uint8_t radio = 30;
    QPainter paint(myPaintBox->getCanvas());
    width = myPaintBox->width();
    height = myPaintBox->height();
    posx = (width/5)-(radio/2);
    x = posx+(radio/2);
    posy = (height/4);
    pen.setColor(Qt::black);
    paint.setPen(pen);
    paint.setRenderHint(QPainter::Antialiasing);

    for(int i=0;i<4;i++){
        auxMask = 0;
        if((auxMask|=1<<i) & ledsAux){
            pen.setWidth(2);
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
            pen.setWidth(2);
            paint.setPen(pen);
            paint.setBrush(Qt::gray);
            paint.drawEllipse(posx,posy,radio,radio);
        }
        posx += x;
    }
    myPaintBox->update();
}

void MainWindow::paintButtons(){
    QPen pen;
    int16_t posx = 0,x ,posy = 0, width, height;
    uint8_t radio = 20,lado = 50;
    QPainter paint(myPaintBox->getCanvas());
    width = myPaintBox->width();
    height = myPaintBox->height();
    posx = (width/5)-(lado/2);
    x = posx+(lado/2);
    posy = (height/4)*2;
    pen.setColor(Qt::black);
    paint.setPen(pen);
    paint.setRenderHint(QPainter::Antialiasing);

    for(int i=0;i<4;i++){
        auxMask = 0;
        if(boton[i] == 1){
            pen.setWidth(3);
            paint.setPen(pen);
            paint.setBrush(Qt::darkGray);
            paint.drawRect(posx,posy,lado,lado);
            paint.setBrush(Qt::black);
            paint.drawEllipse(posx+15,posy+15,radio,radio);
        }else{
            pen.setWidth(3);
            paint.setPen(pen);
            paint.setBrush(Qt::gray);
            paint.drawRect(posx,posy,lado,lado);
            paint.setBrush(Qt::black);
            paint.drawEllipse(posx+15,posy+15,radio,radio);
        }
        posx += x;
    }

    myPaintBox->update();
}


void MainWindow::juego()
{
    switch (estadoJuego) {
        case BEGIN:
            if(checked == 0){
                estadoComandos = ALIVE;
                Send();
            }
            if(checked == 1){
                estadoComandos = BUTTONEVENT;
                Send();
            }
            if(checked == 2){
                estadoComandos = GETLEDS;
                Send();
                estadoJuego = BUTTONS;
                ui->estado1->setText("Estado: BUTTONS");
            }
            
            break;
        case BUTTONS:
            if(timeRead >= 1000 && state == 1){
                estadoComandos = GETBUTTONS;
                Send();
                if(buttonsAux == 15){
                    estadoJuego = INTRO;
                    ui->estado1->setText("Estado: INTRO");
                    ui->partida_2->display(partidaN);
                    aciertos = 0;
                    puntaje = 0;
                    errores = 0;
                    fallos = 0;
                    ui->aciertos_2->display(aciertos);
                    ui->errores_2->display(errores);
                    ui->fallos_2->display(fallos);
                    ui->puntaje_2->display(puntaje);
                }
            }
            break;
        case INTRO:
            timeManager++;
            if((timeManager - contTime) >= 30){
                contTime = timeManager;

                auxState = !auxState;
                estadoComandos = SETLEDS;
                Send();
                estadoComandos = GETLEDS;
                Send();
                if(contTime >= 180){
                    estadoJuego = PLAY;
                    timeManager = 0;
                    contTime = 0;
                    auxState = 0;
                    timeRead = 0;
                    for(int i=0;i<=4;i++){
                        timeLeds[i] = (rand()%(MAXTIMEINSIDE-MINTIMEINSIDE))+MINTIMEINSIDE;
                    }
                    ui->estado1->setText("Estado: PLAY");
                    ui->progressBar->setValue(0);
                }
            }
            break;

        case PLAY:
            timeManager++;
            ui->progressBar->setValue(timeManager);
            if(timeManager >= 3000){
                timeManager = 40;
                indiceLeds = 15;
                auxState = 0;
                estadoJuego = END;
                break;
            }
            //LED 0
            if(timeManager >= timeLeds[0]){
                if(flags.b1 == 0){
                    randsOut[0] = (rand()%(MAXTIMEOUTSIDE - MINTIMEOUTSIDE))+MINTIMEOUTSIDE;
                    timeLeds[0] += randsOut[0];
                    auxState = 1;
                }
                if(flags.b1 == 1){
                    timeLeds[0] += (rand()%(MAXTIMEINSIDE-MINTIMEINSIDE))+MINTIMEINSIDE;
                    auxState = 0;
                    if(flags2.b1 == 1){
                        ui->fallos_2->display(fallos++);
                        puntaje -= 10;
                        ui->puntaje_2->display(puntaje);
                    }
                }
                indiceLeds = 1;
                estadoComandos = SETLEDS;
                Send();
                estadoComandos = GETLEDS;
                Send();
                flags.b1 = !flags.b1;
            }
            //LED 1
            if(timeManager >= timeLeds[1]){
                if(flags.b2 == 0){
                    randsOut[1] = (rand()%(MAXTIMEOUTSIDE - MINTIMEOUTSIDE))+MINTIMEOUTSIDE;
                    timeLeds[1] += randsOut[1];
                    auxState = 1;
                }
                if(flags.b2 == 1){
                    timeLeds[1] += (rand()%(MAXTIMEINSIDE-MINTIMEINSIDE))+MINTIMEINSIDE;
                    auxState = 0;
                    if(flags2.b2 == 1){
                        ui->fallos_2->display(fallos++);
                        puntaje -= 10;
                        ui->puntaje_2->display(puntaje);
                    }
                }
                indiceLeds = 2;
                estadoComandos = SETLEDS;
                Send();
                estadoComandos = GETLEDS;
                Send();
                flags.b2 = !flags.b2;
            }
            //LED 2
            if(timeManager >= timeLeds[2]){
                if(flags.b3 == 0){
                    randsOut[2] = (rand()%(MAXTIMEOUTSIDE - MINTIMEOUTSIDE))+MINTIMEOUTSIDE;
                    timeLeds[2] += randsOut[2];
                    auxState = 1;
                }
                if(flags.b3 == 1){
                    timeLeds[2] += (rand()%(MAXTIMEINSIDE-MINTIMEINSIDE))+MINTIMEINSIDE;
                    auxState = 0;
                    if(flags2.b3 == 1){
                        ui->fallos_2->display(fallos++);
                        puntaje -= 10;
                        ui->puntaje_2->display(puntaje);
                    }
                }
                indiceLeds = 4;
                estadoComandos = SETLEDS;
                Send();
                estadoComandos = GETLEDS;
                Send();
                flags.b3 = !flags.b3;
            }
            //LED 3
            if(timeManager >= timeLeds[3]){
                if(flags.b4 == 0){
                    randsOut[3] = (rand()%(MAXTIMEOUTSIDE - MINTIMEOUTSIDE))+MINTIMEOUTSIDE;
                    timeLeds[3] += randsOut[3];
                    auxState = 1;
                }
                if(flags.b4 == 1){
                    timeLeds[3] += (rand()%(MAXTIMEINSIDE-MINTIMEINSIDE))+MINTIMEINSIDE;
                    auxState = 0;
                    if(flags2.b4 == 1){
                        ui->fallos_2->display(fallos++);
                        puntaje -= 10;
                        ui->puntaje_2->display(puntaje);
                    }
                }
                indiceLeds = 8;
                estadoComandos = SETLEDS;
                Send();
                estadoComandos = GETLEDS;
                Send();
                flags.b4 = !flags.b4;
            }

            if(state == 0){
                switch (indice){
                    case 0:
                        if(flags2.b1 == 1){
                            auxMask |= 1<<0;
                            if(auxMask & ledsAux){
                                timeLeds[0] = timeManager;
                                flags.b1 = 1;
                                puntaje += (MAXTIMEOUTSIDE*MAXTIMEOUTSIDE)/(randsOut[0]*(timeRead/10));
                                ui->aciertos_2->display(aciertos++);
                            }else{
                                ui->errores_2->display(errores++);
                                puntaje -=20;
                            }
                            flags2.b1 = 0;
                            ui->puntaje_2->display(puntaje);
                            auxMask = 0;
                        }
                        break;
                    case 1:
                        if(flags2.b2 == 1){
                            auxMask |= 1<<1;
                            if(auxMask & ledsAux){
                                timeLeds[1] = timeManager;
                                flags.b2 = 1;
                                puntaje += (MAXTIMEOUTSIDE*MAXTIMEOUTSIDE)/(randsOut[1]*(timeRead/10));
                                ui->aciertos_2->display(aciertos++);
                            }else{
                                ui->errores_2->display(errores++);
                                puntaje -=20;
                            }
                            flags2.b2 = 0;
                            ui->puntaje_2->display(puntaje);
                            auxMask = 0;
                        }
                        break;
                    case 2:
                        if(flags2.b3 == 1){
                            auxMask |= 1<<2;
                            if(auxMask & ledsAux){
                                timeLeds[2] = timeManager;
                                flags.b3 = 1;
                                puntaje += (MAXTIMEOUTSIDE*MAXTIMEOUTSIDE)/(randsOut[2]*(timeRead/10));
                                ui->aciertos_2->display(aciertos++);
                            }else{
                                ui->errores_2->display(errores++);
                                puntaje -=20;
                            }
                            flags2.b3 = 0;
                            ui->puntaje_2->display(puntaje);
                            auxMask = 0;
                        }
                        break;
                    case 3:
                        if(flags2.b4 == 1){
                            auxMask |= 1<<3;
                            if(auxMask & ledsAux){
                                timeLeds[3] = timeManager;
                                flags.b4 = 1;
                                puntaje += (MAXTIMEOUTSIDE*MAXTIMEOUTSIDE)/(randsOut[3]*(timeRead/10));
                                ui->aciertos_2->display(aciertos++);
                            }else{
                                ui->errores_2->display(errores++);
                                puntaje -=20;
                            }
                            flags2.b4 = 0;
                            ui->puntaje_2->display(puntaje);
                            auxMask = 0;
                        }
                        break;
                    default:
                        break;
                    }
            }
            break;
        case END:
            timeManager++;
            ui->estado1->setText("Estado: END");
            if((timeManager - contTime) >= 30){
                contTime = timeManager;
                auxState = !auxState;
                estadoComandos = SETLEDS;
                Send();
                estadoComandos = GETLEDS;
                Send();
                if(contTime >= 180){
                    timeManager = 0;
                    contTime = 0;
                    timeRead = 0;
                    partidaN++;
                    estadoJuego = BUTTONS;
                    if(puntaje > record){
                        record = puntaje;
                        ui->record_2->display(record);
                    }
                    ui->progressBar->setValue(0);
                    ui->estado1->setText("Estado: BUTTONS");
                }
            }
            break;

        default:
            break;
    }
}

void MainWindow::on_pushButton_clicked()
{
    if(estadoJuego == BUTTONS){
        record = -400;
        ui->record_2->display(0);
    }
}

