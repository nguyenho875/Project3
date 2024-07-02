//=====[Libraries]=============================================================

#include "scale.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

state_t state;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

//=====[Implementations of private functions]==================================

//=====[Implementations of public methods]=====================================

Scale::Scale(PinName pin_scale, PinName pin_enable_switch, PinMode mode_enable_switch):
        AI(pin_scale), enable_switch(pin_enable_switch, mode_enable_switch), int_enable_switch(pin_enable_switch, mode_enable_switch)
{
    if(enable_switch == HIGH){
        Scale::update_state(ENCENDIDO);
    }
    else{
        Scale::update_state(APAGADO);
    }

    int_enable_switch.rise(callback(this, &Scale::int_enable_switch_callback_on));
    int_enable_switch.fall(callback(this, &Scale::int_enable_switch_callback_off));
}

bool Scale::read(char * buffer)
{
    // Verificar si la balanza está apagada
    if (state == APAGADO) {
        strcpy(buffer, "-");
        return false; // La balanza está apagada, devuelve false
    }

    // La sobrecarga de float() en Scale llamará a AI.read() automáticamente
    // Leer el valor analógico
    float value = AI.read() * 500.0f;

    // Formatear el valor con dos dígitos decimales en buffer
    snprintf(buffer, 16, "%.2f", value);

    return true; // La balanza está encendida, devuelve true
}

state_t Scale::read_state()
{
    return state;
}

//=====[Implementations of private methods]====================================

void Scale::update_state(state_t new_state)
{
    state = new_state;
    switch (state){
        case ENCENDIDO:
            break;
        case APAGADO:
            break;
        default:
            break;
    }
}

void Scale::int_enable_switch_callback_on()
{
    Scale::update_state(ENCENDIDO);
}

void Scale::int_enable_switch_callback_off()
{
    Scale::update_state(APAGADO);
}