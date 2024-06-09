//=====[Libraries]=============================================================

#include "tranquera.h"

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

tranquera::tranquera(PinName pin): salida(pin)
{
}

tranquera::tranquera(PinName pin, int value): salida(pin, value)
{
}

void tranquera::write(int value)
{
    salida = value;
}


int tranquera::read()
{
    return salida;
}

//=====[Implementations of private methods]====================================