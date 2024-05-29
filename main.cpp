//=====[Libraries]=============================================================

#include "system.h"

//=====[Main function, the program entry point after power on or reset]========

int main()
{
    system_init();
    while (true) {
        system_update();
    }
}