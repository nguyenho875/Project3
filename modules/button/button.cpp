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

Button::Button(PinName pin): DI(pin)
{
}

Button::Button(PinName pin, PinMode mode): DI(pin, mode)
{
}

int Button::read()
{
    return DI;
}

void Button::mode(PinMode mode)
{
    DI.mode(mode);
}

//=====[Implementations of private methods]====================================