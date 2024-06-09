//=====[#include guards - begin]===============================================

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

//=====[Declaration of public defines]=========================================

// Placas
#define NUCLEO_F429ZI 0

// Placa usada
#define PLACA NUCLEO_F429ZI

#if PLACA == NUCLEO_F429ZI

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

#endif //PLACA

#define SYSTEM_TIME_INCREMENT_MS   100

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void system_init();
void system_update();

//=====[#include guards - end]=================================================

#endif // _SYSTEM_H_