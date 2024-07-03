//=====[Libraries]=============================================================

#include "mode_selector.h"

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

ModeSelector::ModeSelector(PinName pin_switch_mode_selector, PinMode mode_switch_mode_selector, PinName led_mode_idle, PinName led_mode_solo_lectura):
                system_mode_selector_in(pin_switch_mode_selector, mode_switch_mode_selector), led_idle(led_mode_idle), led_solo_lectura(led_mode_solo_lectura), int_system_mode_selector(pin_switch_mode_selector, mode_switch_mode_selector)
{
    if(system_mode_selector_in == HIGH){
        ModeSelector::update_state(SOLO_LECTURA);
    }
    else{
        ModeSelector::update_state(IDLE);
    }

    int_system_mode_selector.rise(callback(this, &ModeSelector::int_system_mode_solo_lectura_callback));
    int_system_mode_selector.fall(callback(this, &ModeSelector::int_system_mode_idle_callback));
}

system_mode_t ModeSelector::read_state()
{
    return this->system_mode;
}

//=====[Implementations of private methods]====================================

void ModeSelector::update_state(system_mode_t new_mode)
{
    this->system_mode = new_mode;
    switch (this->system_mode){
        case IDLE:
            this->led_idle = ON;
            this->led_solo_lectura = OFF;
            break;
        case SOLO_LECTURA:
            this->led_idle = OFF;
            this->led_solo_lectura = ON;
            break;
        default:
            break;
    }
}

void ModeSelector::int_system_mode_idle_callback()
{
    ModeSelector::update_state(IDLE);
}

void ModeSelector::int_system_mode_solo_lectura_callback()
{
    ModeSelector::update_state(SOLO_LECTURA);
}