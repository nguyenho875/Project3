/*//=====[#include guards - begin]===============================================

#ifndef __NON_BLOCKING_DELAY_H_
#define __NON_BLOCKING_DELAY_H_

//==================[Libraries]===============================================

#include "mbed.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef uint64_t tick_t;

//=====[Declaration of public classes]=========================================

class nonBlockingDelay {
    public:
        nonBlockingDelay(tick_t durationValue);
        void Start();
        void Start(tick_t new_duration);
        bool Read();
        void Write(tick_t durationValue);
    private:
        tick_t startTime;
        tick_t duration;
        bool isRunning;

};

//=====[Declarations (prototypes) of public functions]=========================

void tickInit();

//=====[#include guards - end]=================================================

#endif // __NON_BLOCKING_DELAY_H_*/