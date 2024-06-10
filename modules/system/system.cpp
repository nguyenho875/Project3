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

InterruptIn int_boton_abrir(PIN_BOTON_ABRIR, MODE_PIN_BOTON_ABRIR);
InterruptIn int_boton_cerrar(PIN_BOTON_CERRAR, MODE_PIN_BOTON_CERRAR);

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static Tranquera tranquera(PIN_TRANQUERA);
static Button boton_abrir(PIN_BOTON_ABRIR, MODE_PIN_BOTON_ABRIR);
static Button boton_cerrar(PIN_BOTON_CERRAR, MODE_PIN_BOTON_CERRAR);

//=====[Declarations (prototypes) of private functions]========================

static void int_boton_abrir_callback();
static void int_boton_cerrar_callback();

//=====[Implementations of public functions]===================================

void system_init()
{
    tickInit();

    if(MODE_PIN_BOTON_ABRIR == PullDown){
        int_boton_abrir.rise(&int_boton_abrir_callback);
    }
    else if(MODE_PIN_BOTON_ABRIR == PullUp){
        int_boton_abrir.fall(&int_boton_abrir_callback);
    }

    if(MODE_PIN_BOTON_CERRAR == PullDown){
        int_boton_cerrar.rise(&int_boton_cerrar_callback);
    }
    else if(MODE_PIN_BOTON_CERRAR == PullUp){
        int_boton_cerrar.fall(&int_boton_cerrar_callback);
    }
}

void system_update()
{
    if(system_delay.Read())
    {
        tranquera.update();
    }
}

//=====[Implementations of private functions]==================================

static void int_boton_abrir_callback()
{
    tranquera = ABIERTO;
}

static void int_boton_cerrar_callback()
{
    tranquera = CERRADO;
}