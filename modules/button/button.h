//=====[#include guards - begin]===============================================

#ifndef _BUTTON_H_
#define _BUTTON_H_

//==================[Libraries]===============================================

#include "mbed.h"
#include "arm_book_lib.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declaration of public classes]=========================================

class Button
{
    public:
        // Crea el boton y lo inicializa sin Pull
        Button(PinName pin);

        // Crea el boton y lo inicializa en el modo indicado
        Button(PinName pin, PinMode mode);

        // Lee el valor del boton
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

#endif // _BUTTON_H_