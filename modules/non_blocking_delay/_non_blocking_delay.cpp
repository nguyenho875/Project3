/*//=====[Libraries]=============================================================

#include "_non_blocking_delay.h"

//=====[Declaration of private defines]========================================

//=====[Declaration of private data types]=====================================

//=====[Declaration and initialization of public global objects]===============

//=====[Declaration of external public global variables]=======================

//=====[Declaration and initialization of public global variables]=============

//=====[Declaration and initialization of private global variables]============

static Ticker ticker;
static tick_t tickCounter;

//=====[Declarations (prototypes) of private functions]========================

 void tickerCallback();

//=====[Implementations of public functions]===================================


void tickInit()
{
    ticker.attach( tickerCallback, 1ms);
}

//=====[Implementations of private functions]==================================

void tickerCallback( void ) 
{
    tickCounter++;
}

//=====[Implementations of public methods]=====================================

nonBlockingDelay::nonBlockingDelay(tick_t durationValue)
{
   duration = durationValue;
   isRunning = false;
}

void nonBlockingDelay::Start()
{
    this->startTime = tickCounter;
    this->isRunning = true;
}

void nonBlockingDelay::Start(tick_t new_duration)
{
    this->startTime = tickCounter;
    this->isRunning = true;
    this->duration = new_duration;
}
*/
/*
bool nonBlockingDelay::Read( )
{
   bool timeArrived = false;
   tick_t elapsedTime;

   if( !this->isRunning ) {
      this->startTime = tickCounter;
      this->isRunning = true;
   } else {
      elapsedTime = tickCounter - this->startTime;
      if ( elapsedTime >= this->duration ) {
         timeArrived = true;
         this->isRunning = false;
      }
   }

   return timeArrived;
}
*/
/*
bool nonBlockingDelay::Read( )
{
    bool timeArrived = false;
    tick_t elapsedTime = tickCounter - this->startTime;

    if ( elapsedTime >= this->duration ) {
        timeArrived = true;
        this->isRunning = false;
    }

    return timeArrived;
}

void nonBlockingDelay::Write( tick_t durationValue )
{
   this->duration = durationValue;
}

//=====[Implementations of private methods]====================================*/