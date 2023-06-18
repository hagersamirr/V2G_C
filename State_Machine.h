/*
 * State_Machine.h
 *
 *  Created on: Mar 18, 2023
 *      Author: Ahmed Yasser
 */

#ifndef STATE_MACHINE_H_
#define STATE_MACHINE_H_

#include "main_example.h"

typedef enum{
ST_IDLE,
ST_APP_HAND_SHAKE,
ST_SESSION_SETUP,
ST_SERVICE_DISCOVERY,
//ST_SERVICE_DETAIL,
ST_CHARGE_PARAMETER,
ST_POWER_DELIVERY,
ST_SESSION_STOP,
ST_AUTHORIZED,
ST_TERMINATED,
ST_PAUSED,
ST_RENOGITATE,
ST_COMPLETED,
}state_t;


typedef enum{
EV_ANY,
EV_APP_HAND,
EV_SessionSetup,
EV_ServiceDiscovery,
//EV_ServiceDetail,
EV_ChargeParameterDiscovery,
EV_PowerDelivery,
EV_SessionStop,
EV_RelayClosed,
EV_Send,
EV_Recv,
}event_t;

typedef struct {
    state_t currState;
} stateMachine_t;



//Functions Prototypes
void StateMachine_Init(stateMachine_t * stateMachine);
void StateMachine_RunIteration(stateMachine_t *stateMachine, event_t event);
const char * StateMachine_GetStateName(state_t state);
void Runnable_State ();

#endif /* STATE_MACHINE_H_ */
