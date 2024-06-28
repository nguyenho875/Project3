//=====[#include guards - begin]===============================================

#ifndef _PC_SERIAL_COM_H_
#define _PC_SERIAL_COM_H_

//==================[Libraries]===============================================

#include "mbed.h"
#include "arm_book_lib.h"
//#include <string>

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declaration of public classes]=========================================

class SerialCom
{
    public:
        // Crea el puerto serie
        SerialCom(PinName Tx, PinName Rx, int baudrate);

        // Lee un caracter
        char char_read();

        //
        int string_read(char* buf, int buf_size, int timeout_ms);

        // Escribe un string
        void string_write(const char* str);

        // Escribe un float
        void float_write(const float str);

        // Escribe un int
        void int_write(const int str);

        // Escribe un byte en hexadecimal
        void byte_write(const uint8_t str);

        // Sobrecarga de char() para leer
        operator char()
        {
            return char_read();
        }

    private:
        // Serial port
        UnbufferedSerial serial_com;

};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================

#endif // _PC_SERIAL_COM_H_