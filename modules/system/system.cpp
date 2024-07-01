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

//=====[Declarations (prototypes) of private functions]========================

void parse_message_received(const char * topic, const char * message);
//static void int_scale_callback_on();
//static void int_scale_callback_off();

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
nonBlockingDelay MQTT_update_delay(MQTT_UPDATE_DELAY_TIME_MS);
nonBlockingDelay RFID_read_delay(RFID_READ_DELAY_TIME_MS);
// ---


// ---Interrupciones---
//InterruptIn int_scale(PIN_SWITCH_BALANZA, MODE_PIN_SWITCH_BALANZA);
// ---

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

char * lectura_rfid = nullptr;
char topic_received[256] = "";
char message_received[256] = "";

//=====[Implementations of public functions]===================================

void system_init()
{
    MQTT_update_delay.Start();
    RFID_read_delay.Start();

    mqtt.subscribe(TOPIC_STATE_TRANQUERA);
    /*
    int_scale.fall(&int_scale_callback_on);
    int_scale.rise(&int_scale_callback_off);
    */
}

void system_update()
{
    if(RFID_read_delay.isReady()){
        RFID_read_delay.Start();

        lectura_rfid = rfid_reader.read();
        if(lectura_rfid != nullptr){
            mqtt.publish("ProyectoTranquera/LecturaRFID", lectura_rfid);
            pc.string_write(lectura_rfid);
        }
    }

    if(MQTT_update_delay.isReady()){
        MQTT_update_delay.Start();

        mqtt.processPendings();
    }

    if(mqtt.unread_message){
        mqtt.receive(topic_received, message_received);
        parse_message_received(topic_received, message_received);
    }
}

//=====[Implementations of private functions]==================================

void parse_message_received(const char * topic, const char * message)
{
    mqtt.read_ok();

    if (strcmp(topic, "subscribed") == 0) {
        mqtt.confirmSubscription(message);
    }
    else if (strcmp(topic, "unsubscribed") == 0) {
        mqtt.confirmUnsubscription(message);
    }
    else if (strcmp(topic, TOPIC_STATE_TRANQUERA) == 0) {
        if(strcmp(message, MESSAGE_ABRIR_TRANQUERA) == 0){
            tranquera = ABIERTO;
        }
        else if(strcmp(message, MESSAGE_CERRAR_TRANQUERA) == 0){
            tranquera = CERRADO;
        }
    }
}

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