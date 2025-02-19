//=====[Libraries]=============================================================
#include "arm_book_lib.h"
#include "mbed.h"

#include "ignition_button.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

DigitalIn ignitionButton(BUTTON1);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============
buttonState_t ignitionButtonState;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void ignitionButtonInit() {
    ignitionButton.mode(PullDown);
    if( ignitionButton == 1) {
        ignitionButtonState = BUTTON_DOWN;
    } else {
        ignitionButtonState = BUTTON_UP;
    }
}

bool ignitionButtonRead() {
    return (ignitionButton == 1);
}

bool ignitionButtonReleasedEventUpdate()
{
    bool ignitionButtonReleasedEvent = false;
    switch( ignitionButtonState ) {

    case BUTTON_UP:
        if( ignitionButton == 1) {
            ignitionButtonState = BUTTON_DOWN;
        }
        break;

    case BUTTON_DOWN:
        if( ignitionButton == 0 ) {
            ignitionButtonState = BUTTON_UP;
            ignitionButtonReleasedEvent = true;
        }
        break;

    default:
        ignitionButtonInit();
        break;
    }
    return ignitionButtonReleasedEvent;
}

//=====[Implementations of private functions]==================================
