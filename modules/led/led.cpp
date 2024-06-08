//=====[Libraries]=============================================================

#include "led.h"

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

led::led(PinName pin): DO(pin, OFF)
{
    state = OFF;
}

led::led(PinName pin, int value): DO(pin, value)
{
    state = value;
}

void led::write(int value)
{
    DO = value;
    state = value;
}


int led::read()
{
    return state;
}

//=====[Implementations of private methods]====================================