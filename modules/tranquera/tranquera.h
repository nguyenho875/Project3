//=====[#include guards - begin]===============================================

#ifndef _TRANQUERA_H_
#define _TRANQUERA_H_

//==================[Libraries]===============================================

#include "mbed.h"
#include "arm_book_lib.h"

#include "led.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef enum{
    CERRADO,
    ABIERTO
} position_t;

//=====[Declaration of public classes]=========================================

class Tranquera
{
    public:
        // Crea la tranquera y la inicializa cerrada
        Tranquera(PinName pin_tranquera, PinName pin_boton_abrir, PinMode mode_boton_abrir, PinName pin_boton_cerrar, PinMode mode_boton_cerrar);

        // Crea la tranquera y le indica el valor de inicio (ON=abierto / OFF=cerrado)
        Tranquera(PinName pin_tranquera, int value, PinName pin_boton_abrir, PinMode mode_boton_abrir, PinName pin_boton_cerrar, PinMode mode_boton_cerrar);

        // 
        void update_position(position_t new_position);

        // Lee el valor de la tranquera
        position_t read();

        // Sobrecarga del operador = para escribir
        Tranquera &operator= (position_t new_position)
        {
            update_position(new_position);
            return *this;
        }

        // Sobrecarga de int() para leer
        operator int()
        {
            return read();
        }

    private:
        // leds de salida
        Led output;

        //
        InterruptIn int_boton_abrir;
        InterruptIn int_boton_cerrar;

        void int_boton_abrir_callback();
        void int_boton_cerrar_callback();

};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================

#endif // _TRANQUERA_H_