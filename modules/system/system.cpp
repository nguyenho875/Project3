//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "system.h"
#include "led.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static led mi_led(D0);

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void system_init()
{
}

void system_update()
{
    mi_led = ON;
    delay(100);
    mi_led = OFF;
    delay(100);
}

//=====[Implementations of private functions]==================================
