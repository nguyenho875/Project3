//=====[#include guards - begin]===============================================

#ifndef _TRANQUERA_H_
#define _TRANQUERA_H_

//==================[Libraries]===============================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "led.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declaration of public classes]=========================================

class tranquera
{
    public:
        // Crea la tranquera y la inicializa cerrada
        tranquera(PinName pin);

        // Crea la tranquera y le indica el valor de inicio (ON=abierto / OFF=cerrado)
        tranquera(PinName pin, int value);

        // Setea la tranquera en ON=abierto / OFF=cerrado
        void write(int value);

        // Lee el valor de la tranquera
        int read();

        // Sobrecarga del operador = para escribir
        tranquera &operator= (int value)
        {
            write(value);
            return *this;
        }

        // Sobrecarga de int() para leer
        operator int()
        {
            return read();
        }

    private:
        // leds de salida
        led salida;

};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================

#endif // _TRANQUERA_H_