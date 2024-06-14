//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "system.h"
#include "tranquera.h"
#include "non_blocking_delay.h"
//#include "button.h"
//#include "_switch.h"
#include "scale.h"
#include "led.h"
#include "serial_com.h"
//#include <cstdio>
#include "MFRC522.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

// ---Módulos---
static Tranquera tranquera(PIN_TRANQUERA);
static Scale scale(PIN_BALANZA);
//static Led led_balanza(D1);
static Led led_switch_balanza(D2);
static SerialCom pc(USBTX, USBRX, 115200);
static MFRC522 rfid(PIN_RFID_MOSI, PIN_RFID_MISO, PIN_RFID_SCLK, PIN_RFID_CS, PIN_RFID_RESET);
//static Button boton_abrir(PIN_BOTON_ABRIR, MODE_PIN_BOTON_ABRIR);
//static Button boton_cerrar(PIN_BOTON_CERRAR, MODE_PIN_BOTON_CERRAR);
// ---

// ---Delay---
nonBlockingDelay system_delay(SYSTEM_TIME_INCREMENT_MS);
// ---

// ---Interrupciones---
InterruptIn int_boton_abrir(PIN_BOTON_ABRIR, MODE_PIN_BOTON_ABRIR);
InterruptIn int_boton_cerrar(PIN_BOTON_CERRAR, MODE_PIN_BOTON_CERRAR);
InterruptIn int_scale(PIN_SWITCH_BALANZA, MODE_PIN_SWITCH_BALANZA);
// ---

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

static void int_boton_abrir_callback();
static void int_boton_cerrar_callback();
static void int_scale_callback_on();
static void int_scale_callback_off();

//=====[Implementations of public functions]===================================

void system_init()
{
    tickInit();
    rfid.PCD_Init();

    if(MODE_PIN_BOTON_ABRIR == PullDown){
        int_boton_abrir.rise(&int_boton_abrir_callback);
    }
    else if(MODE_PIN_BOTON_ABRIR == PullUp){
        int_boton_abrir.fall(&int_boton_abrir_callback);
    }

    if(MODE_PIN_BOTON_CERRAR == PullDown){
        int_boton_cerrar.rise(&int_boton_cerrar_callback);
    }
    else if(MODE_PIN_BOTON_CERRAR == PullUp){
        int_boton_cerrar.fall(&int_boton_cerrar_callback);
    }

    int_scale.fall(&int_scale_callback_on);
    int_scale.rise(&int_scale_callback_off);
}

void system_update()
{
    if(system_delay.Read())
    {
        if(scale.read_state() == APAGADO){
            led_switch_balanza = ON;
        }
        else{
            led_switch_balanza = OFF;
        }

        tranquera.update();

        //pc.float_write(scale);

        // Look for new cards
        if (rfid.PICC_IsNewCardPresent()){
            // Select one of the cards
            if (rfid.PICC_ReadCardSerial()){
                // Print Card UID
                //pc.string_write("Card UID:");
                for (uint8_t i = 0; i < rfid.uid.size; i++){
                    //char aux[10] = "";
                    //sprintf(aux, " %02X", rfid.uid.uidByte[i]);

                    pc.byte_write(rfid.uid.uidByte[i]);
                    pc.string_write(" ");
                }
                pc.string_write("\n\r");

                /*
                // Print Card type
                uint8_t piccType = rfid.PICC_GetType(rfid.uid.sak);
                //pc.string_write("PICC Type: %s \n\r", rfid.PICC_GetTypeName(piccType));
                char aux[100] = "";
                sprintf(aux, "PICC Type: %s \n\r", rfid.PICC_GetTypeName(piccType));
                pc.string_write(aux);
                */
            }
        }
    }
}

//=====[Implementations of private functions]==================================

static void int_boton_abrir_callback()
{
    tranquera = ABIERTO;
}

static void int_boton_cerrar_callback()
{
    tranquera = CERRADO;
}

static void int_scale_callback_on()
{
    scale = ENCENDIDO;
}

static void int_scale_callback_off()
{
    scale = APAGADO;
}