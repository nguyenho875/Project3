//=====[#include guards - begin]===============================================

#ifndef _PC_SERIAL_COM_H_
#define _PC_SERIAL_COM_H_

//==================[Libraries]===============================================

#include "mbed.h"
#include "arm_book_lib.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

//=====[Declaration of public classes]=========================================

class SerialCom
{
    public:
        // Crea el puerto serie
        SerialCom(PinName Tx, PinName Rx, int baudrate);

        // Lee un caracter
        char pcSerialComCharRead();

        // Escribe un string
        void pcSerialComStringWrite(const char* str);

        // Setea el led en ON / OFF
        void write(int value);

        // Lee el valor del led
        int read();

        // Sobrecarga del operador = para escribir
        SerialCom &operator= (const char* str)
        {
            pcSerialComStringWrite(str);
            return *this;
        }

        // Sobrecarga de char() para leer
        operator char()
        {
            return pcSerialComCharRead();
        }

    private:
        // Serial port
        UnbufferedSerial serial_com;

};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================

#endif // _PC_SERIAL_COM_H_