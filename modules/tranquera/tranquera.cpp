//=====[Libraries]=============================================================

#include "tranquera.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

position_t position;

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

//=====[Implementations of private functions]==================================

//=====[Implementations of public methods]=====================================

Tranquera::Tranquera(PinName pin_tranquera, PinName pin_boton_abrir, PinMode mode_boton_abrir, PinName pin_boton_cerrar, PinMode mode_boton_cerrar): 
                output(pin_tranquera), int_boton_abrir(pin_boton_abrir, mode_boton_abrir), int_boton_cerrar(pin_boton_cerrar, mode_boton_cerrar)
{
    // Se inicializa en CERRADO
    Tranquera::update_position(CERRADO);

    int_boton_abrir.rise(callback(this, &Tranquera::int_boton_abrir_callback));
    int_boton_cerrar.rise(callback(this, &Tranquera::int_boton_cerrar_callback));
}

Tranquera::Tranquera(PinName pin_tranquera, int value, PinName pin_boton_abrir, PinMode mode_boton_abrir, PinName pin_boton_cerrar, PinMode mode_boton_cerrar):
                output(pin_tranquera, value), int_boton_abrir(pin_boton_abrir, mode_boton_abrir), int_boton_cerrar(pin_boton_cerrar, mode_boton_cerrar)
{
    if(value == OFF){
        Tranquera::update_position(CERRADO);
    }
    else{
        Tranquera::update_position(ABIERTO);
    }

    int_boton_abrir.rise(callback(this, &Tranquera::int_boton_abrir_callback));
    int_boton_cerrar.rise(callback(this, &Tranquera::int_boton_cerrar_callback));
}

void Tranquera::update_position(position_t new_position)
{
    position = new_position;
    switch (position){
        case ABIERTO:
            output = ON;
            break;
        case CERRADO:
            output = OFF;
            break;
        default:
            break;
    }

    this->position_changed = true;
}


position_t Tranquera::read()
{
    return position;
}

//=====[Implementations of private methods]====================================

void Tranquera::int_boton_abrir_callback()
{
    Tranquera::update_position(ABIERTO);
}

void Tranquera::int_boton_cerrar_callback()
{
    Tranquera::update_position(CERRADO);
}