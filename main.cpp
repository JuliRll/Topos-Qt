#include "mbed.h"
#include <stdbool.h>

#define NUMBUTT             4

#define MAXLED              4

#define NUMBEAT             4 

#define HEARTBEATINTERVAL    100

/**
 * @brief Enumeración que contiene los estados de la máquina de estados(MEF) que se implementa para 
 * el "debounce" 
 * El botón está configurado como PullUp, establece un valor lógico 1 cuando no se presiona   
 * y cambia a valor lógico 0 cuando es presionado.
 */
typedef enum{
    BUTTON_DOWN,    //0
    BUTTON_UP,      //1
    BUTTON_FALLING, //2
    BUTTON_RISING   //3
}_eButtonState;

/**
 * @brief Enumeración de eventos del botón
 * Se usa para saber si el botón está presionado o nó
 */
typedef enum{
    EV_PRESSED,
    EV_NOT_PRESSED,
    EV_NONE
}_eButtonEvent;

/**
 * @brief Esturctura de Teclas
 * 
 */
typedef struct{
    _eButtonState estado;
    _eButtonEvent event;
    int32_t timeDown;
    int32_t timeDiff;
}_sTeclas;

_sTeclas ourButton[NUMBUTT];
//                0001 ,  0010,  0100,  1000


uint16_t mask[]={0x0001,0x0002,0x0004,0x0008};

/**
 * @brief Enumeración de la MEF para decodificar el protocolo
 * 
 */
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

/**
 * @brief Enumeración de la lista de comandos
 * 
 */
 typedef enum{
        ACK=0x0D,
        ALIVE=0xF0,
        GETBUTTONSTATE=0xFA,
        GETBUTTONS = 0xFD,
        GETLEDS = 0xFB,
        SETLEDS = 0xFC,
        ANGULO = 0xA2
    }_eID;

/**
 * @brief Estructura de datos para el puerto serie
 * 
 */
typedef struct{
    uint8_t timeOut;         //!< TiemOut para reiniciar la máquina si se interrumpe la comunicación
    uint8_t cheksumRx;       //!< Cheksumm RX
    uint8_t cheksumtx;       //!< Cheksumm Tx
    uint8_t indexWriteRx;    //!< Indice de escritura del buffer circular de recepción
    uint8_t indexReadRx;     //!< Indice de lectura del buffer circular de recepción
    uint8_t indexWriteTx;    //!< Indice de escritura del buffer circular de transmisión
    uint8_t indexReadTx;     //!< Indice de lectura del buffer circular de transmisión
    uint8_t bufferRx[256];   //!< Buffer circular de recepción
    uint8_t bufferTx[256];   //!< Buffer circular de transmisión
    uint8_t payload[32];     //!< Buffer para el Payload de datos recibidos
}_sDato ;

volatile _sDato datosComProtocol;
/**
 * @brief VOLATILE 
 * 
 * La palabra clave volatile se utiliza para evitar que el compilador aplique optimizaciones en variables
 * que pueden cambiar de formas en que el compilador no puede anticipar.
 * Los objetos declarados como volátiles se omiten de la optimización porque sus valores pueden ser cambiados por código 
 * fuera del alcance del código actual en cualquier momento. El sistema siempre lee el valor actual de un objeto volátil 
 * desde la ubicación de la memoria en lugar de mantener su valor en un registro temporal en el punto en el que se solicita, 
 * incluso si una instrucción previa solicitó un valor del mismo objeto. 
 * Se utilizan en variables globales modificadas por una rutina de servicio de interrupción(ISR). 
 * Si no declara la variable como volátil, el compilador optimizará el código.
 * Si no usamos un calificador volátil, pueden surgir los siguientes problemas
 *    1) Es posible que el código no funcione como se esperaba cuando la optimización está activada.
 *    2) Es posible que el código no funcione como se esperaba cuando las interrupciones están habilitadas y utilizadas.
 */


/**
 * @brief Mapa de bits para implementar banderas
 * Como uso una sola los 7 bits restantes los dejo reservados para futuras banderas
 */
typedef union{
    struct{
        uint8_t checkButtons :1;
        uint8_t Reserved :7;
    }individualFlags;
    uint8_t allFlags;
}_bGeneralFlags;

volatile _bGeneralFlags myFlags;

uint8_t heartBeatEvent;

/**
 * @brief Unión para descomponer/componer datos mayores a 1 byte
 * 
 */
typedef union {
    int32_t i32;
    uint32_t ui32;
    uint16_t ui16[2];
    uint8_t ui8[4];
    int8_t i8[4];
}_udat;

_udat myWord;


/**
 * @brief Dato del tipo Enum para asignar los estados de la MEF
 * 
 */
