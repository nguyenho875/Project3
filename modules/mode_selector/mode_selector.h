//=====[#include guards - begin]===============================================

#ifndef _MODE_SELECTOR_H_
#define _MODE_SELECTOR_H_

//==================[Libraries]===============================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "led.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum{
    IDLE,
    SOLO_LECTURA
} system_mode_t;

//=====[Declaration of public classes]=========================================

class ModeSelector
{
    public:
        //
        ModeSelector(PinName pin_switch_mode_selector, PinMode mode_switch_mode_selector, PinName led_mode_idle, PinName led_mode_solo_lectura);

        system_mode_t read_state();

        operator system_mode_t()
        {
            return read_state();
        }

        bool mode_changed = false;

    private:
        //
        Led led_idle;
        Led led_solo_lectura;

        DigitalIn system_mode_selector_in;

        system_mode_t system_mode;

        InterruptIn int_system_mode_selector;

        void update_state(system_mode_t new_mode);

        void int_system_mode_idle_callback();
        void int_system_mode_solo_lectura_callback();

};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================

#endif // _MODE_SELECTOR_H_