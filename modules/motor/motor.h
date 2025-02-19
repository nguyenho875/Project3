//=====[#include guards - begin]===============================================

#ifndef _MOTOR_H_
#define _MOTOR_H_

//=====[Declaration of public defines]=========================================
#define DUTY_MIN 0.0375      // duty cycle at 0 degrees
#define DUTY_MAX 0.0654167   // duty cycle at 67 degrees
#define DUTY_STEP 0.004  // duty cycle for 1 degree step increase

#define PERIOD 0.02

#define HIGH_DELAY_MS 2    // delay time between each 1 degree step for high speed
#define LOW_DELAY_MS 3     // delay time between each 1 degree step for low speed

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================
void motorInit();       // initializes motor, set up at 0 degrees

void motorOff();        // returns motor to 0 degrees

void motorRunHigh();    // runs motor at high speed 

void motorRunLow();   // runs motor at low speed

void motorRunInt(int intTime);  // runs motor at low speed with intermittent delay is the parameter intTime

//=====[#include guards - end]=================================================

#endif // _MOTOR_H_