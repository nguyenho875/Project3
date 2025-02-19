//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "alarm.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalInOut alarm(PE_10); 

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============
bool alarmState = OFF;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void alarmInit()
{
    alarm.mode(OpenDrain);
    alarm.input();
}

void alarmOn() 
{
    alarm.output();
    alarm = LOW; 
    alarmState = ON;
}

void alarmOff() 
{
    alarm.input();
    alarmState = OFF;
}

//=====[Implementations of private functions]==================================

