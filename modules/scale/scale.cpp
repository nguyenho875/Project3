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

Scale::Scale(PinName pin_scale): AI(pin_scale)
{
    // Se inicializa en encendido
    state = ENCENDIDO;
}

float Scale::read()
{
    // read devuelve un float entre 0 y 1
    if(state == ENCENDIDO){
        return AI*500;
    }
    else{
        return -1;
    }
}

state_t Scale::read_state()
{
    return state;
}

void Scale::write_state(state_t new_state)
{
    state = new_state;
}

//=====[Implementations of private methods]====================================