//=====[#include guards - begin]===============================================

#ifndef _SYSTEM_H_
#define _SYSTEM_H_

//=====[Declaration of public defines]=========================================

#define MQTT_UPDATE_DELAY_TIME_MS   1000
#define RFID_READ_DELAY_TIME_MS     250

//---MQTT Topics---
#define TOPIC_STATE_TRANQUERA "ProyectoTranquera/Tranquera"
//---

//---MQTT Messages---
#define MESSAGE_ABRIR_TRANQUERA "1"
#define MESSAGE_CERRAR_TRANQUERA "0"
//

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void system_init();
void system_update();

//=====[#include guards - end]=================================================

#endif // _SYSTEM_H_