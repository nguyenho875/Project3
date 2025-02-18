//=====[Libraries]=============================================================
#include "mbed.h"
#include "arm_book_lib.h"

#include "vehicle_control_system.h"

#include "ignition_subsystem.h"
#include "wiper_subsystem.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void vehicleControlSystemInit()
{
    ignitionSubsystemInit();
    wiperSubsystemInit();
}

void vehicleControlSystemUpdate()
{
    ignitionSubsystemUpdate();
    wiperSubsystemUpdate();
    delay(SYSTEM_TIME_INCREMENT_MS);
}

//=====[Implementations of private functions]==================================
