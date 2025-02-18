//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "int_delay_selector.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
AnalogIn intDelaySelector(A0);

//=====[Declaration of external public global variables]======================

//=====[Declaration and initialization of public global variables]=============
int intTime = 0;
float potIntRead = 0.0;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================
static float intDelaySelectorRead();

//=====[Implementations of public functions]===================================
int intDelaySelectorUpdate() {
    float potIntRead = intDelaySelectorRead();

    if (potIntRead < 0.3) {
        intTime = 3000;
    } 
    else if (potIntRead >= 0.3 && potIntRead <= 0.6) {
        intTime = 6000;
    }
    else{
        intTime = 8000;
    }
    return intTime;
}

//=====[Implementations of private functions]==================================
static float intDelaySelectorRead() {
    return intDelaySelector.read();
}
