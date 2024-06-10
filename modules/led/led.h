//=====[#include guards - begin]===============================================

#ifndef _LED_H_
#define _LED_H_

//==================[Libraries]===============================================

#include "mbed.h"
#include "arm_book_lib.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declaration of public classes]=========================================

class Led
{
    public:
        // Crea el led y lo inicializa apagado
        Led(PinName pin);

        // Crea el led y le indica el valor de inicio (ON / OFF)
        Led(PinName pin, int value);

        // Setea el led en ON / OFF
        void write(int value);

        // Lee el valor del led
        int read();

        // Sobrecarga del operador = para escribir
        Led &operator= (int value)
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
        // Salida digital
        DigitalOut DO;

};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================

#endif // _LED_H_