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
static void ignitionSubsystemToggle();

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
    checkSeatsandSeatbelts();
    ignitionSubsystemToggle(); 
}

bool engineStateUpdate() {
    return engineOn;
}

//=====[Implementations of private functions]==================================
static bool checkSeatsandSeatbelts() {
    static bool welcomeMessageSent = false; // Tracks if the message has been sent before
    bool engineReady = false;

    // Print welcome message when the driver sits down
    if (driverSeatOccupied() && !welcomeMessageSent) {
        pcSerialComStringWrite("Welcome to enhanced automobile system model 218-W24\r\n");
        welcomeMessageSent = true; // Prevents further messages
    }

    // Check if all conditions are met for the engine to be ready
    if (driverSeatOccupied() && passengerSeatOccupied() && driverSeatbeltFastened() && passengerSeatbeltFastened()) {
        engineReady = true;
        engineReadyLedUpdate(true);
    } else {
        engineReadyLedUpdate(false);
    }

    return engineReady;
}

static void ignitionSubsystemToggle() {
    static bool previousIgnitionButtonState = false;
    static bool engineToggleRequested = false; 
    // Tracks if we're waiting for the next button press to toggle engine state

    bool currentIgnitionButtonState = ignitionButtonRead();

    if (currentIgnitionButtonState && !previousIgnitionButtonState) {

        if (!engineOn) { 
            if (checkSeatsandSeatbelts()) {
                alarmOff();
                engineReadyLedUpdate(false);
                engineRunningLedUpdate(true);
                pcSerialComStringWrite("Engine started!\r\n");
                engineOn = true;
            } 
            else {
                alarmOn();
                pcSerialComStringWrite("Ignition inhibited!\r\n");

                if (!driverSeatOccupied()) {
                    pcSerialComStringWrite("Driver seat not occupied.\r\n");
                }
                if (!passengerSeatOccupied()) {
                    pcSerialComStringWrite("Passenger seat not occupied.\r\n");
                }
                if (!driverSeatbeltFastened()) {
                    pcSerialComStringWrite("Driver seatbelt not fastened.\r\n");
                }
                if (!passengerSeatbeltFastened()) {
                    pcSerialComStringWrite("Passenger seatbelt not fastened.\r\n");
                }
            }
        } else { // Engine is ON, mark request to turn OFF
            engineToggleRequested = true;
        }
    }

    // Detect button release event after requesting toggle
    if (!currentIgnitionButtonState && previousIgnitionButtonState) {
        if (engineOn && engineToggleRequested) { // Only turn OFF if it was requested
            engineOn = false;
            engineRunningLedUpdate(false);
            pcSerialComStringWrite("Engine stopped!\r\n");
            engineToggleRequested = false; // Reset toggle request
        }
    }
    // Update previous button state
    previousIgnitionButtonState = currentIgnitionButtonState;
}
