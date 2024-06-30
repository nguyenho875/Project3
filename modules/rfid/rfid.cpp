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
        reader(pin_mosi, pin_miso, pin_sclk, pin_cs, pin_reset), led_lectura(pin_led, OFF), read_delay(READ_DELAY_TIME_MS, callback(this, &RFID::read_delay_callback))
{
    this->reader.PCD_Init();
    RFID::set_status(ESPERANDO);
    this->led_lectura = OFF;
}

char * RFID::read()
{
    if(this->RFID_status == ESPERANDO){
        // Limpiar el buffer del ID
        memset(id, 0, sizeof(id));

        // Buscar nuevas tarjetas
        if (reader.PICC_IsNewCardPresent()) {
            // Seleccionar una de las tarjetas
            if (reader.PICC_ReadCardSerial()) {
                RFID::set_status(LEYENDO);
                // Convertir el UID a una cadena de caracteres hexadecimales
                for (uint8_t i = 0; i < this->reader.uid.size; i++) {
                    sprintf(&this->id[i * 2], "%02X", this->reader.uid.uidByte[i]);
                }
                this->id[reader.uid.size * 2] = '\0'; // Agregar el carácter nulo al final
                return this->id;
            }
        }
    }
    return nullptr; // Devolver nullptr si no se leyó ninguna tarjeta
}

RFID_status_t RFID::get_status()
{
    return this->RFID_status;
}

//=====[Implementations of private methods]====================================

void RFID::set_status(RFID_status_t new_status)
{
    this->RFID_status = new_status;
    switch (RFID_status){
        case LEYENDO:
            this->led_lectura = ON;
            this->read_delay.Start();
            break;
        case ESPERANDO:
            this->led_lectura = OFF;
            break;
        default:
            break;
    }
}

void RFID::read_delay_callback()
{
    RFID::set_status(ESPERANDO);
}