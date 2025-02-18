//=====[#include guards - begin]===============================================

#ifndef _MOTOR_H_
#define _MOTOR_H_

//=====[Declaration of public defines]=========================================
#define DUTY_MIN 0.0375      // duty cycle at 0 degrees
#define DUTY_MAX 0.0654167   // duty cycle at 67 degrees
#define DUTY_STEP 0.0004167  // duty cycle for 1 degree step increase

#define PERIOD 0.02

#define HIGH_DELAY_MS 4    // delay time between each 1 degree step for high speed
#define LOW_DELAY_MS 6     // delay time between each 1 degree step for low speed

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================
void motorInit();       // initialize motor, set up at 0 degrees
void motorOff();        // keep motor at 0 degrees

// runs motor at high speed, 
// stops motor at 0 degrees when ignition button is pressed and released (shutdown requested)
// or when mode selector is turned to OFF
void motorRunHigh();   

// runs motor at low speed, 
// stops motor at 0 degrees when ignition button is pressed and released (shutdown requested),
// or when mode selector is turned to OFF
void motorRunLow();

// runs motor at low speed with intermittent delay is the parameter intTime, 
// stops motor at 0 degrees when ignition button is pressed and released (shutdown requested)
// or when mode selector is turned to OFF
void motorRunInt(int intTime);

//=====[#include guards - end]=================================================

#endif // _MOTOR_H_