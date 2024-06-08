//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "system.h"
#include "led.h"
#include "non_blocking_delay.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

nonBlockingDelay system_delay(SYSTEM_TIME_INCREMENT_MS);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static led mi_led(D0);

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void system_init()
{
    tickInit();
}

void system_update()
{
    if(system_delay.Read())
    {
    mi_led = !mi_led;
    }
}

//=====[Implementations of private functions]==================================
