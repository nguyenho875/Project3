//=====[#include guards - begin]===============================================

#ifndef _IGNITION_SUBSYSTEM_H_
#define _IGNITION_SUBSYSTEM_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================
void ignitionSubsystemInit();     // initializes all components of ignition subsystem
void ignitionSubsystemUpdate();   // handles turning on system, and turning off subsystem
bool engineStateUpdate();         // returns state of engine 

//=====[#include guards - end]=================================================

#endif // _IGNITION_SUBSYSTEM_H_