//=====[Libraries]=============================================================

//#include "smart_home_system.h"
#include "system.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    //smartHomeSystemInit();
    system_init();
    while (true) {
        //smartHomeSystemUpdate();
        system_update();
    }
}