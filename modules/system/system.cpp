//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "system.h"
#include "global_defines.h"
#include "non_blocking_delay.h"
#include "tranquera.h"
//#include "scale.h"
#include "led.h"
#include "MQTT.h"
#include "rfid.h"

#include "serial_com.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

// ---Módulos---
static Tranquera tranquera(PIN_TRANQUERA, PIN_BOTON_ABRIR, MODE_PIN_BOTON_ABRIR, PIN_BOTON_CERRAR, MODE_PIN_BOTON_CERRAR);
//static Scale scale(PIN_BALANZA);
//static Led led_balanza(D1);
//static Led led_switch_balanza(D2);
static SerialCom pc(USBTX, USBRX, PC_BAUDRATE);
static RFID rfid_reader(PIN_RFID_MOSI, PIN_RFID_MISO, PIN_RFID_SCLK, PIN_RFID_CS, PIN_RFID_RESET, PIN_LED_LECTURA);
//static Button boton_abrir(PIN_BOTON_ABRIR, MODE_PIN_BOTON_ABRIR);
//static Button boton_cerrar(PIN_BOTON_CERRAR, MODE_PIN_BOTON_CERRAR);
static MQTT mqtt(PIN_MQTT_TX, PIN_MQTT_RX, MQTT_BAUDRATE, PIN_MQTT_STATUS, PIN_LED_WIFI_SIN_CONEXION, PIN_LED_WIFI_CONECTADO, PIN_LED_MENSAJE_MQTT);
// ---

// ---Delay---
nonBlockingDelay system_delay(SYSTEM_TIME_INCREMENT_MS);
// ---


// ---Interrupciones---
//InterruptIn int_scale(PIN_SWITCH_BALANZA, MODE_PIN_SWITCH_BALANZA);
// ---

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

char * lectura_rfid = nullptr;

//=====[Declarations (prototypes) of private functions]========================

//static void int_scale_callback_on();
//static void int_scale_callback_off();

//=====[Implementations of public functions]===================================

void system_init()
{
    system_delay.Start();

    /*
    int_scale.fall(&int_scale_callback_on);
    int_scale.rise(&int_scale_callback_off);
    */
}

void system_update()
{
    if(system_delay.isReady()){
        system_delay.Start();

        lectura_rfid = rfid_reader.read();
        if(lectura_rfid != nullptr){
            mqtt.publish("ProyectoTranquera/LecturaRFID", lectura_rfid);
            pc.string_write(lectura_rfid);
        }
    }
}

//=====[Implementations of private functions]==================================

/*
static void int_scale_callback_on()
{
    scale = ENCENDIDO;
}

static void int_scale_callback_off()
{
    scale = APAGADO;
}
*/