//=====[#include guards - begin]===============================================

#ifndef _NON_BLOCKING_DELAY_H_
#define _NON_BLOCKING_DELAY_H_

//==================[Libraries]===============================================

#include "mbed.h"

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================

typedef uint64_t tick_t;

//=====[Declaration of public classes]=========================================

class nonBlockingDelay {
    public:
        nonBlockingDelay(tick_t durationValue);
        nonBlockingDelay(tick_t durationValue, Callback<void()> cb);
        void Start();
        void Start(tick_t new_duration);
        void Start(tick_t new_duration, Callback<void()> cb);
        void Start(Callback<void()> cb);
        bool isReady();
        void SetDuration(tick_t durationValue);
        void SetCallback(Callback<void()> cb);
    private:
        tick_t startTime;
        tick_t duration;
        bool isRunning;
        Callback<void()> my_callback;
        Ticker ticker;
        Ticker ready_ticker;

        void tickerCallback();
        void readyTickerCallback();
        
};

//=====[Declarations (prototypes) of public functions]=========================

//=====[#include guards - end]=================================================

#endif // _NON_BLOCKING_DELAY_H_
