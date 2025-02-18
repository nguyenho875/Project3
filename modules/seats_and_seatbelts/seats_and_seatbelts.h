//=====[#include guards - begin]===============================================

#ifndef _SEATS_AND_SEATBELTS_H_
#define _SEATS_AND_SEATBELTS_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declarations (prototypes) of public functions]=========================
void seatsAndSeatbeltsInit();      // initialize seat buttons with pulldown mode
bool driverSeatOccupied();         // return state of driver seat
bool passengerSeatOccupied();      // return state of passenger seat
bool driverSeatbeltFastened();     // return state of driver seatbelt
bool passengerSeatbeltFastened();  // return state of passenger seatbelt

//=====[#include guards - end]=================================================

#endif // _SEATS_AND_SEATBELTS_H_