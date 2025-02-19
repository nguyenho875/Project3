//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "int_delay_selector.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
AnalogIn intDelaySelector(A2);

//=====[Declaration of external public global variables]======================

//=====[Declaration and initialization of public global variables]=============
int intTimeMotor = 0;
int intTimeDisplay = 0;
float potIntRead = 0.0;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================
static float intDelaySelectorRead();

//=====[Implementations of public functions]===================================
int intDelaySelectorMotorUpdate() {
    float potIntRead = intDelaySelectorRead();

    if (potIntRead < 0.1) {
        intTimeMotor = 167; //approximated from testing with motor using timer
    } 
    else if (potIntRead >= 0.1 && potIntRead <= 0.2) {
        intTimeMotor = 333; //approximated from testing with motor using timer
    }
    else{
        intTimeMotor = 445; //approximated from testing with motor using timer
    }
    return intTimeMotor;
}

int intDelaySelectorDisplayUpdate() {
    float potIntRead = intDelaySelectorRead();

    if (potIntRead < 0.1) {
        intTimeDisplay = 3;
    } 
    else if (potIntRead >= 0.1 && potIntRead <= 0.2) {
        intTimeDisplay = 6;
    }
    else{
        intTimeDisplay = 8;
    }
    return intTimeDisplay;
}

//=====[Implementations of private functions]==================================
static float intDelaySelectorRead() {
    return intDelaySelector.read();
}
