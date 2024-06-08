//=====[Libraries]=============================================================

#include "button.h"

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

button::button(PinName pin): DI(pin)
{
}

button::button(PinName pin, PinMode mode): DI(pin, mode)
{
}

int button::read()
{
    return DI;
}

void button::mode(PinMode mode)
{
    DI.mode(mode);
}

//=====[Implementations of private methods]====================================