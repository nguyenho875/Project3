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

Tranquera::Tranquera(PinName pin): output(pin)
{
    // Se inicializa en CERRADO
    position = CERRADO;
}

Tranquera::Tranquera(PinName pin, int value): output(pin, value)
{
    if(value == OFF){
        position = CERRADO;
    }
    else{
        position = ABIERTO;
    }
}

void Tranquera::write(position_t new_position)
{
    position = new_position;
}


int Tranquera::read()
{
    return position;
}

void Tranquera::update()
{
    update_position();
}

//=====[Implementations of private methods]====================================

void Tranquera::update_position()
{
    switch (position){
        case ABIERTO:
            output = ON;
            break;
        case CERRADO:
            output = OFF;
            break;
        default:
            break;
    }
}