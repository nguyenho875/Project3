//=====[#include guards - begin]===============================================

#ifndef _INDICATOR_LEDS_H_
#define _INDICATOR_LEDS_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================

void indicatorLedsInit();    // initialize green and blue LEDs to off
bool engineReadyLedStateRead();  // return state of engine ready (green) led 
bool engineRunningLedStateRead();  // return state of engine running (blue) led 
void engineReadyLedUpdate( bool state );   // turn on/off green led and update state
void engineRunningLedUpdate( bool state ); // turn on/off blue led and update state
 
//=====[#include guards - end]=================================================

#endif // _INDICATOR_LEDS_H_