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
static void userInterfaceDisplayInit();

//=====[Implementations of public functions]===================================

void wiperSubsystemInit()
{
    userInterfaceDisplayInit();
    motorInit();  
}

void wiperSubsystemUpdate() 
{
    if (!engineStateUpdate() || wiperModeSelectorUpdate() == OFF) {
        displayCharPositionWrite ( 12,0 );
        displayStringWrite( "OFF" );
        displayCharPositionWrite ( 11,1 );
        displayStringWrite( "-" );
        // mechanism to turn off motor while running is already implemented in motorRun functions
    }
    else if (engineStateUpdate() && wiperModeSelectorUpdate() == LOW) {
        motorRunLow();
        displayCharPositionWrite ( 12,0 );
        displayStringWrite( "LOW" );
        displayCharPositionWrite ( 11,1 );
        displayStringWrite( "-" );
    }
    else if (engineStateUpdate() && wiperModeSelectorUpdate() == HIGH) {
        motorRunHigh();
        displayCharPositionWrite ( 12,0 );
        displayStringWrite( "HIGH" );
        displayCharPositionWrite ( 11,1 );
        displayStringWrite( "-" );
    }
    else if (engineStateUpdate() && wiperModeSelectorUpdate() == INT) {
        motorRunInt(int intDelaySelectorUpdate());
        displayCharPositionWrite ( 12,0 );
        displayStringWrite( "INT" );

        sprintf(intString, "%d", intDelaySelectorUpdate());
        displayCharPositionWrite ( 11,1 );
        displayStringWrite( intString );
    }
}

//=====[Implementations of private functions]==================================
static void userInterfaceDisplayInit()
{
    displayInit();
     
    displayCharPositionWrite ( 0,0 );
    displayStringWrite( "Wiper mode: " );
    
    displayCharPositionWrite ( 0,1 );
    displayStringWrite( "Int Delay: " );
}
