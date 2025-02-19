//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "indicator_leds.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalOut engineReadyLed(LED1);
DigitalOut engineRunningLed(LED2);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============
bool engineReadyLedState = OFF;
bool engineRunningLedState = OFF;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void indicatorLedsInit()
{
    engineReadyLed = OFF;
    engineRunningLed = OFF;
}

void engineReadyLedUpdate( bool state )
{
    engineReadyLed = state;
    engineReadyLedState = state;
}

void engineRunningLedUpdate( bool state )
{
    engineRunningLed = state;
    engineRunningLedState = state;
}

//=====[Implementations of private functions]==================================

