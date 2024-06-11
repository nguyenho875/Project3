//=====[#include guards - begin]===============================================

#ifndef _SCALE_H_
#define _SCALE_H_

//==================[Libraries]===============================================

#include "mbed.h"
#include "arm_book_lib.h"
#include "_switch.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum{
    ENCENDIDO,
    APAGADO
} state_t;

//=====[Declaration of public classes]=========================================

class Scale
{
    public:
        // Crea la balanza
        Scale(PinName pin_scale);

        // Lee el valor de la balanza, entre 0 y 500 kg. -1 si la balanza está apagada
        float read();

        // Pide el cambio de estado a ENCENDIDO o APAGADO
        void write_state(state_t new_state);

        // Sobrecarga de int() para leer
        operator int()
        {
            return read();
        }

        // Sobrecarga del operador = para escribir
        Scale &operator= (state_t new_state)
        {
            write_state(new_state);
            return *this;
        }

    private:
        // Entrada analógica
        AnalogIn AI;

};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================

#endif // _SCALE_H_