_eButtonState myButton;

/*************************************************************************************************/
/* Prototipo de Funciones */

/**
 * @brief Inicializa la MEF
 * Le dá un estado inicial a myButton
 */
void startMef(uint8_t indice);

/**
 * @brief Máquina de Estados Finitos(MEF)
 * Actualiza el estado del botón cada vez que se invoca.
 * 
 * @param buttonState Este parámetro le pasa a la MEF el estado del botón.
 */
void actuallizaMef(uint8_t indice );

/**
 * @brief Función para cambiar el estado del LED cada vez que sea llamada.
 * 
 */
void togleLed(uint8_t indice, uint8_t state);

/**
 * @brief Enciende o apaga los leds de la máscara
 * 
 * @param mask Se envian las posiciones de los leds que se quieren encender 
 */
void manejadorLed(uint8_t mask);

/**
 * @brief Función que se llama en la interrupción de recepción de datos
 * Cuando se llama la fucnión se leen todos los datos que llagaron.
 */
void onDataRx(void);

/**
 * @brief Decodifica las tramas que se reciben 
 * La función decodifica el protocolo para saber si lo que llegó es válido.
 * Utiliza una máquina de estado para decodificar el paquete
 */
void decodeProtocol(void);

/**
 * @brief Procesa el comando (ID) que se recibió
 * Si el protocolo es correcto, se llama a esta función para procesar el comando
 */
void loadData(void);

/**
 * @brief Envía los datos a la PC
 * La función consulta si el puerto serie está libra para escribir, si es así envía 1 byte y retorna
 */
void sendData(void);

/**
 * @brief Función que se llama con la interrupción del TICKER
 * maneja el tiempo de debounce de los botones, cambia un falg cada vez que se deben revisar los botones
 */
void OnTimeOut(void);

/**
 * @brief Función Hearbeat
 * Ejecuta las tareas del hearbeat 
 */
void hearbeatTask(void);

/**
 * @brief Carga los datos de los botones para enviar a la PC
 * 
 * @param indice 
 * @param state 
 */
void buttonEvent(uint8_t indice, uint8_t state);


/*****************************************************************************************************/
/* Configuración del Microcontrolador */

BusIn buttonArray(PB_6,PB_7,PB_8,PB_9);

BusOut leds(PB_12,PB_13,PB_14,PB_15);

DigitalOut HEARBEAT(PC_13); //!< Defino la salida del led

Serial pcCom(PA_9,PA_10,115200); //!< Configuración del puerto serie, la velocidad (115200) tiene que ser la misma en QT

Timer miTimer; //!< Timer general

Ticker timerGeneral;

/*****************************************************************************************************/
/************  Función Principal ***********************/


int main()
{
    int hearbeatTime=0;

    miTimer.start();

    myFlags.individualFlags.checkButtons=false;

    heartBeatEvent=0;
    
    pcCom.attach(&onDataRx,Serial::RxIrq);

    timerGeneral.attach_us(&OnTimeOut, 50000);

    for(uint8_t indice=0; indice<NUMBUTT;indice++){
        startMef(indice);
    }

    while(true)
    {
        if(myFlags.individualFlags.checkButtons){
            myFlags.individualFlags.checkButtons=false;
            for(uint8_t indice=0; indice < NUMBUTT; indice++){
                if (buttonArray & mask[indice]){
                    ourButton[indice].event =EV_NOT_PRESSED;
                }else{
                    ourButton[indice].event =EV_PRESSED; 
                }
                actuallizaMef(indice);
            }
        }
        if ((miTimer.read_ms()-hearbeatTime)>=HEARTBEATINTERVAL){
            hearbeatTime=miTimer.read_ms();
            hearbeatTask();
        }
        if(datosComProtocol.indexReadRx!=datosComProtocol.indexWriteRx) 
            decodeProtocol();

        if(datosComProtocol.indexReadTx!=datosComProtocol.indexWriteTx) 
            sendData();

    }
    return 0;
}


/*****************************************************************************************************/
/************  MEF para DEBOUNCE de botones ***********************/

void startMef(uint8_t indice){
   ourButton[indice].estado=BUTTON_UP;
}


