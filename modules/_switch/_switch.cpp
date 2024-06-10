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

_Switch::_Switch(PinName pin): DI(pin)
{
}

_Switch::_Switch(PinName pin, PinMode mode): DI(pin, mode)
{
}

int _Switch::read()
{
    return DI;
}

void _Switch::mode(PinMode mode)
{
    DI.mode(mode);
}

//=====[Implementations of private methods]====================================