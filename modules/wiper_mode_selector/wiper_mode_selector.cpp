//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "wiper_mode_selector.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

AnalogIn wiperModeSelector(A1);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============
wiperMode_t wiperMode = OFF;
float potRead = 0.0;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================
static float wiperModeSelectorRead();

//=====[Implementations of public functions]===================================
wiperMode_t wiperModeSelectorUpdate() {
    potRead = wiperModeSelectorRead();
    
    if (potRead <= 0.25) {
        wiperMode = OFF;
    } 
    else if (potRead > 0.25 && potRead <= 0.5) {
        wiperMode = LOW;
    }
    else if (potRead > 0.5 && potRead <= 0.75) {
        wiperMode = HIGH;
    }
    else {
        wiperMode = INT;
    }
    return wiperMode;
}

//=====[Implementations of private functions]==================================
static float wiperModeSelectorRead() {
    return wiperModeSelector.read();
}
