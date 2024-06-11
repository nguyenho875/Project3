//=====[#include guards - begin]===============================================

#ifndef _TRANQUERA_H_
#define _TRANQUERA_H_

//==================[Libraries]===============================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "led.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum{
    CERRADO,
    ABIERTO
} position_t;

//=====[Declaration of public classes]=========================================

class Tranquera
{
    public:
        // Crea la tranquera y la inicializa cerrada
        Tranquera(PinName pin);

        // Crea la tranquera y le indica el valor de inicio (ON=abierto / OFF=cerrado)
        Tranquera(PinName pin, int value);

        // Pide el cambio de posición a CERRADO o ABIERTO
        void write(position_t new_position);

        // Lee el valor de la tranquera
        int read();

        // Realiza el cambio de posición de la tranquera
        void update();

        // Sobrecarga del operador = para escribir
        Tranquera &operator= (position_t new_position)
        {
            write(new_position);
            return *this;
        }

        // Sobrecarga de int() para leer
        operator int()
        {
            return read();
        }

    private:
        // leds de salida
        Led output;

        // Actualiza la posición de la tranquera
        void update_position();

};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================

#endif // _TRANQUERA_H_