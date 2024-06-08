//=====[Libraries]=============================================================

#include "_switch.h"

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

_switch::_switch(PinName pin): DI(pin)
{
}

_switch::_switch(PinName pin, PinMode mode): DI(pin, mode)
{
}

int _switch::read()
{
    return DI;
}

void _switch::mode(PinMode mode)
{
    DI.mode(mode);
}

//=====[Implementations of private methods]====================================