void actuallizaMef(uint8_t indice){

    switch (ourButton[indice].estado)
    {
    case BUTTON_DOWN:
        if(ourButton[indice].event )
           ourButton[indice].estado=BUTTON_RISING;
    break;
    case BUTTON_UP:
        if(!(ourButton[indice].event))
            ourButton[indice].estado=BUTTON_FALLING;
    break;
    case BUTTON_FALLING:
        if(!(ourButton[indice].event))
        {
            ourButton[indice].timeDown=miTimer.read_ms();
            ourButton[indice].estado=BUTTON_DOWN;
            buttonEvent(indice,ourButton[indice].estado);
            loadData();
        }else
            ourButton[indice].estado=BUTTON_UP;    
    break;
    case BUTTON_RISING:
        if(ourButton[indice].event){
            ourButton[indice].estado=BUTTON_UP;
            ourButton[indice].timeDiff=miTimer.read_ms()-ourButton[indice].timeDown;
            buttonEvent(indice,ourButton[indice].estado);
            loadData();
        }else
            ourButton[indice].estado=BUTTON_DOWN;
    break;
    
    default:
        startMef(indice);
        break;
    }
}


/*****************************************************************************************************/
/************  Funciónes para manejar los LEDS ***********************/

void togleLed(uint8_t indice, uint8_t state){
    uint16_t auxmask=leds;

    if(state == 1){
        auxmask |= indice;
        leds = auxmask;
    }else{
        auxmask &= ~(indice);
        leds = auxmask;
    }
}


void manejadorLed(uint8_t mask){
    uint16_t auxled=0, setLeds=0;
    auxled|=1<<3;
    if(auxled & mask)
        setLeds |= 1 <<3;
    else
        setLeds &= ~(1<<3);
    auxled=0;
    auxled|=1<<2;
    if(auxled & mask)
        setLeds |= 1 <<2;
    else
        setLeds &= ~(1<<2);
    auxled=0;
    auxled|=1<<1;
    if(auxled & mask)
        setLeds |= 1 <<1;
    else
        setLeds &= ~(1<<1);
    auxled=0;
    auxled|=1<<0;
    if(auxled & mask)
        setLeds |= 1 <<0;
    else
        setLeds &= ~(1<<0);

    leds=setLeds;
}


/*****************************************************************************************************/
/************  MEF para decodificar el protocolo serie ***********************/
void decodeProtocol(void)
{
    static int8_t nBytes=0, indice=0;
    while (datosComProtocol.indexReadRx!=datosComProtocol.indexWriteRx)
    {
        switch (estadoProtocolo) {
            case START:
                if (datosComProtocol.bufferRx[datosComProtocol.indexReadRx++]=='U'){
                    estadoProtocolo=HEADER_1;
                    datosComProtocol.cheksumRx=0;
                }
                break;
            case HEADER_1:
                if (datosComProtocol.bufferRx[datosComProtocol.indexReadRx++]=='N')
                   estadoProtocolo=HEADER_2;
                else{
                    datosComProtocol.indexReadRx--;
                    estadoProtocolo=START;
                }
                break;
            case HEADER_2:
                if (datosComProtocol.bufferRx[datosComProtocol.indexReadRx++]=='E')
                    estadoProtocolo=HEADER_3;
                else{
                    datosComProtocol.indexReadRx--;
                   estadoProtocolo=START;
                }
                break;
        case HEADER_3:
            if (datosComProtocol.bufferRx[datosComProtocol.indexReadRx++]=='R')
                estadoProtocolo=NBYTES;
            else{
                datosComProtocol.indexReadRx--;
               estadoProtocolo=START;
            }
            break;
            case NBYTES:
                nBytes=datosComProtocol.bufferRx[datosComProtocol.indexReadRx++];
               estadoProtocolo=TOKEN;
                break;
            case TOKEN:
                if (datosComProtocol.bufferRx[datosComProtocol.indexReadRx++]==':'){
                   estadoProtocolo=PAYLOAD;
                    datosComProtocol.cheksumRx ='U'^'N'^'E'^'R'^ nBytes^':';
                    datosComProtocol.payload[0]=nBytes;
                    indice=1;
                }
                else{
                    datosComProtocol.indexReadRx--;
                    estadoProtocolo=START;
                }
                break;
            case PAYLOAD:
                if (nBytes>1){
                    datosComProtocol.payload[indice++]=datosComProtocol.bufferRx[datosComProtocol.indexReadRx];
                    datosComProtocol.cheksumRx ^= datosComProtocol.bufferRx[datosComProtocol.indexReadRx++];
                }
                nBytes--;
                if(nBytes<=0){
                    estadoProtocolo=START;
                    if(datosComProtocol.cheksumRx == datosComProtocol.bufferRx[datosComProtocol.indexReadRx]){
                        loadData();
                    }
                }
                break;
            default:
                estadoProtocolo=START;
                break;
        }
    }

}


