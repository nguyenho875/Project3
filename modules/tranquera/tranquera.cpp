//=====[Libraries]=============================================================

#include "tranquera.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

position_t position;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

//=====[Implementations of private functions]==================================

//=====[Implementations of public methods]=====================================

tranquera::tranquera(PinName pin): output(pin)
{
    // Se inicializa en CERRADO
    position = CERRADO;
}

tranquera::tranquera(PinName pin, int value): output(pin, value)
{
    if(value == OFF){
        position = CERRADO;
    }
    else{
        position = ABIERTO;
    }
}

void tranquera::write(position_t new_position)
{
    position = new_position;
}


int tranquera::read()
{
    return position;
}

void tranquera::update()
{
    change_position();
}

//=====[Implementations of private methods]====================================

void tranquera::change_position()
{
    if(position == ABIERTO){
        output = ON;
    }
    else if(position == CERRADO){
        output = OFF;
    }
    else{
    }
}