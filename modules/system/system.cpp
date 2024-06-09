//=====[Libraries]=============================================================

#include "arm_book_lib.h"
#include "mbed.h"

#include "system.h"
#include "tranquera.h"
#include "non_blocking_delay.h"
#include "button.h"
#include "_switch.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

nonBlockingDelay system_delay(SYSTEM_TIME_INCREMENT_MS);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static tranquera mi_tranquera(PIN_TRANQUERA);
static button boton_abrir(PIN_BOTON_ABRIR, PullDown);
static button boton_cerrar(PIN_BOTON_CERRAR, PullDown);
static _switch switch_cambiar(D8, PullUp);

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

void system_init()
{
    tickInit();
}

void system_update()
{
    if(system_delay.Read())
    {
        if(boton_abrir){
            mi_tranquera = ABIERTO;
        }
        else if(boton_cerrar){
            mi_tranquera = CERRADO;
        }
        else{

        }
        mi_tranquera.update();
    }
}

//=====[Implementations of private functions]==================================