/*****************************************************************************************************/
/************  Función para procesar el comando recibido ***********************/
void loadData(void)
{
    uint8_t auxBuffTx[50], indiceAux=0, cheksum;
    auxBuffTx[indiceAux++]='U';
    auxBuffTx[indiceAux++]='N';
    auxBuffTx[indiceAux++]='E';
    auxBuffTx[indiceAux++]='R';
    auxBuffTx[indiceAux++]=0;
    auxBuffTx[indiceAux++]=':';

    switch (datosComProtocol.payload[1]) {
        case ALIVE:
            auxBuffTx[indiceAux++]=ALIVE;
            auxBuffTx[indiceAux++]=ACK;
            auxBuffTx[NBYTES]=0x03;
            break;
        case GETBUTTONSTATE:
            auxBuffTx[indiceAux++]=GETBUTTONSTATE;
            auxBuffTx[indiceAux++]=datosComProtocol.payload[2];
            auxBuffTx[indiceAux++]=datosComProtocol.payload[3];
            auxBuffTx[indiceAux++]=datosComProtocol.payload[4];
            auxBuffTx[indiceAux++]=datosComProtocol.payload[5];
            auxBuffTx[indiceAux++]=datosComProtocol.payload[6];
            auxBuffTx[indiceAux++]=datosComProtocol.payload[7];
            auxBuffTx[NBYTES]=0x08;
            break;
        case GETBUTTONS:
            auxBuffTx[indiceAux++]=GETBUTTONS;
            myWord.ui16[0] = buttonArray;
            datosComProtocol.payload[2] = myWord.ui8[0];
            datosComProtocol.payload[3] = myWord.ui8[1];
            auxBuffTx[indiceAux++] = datosComProtocol.payload[2];
            auxBuffTx[indiceAux++] = datosComProtocol.payload[3];
            auxBuffTx[NBYTES] = 0x04;
            break;
        case SETLEDS:
            auxBuffTx[indiceAux++]=SETLEDS;
            myWord.ui8[0]=datosComProtocol.payload[2];
            myWord.ui8[1]=datosComProtocol.payload[3];
            auxBuffTx[NBYTES]=0x02;
            togleLed(myWord.ui8[0],myWord.ui8[1]);
            break;
        case GETLEDS:
            auxBuffTx[indiceAux++]=GETLEDS;
            myWord.ui16[0] = leds;
            datosComProtocol.payload[2] = myWord.ui8[0];
            datosComProtocol.payload[3] = myWord.ui8[1];
            auxBuffTx[indiceAux++] = datosComProtocol.payload[2];
            auxBuffTx[indiceAux++] = datosComProtocol.payload[3];
            auxBuffTx[NBYTES] = 0x04;
            break;
        default:
            auxBuffTx[indiceAux++]=0xDD;
            auxBuffTx[NBYTES]=0x02;
            break;
    }
   cheksum=0;
   for(uint8_t a=0 ;a < indiceAux ;a++)
   {
       cheksum ^= auxBuffTx[a];
       datosComProtocol.bufferTx[datosComProtocol.indexWriteTx++]=auxBuffTx[a];
   }
    datosComProtocol.bufferTx[datosComProtocol.indexWriteTx++]=cheksum;

}


/*****************************************************************************************************/
/************  Función para enviar los bytes hacia la pc ***********************/
void sendData(void)
{
    if(pcCom.writable())
        pcCom.putc(datosComProtocol.bufferTx[datosComProtocol.indexReadTx++]);

}


/*****************************************************************************************************/
/************  Función para hacer el hearbeats ***********************/
void hearbeatTask(void)
{
    if(heartBeatEvent < NUMBEAT){
        HEARBEAT=!HEARBEAT;
        heartBeatEvent++;
    }else{
        HEARBEAT=1;
        heartBeatEvent = (heartBeatEvent>=25) ? (0) : (heartBeatEvent+1);    
    }
}
/**********************************************************************************/
/* Servicio de Interrupciones*/

void onDataRx(void)
{
    while (pcCom.readable())
    {
        datosComProtocol.bufferRx[datosComProtocol.indexWriteRx++]=pcCom.getc();
    }
}

void OnTimeOut(void)
{
    if(!myFlags.individualFlags.checkButtons)
        myFlags.individualFlags.checkButtons=true;
}
/********************************************************************************/
/*Cargar datos de botones*/
void buttonEvent(uint8_t indice, uint8_t state){
    datosComProtocol.payload[1] = GETBUTTONSTATE;
    datosComProtocol.payload[2] = indice;
    datosComProtocol.payload[3] = state;
    if(state == BUTTON_FALLING)
        myWord.i32 = ourButton[indice].timeDown;
    else
        myWord.i32 = ourButton[indice].timeDiff;
    datosComProtocol.payload[4] = myWord.i8[0];
    datosComProtocol.payload[5] = myWord.i8[1];
    datosComProtocol.payload[6] = myWord.i8[2];
    datosComProtocol.payload[7] = myWord.i8[3];
} 