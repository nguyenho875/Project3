//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "global_defines.h"

#include "system.h"
#include "non_blocking_delay.h"
#include "tranquera.h"
#include "scale.h"
#include "MQTT.h"
#include "rfid.h"


#include "serial_com.h"
#include "led.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declarations (prototypes) of private functions]========================

void parse_message_received(const char * topic, const char * message);

//=====[Declaration and initialization of public global objects]===============

//PARA DEBUGGUEAR:
static SerialCom pc(USBTX, USBRX, PC_BAUDRATE);

// ---Módulos---
static Tranquera tranquera(PIN_TRANQUERA, PIN_BOTON_ABRIR, MODE_PIN_BOTON_ABRIR, PIN_BOTON_CERRAR, MODE_PIN_BOTON_CERRAR);
static Scale scale(PIN_BALANZA, PIN_SWITCH_BALANZA, MODE_PIN_SWITCH_BALANZA);
static RFID rfid_reader(PIN_RFID_MOSI, PIN_RFID_MISO, PIN_RFID_SCLK, PIN_RFID_CS, PIN_RFID_RESET, PIN_LED_LECTURA);
static MQTT mqtt(PIN_MQTT_TX, PIN_MQTT_RX, MQTT_BAUDRATE, PIN_MQTT_STATUS, PIN_LED_WIFI_CONECTADO, PIN_LED_WIFI_SIN_CONEXION, PIN_LED_MENSAJE_MQTT);
// ---

// ---Delay---
nonBlockingDelay MQTT_update_delay(MQTT_UPDATE_DELAY_TIME_MS);
nonBlockingDelay RFID_read_delay(RFID_READ_TRY_DELAY_TIME_MS);
// ---

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

char * lectura_rfid = nullptr;
char lectura_scale [256] = "";
char msg [256] = "";
char topic_received[256] = "";
char message_received[256] = "";

//=====[Implementations of public functions]===================================

void system_init()
{
    MQTT_update_delay.Start();
    RFID_read_delay.Start();

    mqtt.subscribe(TOPIC_STATE_TRANQUERA);
}

void system_update()
{
    if(RFID_read_delay.isReady()){
        RFID_read_delay.Start();

        lectura_rfid = rfid_reader.read();
        if(lectura_rfid != nullptr){
            scale.read(lectura_scale);
            strcpy(msg, lectura_rfid);
            strcat(msg, ":");
            strcat(msg, lectura_scale);
            mqtt.publish("ProyectoTranquera/LecturaRFID", msg);
            pc.string_write("\nRFID: ");
            pc.string_write(lectura_rfid);
            pc.string_write("\n");
            pc.string_write("Peso: ");
            pc.string_write(lectura_scale);
            pc.string_write("\n");
        }

    }

    if(MQTT_update_delay.isReady()){
        MQTT_update_delay.Start();

        mqtt.processPendings();
    }

    if(mqtt.receive(topic_received, message_received)){
        parse_message_received(topic_received, message_received);
    }
}

//=====[Implementations of private functions]==================================

void parse_message_received(const char * topic, const char * message)
{
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