//=====[Libraries]=============================================================

#include "non_blocking_delay.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

//=====[Declarations (prototypes) of private functions]========================

//=====[Implementations of public functions]===================================

//=====[Implementations of private functions]==================================

//=====[Implementations of public methods]=====================================

nonBlockingDelay::nonBlockingDelay(tick_t durationValue)
{
    //globalTicker.attach(callback(this, &nonBlockingDelay::globalTickerCallback), 1ms);
    nonBlockingDelay::SetDuration(durationValue);
    nonBlockingDelay::SetCallback(nullptr);
    this->isRunning = false;
}

nonBlockingDelay::nonBlockingDelay(tick_t durationValue, Callback<void()> cb)
{
    //globalTicker.attach(callback(this, &nonBlockingDelay::globalTickerCallback), 1ms);
    nonBlockingDelay::SetDuration(durationValue);
    nonBlockingDelay::SetCallback(cb);
    this->isRunning = false;
}

void nonBlockingDelay::Start()
{
    //this->startTime = tickCounter;
    this->isRunning = true;
    if(this->my_callback){
        this->ticker.attach(callback(this, &nonBlockingDelay::tickerCallback), std::chrono::milliseconds(this->duration));
    }
    this->ready_ticker.attach(callback(this, &nonBlockingDelay::readyTickerCallback), std::chrono::milliseconds(this->duration));
}

void nonBlockingDelay::Start(tick_t new_duration)
{
    //this->startTime = tickCounter;
    this->isRunning = true;
    nonBlockingDelay::SetDuration(new_duration);
    if(this->my_callback){
        this->ticker.attach(callback(this, &nonBlockingDelay::tickerCallback), std::chrono::milliseconds(this->duration));
    }
    this->ready_ticker.attach(callback(this, &nonBlockingDelay::readyTickerCallback), std::chrono::milliseconds(this->duration));
}

void nonBlockingDelay::Start(tick_t new_duration, Callback<void()> cb)
{
    //this->startTime = tickCounter;
    this->isRunning = true;
    nonBlockingDelay::SetDuration(new_duration);
    nonBlockingDelay::SetCallback(cb);
    this->ticker.attach(callback(this, &nonBlockingDelay::tickerCallback), std::chrono::milliseconds(this->duration));
    this->ready_ticker.attach(callback(this, &nonBlockingDelay::readyTickerCallback), std::chrono::milliseconds(this->duration));
}

void nonBlockingDelay::Start(Callback<void()> cb)
{
    //this->startTime = tickCounter;
    this->isRunning = true;
    nonBlockingDelay::SetCallback(cb);
    this->ticker.attach(callback(this, &nonBlockingDelay::tickerCallback), std::chrono::milliseconds(this->duration));
    this->ready_ticker.attach(callback(this, &nonBlockingDelay::readyTickerCallback), std::chrono::milliseconds(this->duration));
}

bool nonBlockingDelay::isReady()
{
    return !this->isRunning;
}

void nonBlockingDelay::SetDuration(tick_t durationValue)
{
   this->duration = durationValue;
}

void nonBlockingDelay::SetCallback(Callback<void()> cb)
{
   this->my_callback = cb;
   if(!this->my_callback){
       this->ticker.detach();
   }
}

//=====[Implementations of private methods]====================================

//void nonBlockingDelay::globalTickerCallback(void) 
//{
//    this->tickCounter++;
//}

void nonBlockingDelay::tickerCallback()
{
    if (this->my_callback) {
        this->my_callback();
    }
}

void nonBlockingDelay::readyTickerCallback()
{
    this->isRunning = false;
}