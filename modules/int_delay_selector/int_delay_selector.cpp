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
int intTime = 0;
int timeDisplay = 0;
float potIntRead = 0.0;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================
static float intDelaySelectorRead();

//=====[Implementations of public functions]===================================
int intDelaySelectorUpdate() {
    float potIntRead = intDelaySelectorRead();

    if (potIntRead < 0.1) {
        intTime = 167;
    } 
    else if (potIntRead >= 0.1 && potIntRead <= 0.2) {
        intTime = 333;
    }
    else{
        intTime = 445;
    }
    return intTime;
}

int intDelaySelectorDisplay() {
    float potIntRead = intDelaySelectorRead();

    if (potIntRead < 0.1) {
        timeDisplay = 3;
    } 
    else if (potIntRead >= 0.1 && potIntRead <= 0.2) {
        timeDisplay = 6;
    }
    else{
        timeDisplay = 8;
    }
    return timeDisplay;
}

//=====[Implementations of private functions]==================================
static float intDelaySelectorRead() {
    return intDelaySelector.read();
}
