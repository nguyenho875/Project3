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

char SerialCom::char_read()
{
    char receivedChar = '\0';
    if( serial_com.readable() ) {
        serial_com.read( &receivedChar, 1 );
    }
    return receivedChar;
}

void SerialCom::string_write( const char* str )
{
    serial_com.write( str, strlen(str) );
}

void SerialCom::float_write( const float str)
{
    char aux[100] = "";
    sprintf(aux, "%f \n", str);
    serial_com.write( aux, strlen(aux) );
}

void SerialCom::int_write( const int str )
{
    char aux[100] = "";
    sprintf(aux, "%d \n", str);
    serial_com.write( aux, strlen(aux) );
}

void SerialCom::byte_write( const uint8_t str )
{
    char aux[100] = "";
    sprintf(aux, "%X", str);
    serial_com.write( aux, strlen(aux) );
}

//=====[Implementations of private methods]====================================