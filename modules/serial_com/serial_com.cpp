//=====[Libraries]=============================================================

#include "serial_com.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

//=====[Implementations of private functions]==================================

//=====[Implementations of public methods]=====================================

SerialCom::SerialCom(PinName Tx, PinName Rx, int baudrate): serial_com(Tx, Rx, baudrate)
{
}

char SerialCom::pcSerialComCharRead()
{
    char receivedChar = '\0';
    if( serial_com.readable() ) {
        serial_com.read( &receivedChar, 1 );
    }
    return receivedChar;
}

void SerialCom::pcSerialComStringWrite( const char* str )
{
    serial_com.write( str, strlen(str) );
}

//=====[Implementations of private methods]====================================