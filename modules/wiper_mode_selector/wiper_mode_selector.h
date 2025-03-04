//=====[#include guards - begin]===============================================

#ifndef _WIPER_MODE_SELECTOR_H_
#define _WIPER_MODE_SELECTOR_H_

//=====[Declaration of public defines]=========================================

//=====[Declaration of public data types]======================================
typedef enum {
    OFF_MODE,
    LOW_MODE,
    HIGH_MODE,
    INT_MODE
} wiperMode_t;

//=====[Declarations (prototypes) of public functions]=========================
wiperMode_t wiperModeSelectorUpdate(); // returns wiper mode selected by potentiometer

//=====[#include guards - end]=================================================

#endif // _WIPER_MODE_SELECTOR_H_