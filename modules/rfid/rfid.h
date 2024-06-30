//=====[#include guards - begin]===============================================

#ifndef _RFID_H_
#define _RFID_H_

//==================[Libraries]===============================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "MFRC522.h"
#include "led.h"
#include "non_blocking_delay.h"

//=====[Declaration of public defines]=========================================

#define READ_DELAY_TIME_MS 3000

//=====[Declaration of public data types]======================================

typedef enum{
    LEYENDO,
    ESPERANDO
} RFID_status_t;

//=====[Declaration of public classes]=========================================

class RFID
{
    public:
        // Crea el objeto y lo inicializa
        RFID(PinName pin_mosi, PinName pin_miso, PinName pin_sclk, PinName pin_cs, PinName pin_reset, PinName pin_led);

        // Busca si hay una tarjeta y la lee
        char * read();

        //
        RFID_status_t get_status();

    private:
        // Módulo lector de rfid
        MFRC522 reader;

        // ID leído
        char id[20];

        // Led de lectura
        Led led_lectura;

        nonBlockingDelay read_delay;

        //
        RFID_status_t RFID_status;

        //
        void set_status(RFID_status_t new_status);

        //
        void read_delay_callback();

};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================

#endif // _RFID_H_