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
void send_tranquera_position();
void int_system_mode_idle_callback();
void int_system_mode_solo_lectura_callback();

//=====[Declaration and initialization of public global objects]===============

//PARA DEBUGGUEAR:
static SerialCom pc(USBTX, USBRX, PC_BAUDRATE);

// ---Módulos---
static Tranquera tranquera(PIN_TRANQUERA, PIN_BOTON_ABRIR, MODE_PIN_BOTON_ABRIR, PIN_BOTON_CERRAR, MODE_PIN_BOTON_CERRAR);
static Scale scale(PIN_BALANZA, PIN_SWITCH_BALANZA, MODE_PIN_SWITCH_BALANZA);
static RFID rfid_reader(PIN_RFID_MOSI, PIN_RFID_MISO, PIN_RFID_SCLK, PIN_RFID_CS, PIN_RFID_RESET, PIN_LED_LECTURA);
static MQTT mqtt(PIN_MQTT_TX, PIN_MQTT_RX, MQTT_BAUDRATE, PIN_MQTT_STATUS, PIN_LED_WIFI_CONECTADO, PIN_LED_WIFI_SIN_CONEXION, PIN_LED_MENSAJE_MQTT);
// ---

// ---Delays---
static nonBlockingDelay RFID_read_delay(RFID_READ_TRY_DELAY_TIME_MS);
// ---

//---Interrupciones---
InterruptIn int_system_mode_selector(PIN_SWITCH_SOLO_LECTURA, MODE_PIN_SWITCH_SOLO_LECTURA);
//---

DigitalIn system_mode_selector_in(PIN_SWITCH_SOLO_LECTURA, MODE_PIN_SWITCH_SOLO_LECTURA);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

char * lectura_rfid = nullptr;
char lectura_scale [256] = "";
char msg [256] = "";
char topic_received[256] = "";
char message_received[256] = "";

static system_mode_t system_mode;

//=====[Implementations of public functions]===================================

void system_init()
{
    RFID_read_delay.Start();

    if(system_mode_selector_in == HIGH){
        system_mode = SOLO_LECTURA;
    }
    else{
        system_mode = IDLE;
    }

    int_system_mode_selector.fall(&int_system_mode_idle_callback);
    int_system_mode_selector.rise(&int_system_mode_solo_lectura_callback);

    mqtt.subscribe(TOPIC_TRANQUERA);
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
            mqtt.publish(TOPIC_RFID_LECTURA, msg);
            pc.string_write("\nRFID: ");
            pc.string_write(lectura_rfid);
            pc.string_write("\n");
            pc.string_write("Peso: ");
            pc.string_write(lectura_scale);
            pc.string_write("\n");
        }

        if(tranquera.position_changed){
            send_tranquera_position();
            tranquera.position_changed = false;
        }

    }

    mqtt.processPendings();

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

    else if (strcmp(topic, TOPIC_TRANQUERA) == 0) {
        if(strcmp(message, MESSAGE_TRANQUERA_ABRIR) == 0 && system_mode == IDLE){
            tranquera = ABIERTO;
        }
        else if(strcmp(message, MESSAGE_TRANQUERA_CERRAR) == 0 && system_mode == IDLE){
            tranquera = CERRADO;
        }
        else if(strcmp(message, MESSAGE_TRANQUERA_PEDIR_ESTADO) == 0){
            send_tranquera_position();
        }
    }
}

void send_tranquera_position()
{
    
    position_t position = tranquera;
    switch (position){
        case ABIERTO:
            mqtt.publish(TOPIC_TRANQUERA_ESTADO, MESSAGE_TRANQUERA_ABRIR);
            break;
        case CERRADO:
            mqtt.publish(TOPIC_TRANQUERA_ESTADO, MESSAGE_TRANQUERA_CERRAR);
            break;
        default:
            break;
    }
    
}

void int_system_mode_idle_callback()
{
    system_mode = IDLE;
}

void int_system_mode_solo_lectura_callback()
{
    system_mode = SOLO_LECTURA;
}