//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "wiper_subsystem.h"

#include "display.h"
#include "ignition_button.h"       // need ignitionButtonReleasedEventUpdate()
#include "ignition_subsystem.h"    // need engineStateUpdate()
#include "int_delay_selector.h"
#include "motor.h"
#include "vehicle_control_system.h"
#include "wiper_mode_selector.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================
static void lcdDisplayInit();

//=====[Implementations of public functions]===================================

void wiperSubsystemInit()
{
    lcdDisplayInit();
    motorInit();  
}

void wiperSubsystemUpdate() 
{
    //static bool motorStopping = false;
    static int lastSpeedMode = LOW_MODE; // Store last mode before OFF

    if (!engineStateUpdate() || wiperModeSelectorUpdate() == OFF_MODE) {  
        motorOff();
        displayCharPositionWrite(12, 0);
        displayStringWrite("OFF ");
        displayCharPositionWrite(11, 1);
        displayStringWrite("-    ");
        return;  
    }
    else if (wiperModeSelectorUpdate() == LOW_MODE) {
        motorRunLow();
        displayCharPositionWrite(12, 0);
        displayStringWrite("LOW ");
        displayCharPositionWrite(11, 1);
        displayStringWrite("-    ");
    }
    else if (wiperModeSelectorUpdate() == HIGH_MODE) {
        motorRunHigh();
        displayCharPositionWrite(12, 0);
        displayStringWrite("HIGH");
        displayCharPositionWrite(11, 1);
        displayStringWrite("-    ");
    }
    else if (wiperModeSelectorUpdate() == INT_MODE) {
        motorRunInt(intDelaySelectorMotorUpdate());
        displayCharPositionWrite(12, 0);
        displayStringWrite("INT ");

        char intString[10];
        sprintf(intString, "%d", intDelaySelectorDisplayUpdate());
        displayCharPositionWrite(11, 1);
        displayStringWrite(intString);
        displayCharPositionWrite(12, 1);
        displayStringWrite("s");

    }
}

//=====[Implementations of private functions]==================================
static void lcdDisplayInit()
{
    displayInit();
     
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Wiper mode: " );
    
    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "Int Delay: " );
}

