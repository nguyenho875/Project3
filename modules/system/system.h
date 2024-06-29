//=====[#include guards - begin]===============================================

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

//=====[Declaration of public defines]=========================================

// Placas
#define NUCLEO_F429ZI 0

// Placa usada
#define PLACA NUCLEO_F429ZI

#if PLACA == NUCLEO_F429ZI

#define PC_BAUDRATE 115200

#define PIN_TRANQUERA D0
#define PIN_LED_WIFI_SIN_CONEXION D1
#define PIN_LED_WIFI_CONECTADO D2
#define PIN_LED_LECTURA D3
#define PIN_LED_MODO_NORMAL D4
#define PIN_LED_MODO_SOLO_LECTURA D5

#define PIN_SWITCH_BALANZA D7
#define PIN_SWITCH_SOLO_LECTURA D8
#define PIN_BOTON_ABRIR D9
#define PIN_BOTON_CERRAR D10

#define PIN_BALANZA A0

#define MODE_PIN_SWITCH_BALANZA PullDown
#define MODE_PIN_SWITCH_SOLO_LECTURA PullDown
#define MODE_PIN_BOTON_ABRIR PullDown
#define MODE_PIN_BOTON_CERRAR PullDown

#define PIN_RFID_MOSI PF_9
#define PIN_RFID_MISO PF_8
#define PIN_RFID_SCLK PF_7
#define PIN_RFID_RESET PG_1
#define PIN_RFID_CS PE_3

#define PIN_MQTT_TX PC_12
#define PIN_MQTT_RX PD_2
#define PIN_MQTT_STATUS PG_2
#define MQTT_BAUDRATE 115200

#endif //PLACA

#define SYSTEM_TIME_INCREMENT_MS   100

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void system_init();
void system_update();

//=====[#include guards - end]=================================================

#endif // _SYSTEM_H_