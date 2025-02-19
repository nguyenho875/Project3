//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "motor.h"
#include "vehicle_control_system.h"
#include "ignition_button.h"
#include "ignition_subsystem.h"
#include "wiper_mode_selector.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
PwmOut motor(PF_9);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================
void motorInit() {
    motor.period(PERIOD); 
    motor.write(DUTY_MIN);
}

void motorOff() {
    motor.write(DUTY_MIN);
}

void motorRunHigh() {
    static int accumulatedTime = 0;
    static float duty = DUTY_MIN;  
    static float dutyStep = DUTY_STEP; 

    accumulatedTime += SYSTEM_TIME_INCREMENT_MS;

    if (accumulatedTime >= HIGH_DELAY_MS) {
        accumulatedTime = 0;

        motor.write(duty);
        duty += dutyStep;

        if (duty >= DUTY_MAX || duty <= DUTY_MIN) {
            dutyStep = -dutyStep;
        }
    }
}

void motorRunLow() {
    static int accumulatedTime = 0;
    static float duty = DUTY_MIN;  
    static float dutyStep = DUTY_STEP; 

    accumulatedTime += SYSTEM_TIME_INCREMENT_MS;

    if (accumulatedTime >= LOW_DELAY_MS) {
        accumulatedTime = 0;
        
        motor.write(duty);
        duty += dutyStep;

        if (duty >= DUTY_MAX || duty <= DUTY_MIN) {
            dutyStep = -dutyStep;

        }
    }
}

void motorRunInt(int intTime) {
    static int accumulatedTimeDuty = 0;
    static int accumulatedTimeInt = 0;
    static float duty = DUTY_MIN;  
    static float dutyStep = DUTY_STEP; 
    static int turns = 0;

    accumulatedTimeInt += SYSTEM_TIME_INCREMENT_MS;
    accumulatedTimeDuty += SYSTEM_TIME_INCREMENT_MS;

    if (accumulatedTimeDuty >= LOW_DELAY_MS && turns < 2) {
        accumulatedTimeDuty = 0;
        motor.write(duty);
        duty += dutyStep;

        if (duty >= DUTY_MAX || duty <= DUTY_MIN) {
            dutyStep = -dutyStep;
            turns++;
        }
    }

    if (turns >= 2) {
        duty = DUTY_MIN;
        motor.write(duty);
    }

    if (accumulatedTimeInt >= intTime) {
        accumulatedTimeInt = 0;
        accumulatedTimeDuty = 0;
        turns = 0;
        duty = DUTY_MIN;
        dutyStep = DUTY_STEP;
    }
}

//=====[Implementations of private functions]==================================