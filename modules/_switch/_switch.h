//=====[#include guards - begin]===============================================

#ifndef __SWITCH_H_
#define __SWITCH_H_

//==================[Libraries]===============================================

#include "mbed.h"
#include "arm_book_lib.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declaration of public classes]=========================================

class _switch
{
    public:
        // Crea el switch y lo inicializa sin Pull
        _switch(PinName pin);

        // Crea el switch y lo inicializa en el modo indicado
        _switch(PinName pin, PinMode mode);

        // Lee el valor del switch
        int read();

        // Setea el modo de Pull
        void mode(PinMode mode);

        // Sobrecarga de int() para leer
        operator int()
        {
            return read();
        }

    private:
        // Entrada digital
        DigitalIn DI;

};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================

#endif // __SWITCH_H_