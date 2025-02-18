//=====[Libraries]=============================================================

#include "arm_book_lib.h"

#include "ignition_subsystem.h"

#include "alarm.h"
#include "ignition_button.h"
#include "indicator_leds.h"
#include "pc_serial_com.h"
#include "seats_and_seatbelts.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============
bool engineOn = false;

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================
static bool checkSeatsandSeatbelts();
static void ignitionSubsytemTurnOn();
static void ignitionSubsystemTurnOff();

//=====[Implementations of public functions]===================================

void ignitionSubsystemInit()
{
    alarmInit(); 
    ignitionButtonInit();  
    indicatorLedsInit(); 
    seatsAndSeatbeltsInit(); 
}

void ignitionSubsystemUpdate()
{   
    if (!engineOn) {
        checkSeatsandSeatbelts();
        ignitionSubsytemTurnOn();
    }
    else {
        ignitionSubsystemTurnOff();
    }
}

bool engineStateUpdate() {
    return engineOn;
}

//=====[Implementations of private functions]==================================
static bool checkSeatsandSeatbelts() {
    static bool previousdriverSeatState = false; 
    static bool engineReady = false;

    if (driverSeatOccupied() && !previousdriverSeatState) {
        pcSerialComStringWrite( "Welcome to enhanced automobile system model 218-W24\r\n\r\n" );
        previousdriverSeatState = true;  // Set flag to prevent reprinting
    }
    if (driverSeatOccupied() && passengerSeatOccupied() && driverSeatbeltFastened() && passengerSeatbeltFastened()) {
        engineReady = true;
        engineReadyLedUpdate( true );
    }
    return engineReady;
}

static void ignitionSubsytemTurnOn() {
    static bool previousIgnitionButtonState = false; 
    if (!engineOn && ignitionButtonRead() && !previousIgnitionButtonState) {
        if ( checkSeatsandSeatbelts()) {
            alarmOff();
            engineReadyLedUpdate( false );
            engineRunningLedUpdate ( true ) ;
            pcSerialComStringWrite( "Engine started!\r\n" );
            previousIgnitionButtonState = true;  // Set flag to prevent reprinting
            engineOn = true;
        } 
        else {
            alarmOn(); 
            pcSerialComStringWrite( "Ignition inhibited!\r\n" );
            if (!driverSeatOccupied()) {
                pcSerialComStringWrite( "Driver seat not occupied.\r\n" );
            }
            if (!passengerSeatOccupied()) {
                pcSerialComStringWrite( "Passenger seat not occupied.\r\n" );
            }
            if (!driverSeatbeltFastened()) {
                pcSerialComStringWrite( "Driver seatbelt not fastened.\r\n" );
            }
            if (!passengerSeatbeltFastened()) {
                pcSerialComStringWrite( "Passenger seatbelt not fastened.\r\n" );
            }
            previousIgnitionButtonState = true;  // Set flag to prevent reprinting
        }
    }
    if (!engineOn && !ignitionButtonRead()) {
        previousIgnitionButtonState = false;
    }
}

static void ignitionSubsystemTurnOff() {
    static bool engineOffState = false; 

    if (engineOn && ignitionButtonReleasedEventUpdate()) {
        engineOn = false;
        pcSerialComStringWrite( "Engine stopeped!\r\n" );
        engineRunningLedUpdate ( false ) ;
        engineOffState = true;  // Set flag to prevent reprinting
    }
}
