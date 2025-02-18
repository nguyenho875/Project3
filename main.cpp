//=====[Libraries]=============================================================

#include "vehicle_control_system.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    vehicleControlSystemInit();
    while (true) {
        vehicleControlSystemUpdate();
    }
}