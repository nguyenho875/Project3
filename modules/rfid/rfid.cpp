//=====[Libraries]=============================================================

#include "rfid.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

//=====[Implementations of private functions]==================================

//=====[Implementations of public methods]=====================================

RFID::RFID(PinName pin_mosi, PinName pin_miso, PinName pin_sclk, PinName pin_cs, PinName pin_reset, PinName pin_led): 
        reader(pin_mosi, pin_miso, pin_sclk, pin_cs, pin_reset), led(pin_led, OFF), read_delay(READ_DELAY_TIME_MS)
{
    reader.PCD_Init();
    read_delay.Start();
}

char * RFID::read()
{
    if(read_delay.Read()){
        led = OFF;
        // Limpiar el buffer del ID
        memset(id, 0, sizeof(id));

        // Buscar nuevas tarjetas
        if (reader.PICC_IsNewCardPresent()) {
            // Seleccionar una de las tarjetas
            if (reader.PICC_ReadCardSerial()) {
                // Convertir el UID a una cadena de caracteres hexadecimales
                for (uint8_t i = 0; i < reader.uid.size; i++) {
                    sprintf(&id[i * 2], "%02X", reader.uid.uidByte[i]);
                }
                id[reader.uid.size * 2] = '\0'; // Agregar el carácter nulo al final
                led = ON;
                read_delay.Start();
                return id;
            }
        }
    }
    return nullptr; // Devolver nullptr si no se leyó ninguna tarjeta
}

//=====[Implementations of private methods]====================================
