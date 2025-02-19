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
wiperMode_t wiperMode = OFF_MODE;
float potWiperRead = 0.0;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================
static float wiperModeSelectorRead();

//=====[Implementations of public functions]===================================
wiperMode_t wiperModeSelectorUpdate() {
    potWiperRead = wiperModeSelectorRead();
    
    if (potWiperRead <= 0.05) {
        wiperMode = OFF_MODE;
    } 
    else if (potWiperRead > 0.05 && potWiperRead <= 0.15) {
        wiperMode = LOW_MODE;
    }
    else if (potWiperRead > 0.15 && potWiperRead <= 0.375) {
        wiperMode = HIGH_MODE;
    }
    else {
        wiperMode = INT_MODE;
    }
    return wiperMode;
}

//=====[Implementations of private functions]==================================
static float wiperModeSelectorRead() {
    return wiperModeSelector.read();
}
