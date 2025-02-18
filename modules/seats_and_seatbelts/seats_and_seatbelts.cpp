//=====[Libraries]=============================================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "seats_and_seatbelts.h"
//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============
DigitalIn driverSeat(D10);
DigitalIn passengerSeat(D11);
DigitalIn driverSeatbelt(D12);
DigitalIn passengerSeatbelt(D13);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void seatsAndSeatbeltsInit() {  
    driverSeat.mode(PullDown); 
    passengerSeat.mode(PullDown); 
}

bool driverSeatOccupied() {
    return driverSeat;
}

bool passengerSeatOccupied() {
    return passengerSeat;
}

bool driverSeatbeltFastened() {
    return driverSeatbelt;
}

bool passengerSeatbeltFastened() {
    return passengerSeatbelt;
}
//=====[Implementations of private functions]===================================