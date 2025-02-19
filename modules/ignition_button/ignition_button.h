//=====[#include guards - begin]===============================================

#ifndef _IGNITION_BUTTON_H_
#define _IGNITION_BUTTON_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================
typedef enum {
    BUTTON_UP,
    BUTTON_DOWN
} buttonState_t;

//=====[Declarations (prototypes) of public functions]=========================

void ignitionButtonInit();                // initialize ignition button
bool ignitionButtonRead();                // read state of button (pressed or released)
bool ignitionButtonReleasedEventUpdate(); // detect ignition button when pressed and released (to turn off engine)

//=====[#include guards - end]=================================================

#endif // _IGNITION_BUTTON_H_