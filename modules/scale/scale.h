//=====[#include guards - begin]===============================================

#ifndef _SCALE_H_
#define _SCALE_H_

//==================[Libraries]===============================================

#include "mbed.h"
#include "arm_book_lib.h"

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
        Scale(PinName pin_scale, PinName pin_enable_switch, PinMode mode_enable_switch);

        // Lee el valor de la balanza, entre 0 y 500 kg. -1 si la balanza está apagada
        bool read(char * value);

        // Lee el valor del estado de la balanza
        state_t read_state();

    private:
        // Entrada analógica
        AnalogIn AI;

        //
        DigitalIn enable_switch;

        //
        InterruptIn int_enable_switch;

        //
        void update_state(state_t new_state);

        void int_enable_switch_callback_on();
        void int_enable_switch_callback_off();

};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================

#endif // _SCALE_H_