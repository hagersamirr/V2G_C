/*
 * State_Machine.c
 *
 *  Created on: Mar 18, 2023
 *      Author: Ahmed Yasser
 */
#include "State_Machine.h"


struct iso1EXIDocument exi;
struct iso1EXIDocument REQ_MES;
struct appHandEXIDocument exiIn;

extern stateMachine_t SM;

typedef struct {

	const char * name;
	void (*APP)(r,exiIn);
	void (*func)(req,exi);

} V2g_stateFunctionRow;


//
//typedef struct {
//
//	const char * name;
//
//	void (*fun)(r,exi);
//} V2g_state_APP_FunctionRow;



typedef struct {
	state_t currState;
	event_t event;
	state_t nextState;
} stateTransMatrixRow_t;


void StateMachine_Init(stateMachine_t * stateMachine) {
	printf("Initialising state machine.\r\n");
	stateMachine->currState = ST_IDLE;
}

static stateTransMatrixRow_t stateTransMatrix[] = {
		// CURR STATE            // EVENT                     // NEXT STATE
		{ ST_IDLE,               EV_APP_HAND,                         ST_APP_HAND_SHAKE  },
		{ST_APP_HAND_SHAKE, 		EV_SessionSetup,                 ST_SESSION_SETUP},
		{ST_SESSION_SETUP, EV_ServiceDiscovery,                      ST_SERVICE_DISCOVERY},
		{ST_SERVICE_DISCOVERY,    EV_ChargeParameterDiscovery,                  ST_CHARGE_PARAMETER  },
	//	{ST_SERVICE_DETAIL,  ,         },
		{ST_CHARGE_PARAMETER, EV_PowerDelivery,      ST_POWER_DELIVERY},
		{ST_POWER_DELIVERY, EV_SessionStop, ST_SESSION_STOP},
};

static V2g_stateFunctionRow stateFunctionA[] = {
		// NAME         // FUNC
		{"ST_IDLE",          &IDLE,   &IDLE},
		{"ST_APP_HAND_SHAKE", &appHandshakeHandler},
		{"ST_SESSION_SETUP",    0,     &sessionSetup1},
		{"ST_SERVICE_DISCOVERY",0,     &serviceDiscovery1 },
	//	{"ST_SERVICE_DETAIL",   0,      &serviceDetail1},
		{"ST_CHARGE_PARAMETER", 0,      &chargeParameterDiscovery1},
		{"ST_POWER_DELIVERY",   0,      &powerDelivery1},
		{"ST_SESSION_STOP",     0,      &sessionStop1},

};


void Runnable_State ()
{

	event_t  x;

	if(r.supportedAppProtocolReq_isUsed)
	{
		x = EV_APP_HAND;
		r.supportedAppProtocolReq_isUsed=0;
	}
	if (req.V2G_Message.Body.SessionSetupReq_isUsed )
	{
		x = EV_SessionSetup;
		printf("Session Setup Called \n");

	}
	else if (req.V2G_Message.Body.ServiceDiscoveryReq_isUsed)
	{
		x = EV_ServiceDiscovery;
		printf("ServiceDiscovery Called \n");
	}
/*
	else if (req.V2G_Message.Body.ServiceDetailReq_isUsed)
	{
		x = EV_ServiceDetail;
		printf("ServiceDetail Called \n");
	}
*/
	else if (req.V2G_Message.Body.ChargeParameterDiscoveryReq_isUsed)
	{
		x = EV_ChargeParameterDiscovery;
		printf("ChargeParameterDiscovery Called \n");
	}

	else if (req.V2G_Message.Body.PowerDeliveryReq_isUsed)
	{
		x = EV_PowerDelivery;
		printf("PowerDelivery Called \n");
	}


	else if (req.V2G_Message.Body.SessionStopReq_isUsed)
	{
		x = EV_SessionStop;
		printf("SessionStop Called \n");
	}

	StateMachine_RunIteration(&SM,x);
}



void StateMachine_RunIteration(stateMachine_t *stateMachine, event_t event) {

	// Iterate through the state transition matrix, checking if there is both a match with the current state
	// and the event
	for(int i = 0; i < sizeof(stateTransMatrix)/sizeof(stateTransMatrix[0]); i++) {

		if(stateTransMatrix[i].currState == stateMachine->currState) {
			if((stateTransMatrix[i].event == event) || (stateTransMatrix[i].event == EV_ANY)) {

				// Transition to the next state
				stateMachine->currState =  stateTransMatrix[i].nextState;
				if(stateMachine->currState == ST_APP_HAND_SHAKE)
				{
					(stateFunctionA[stateMachine->currState].APP)(&r,&exiIn);
				}
				else{
					// Call the function associated with transition
					(stateFunctionA[stateMachine->currState].func)(&req,&exi);
				}
				break;

			}
		}
	}

	const char * StateMachine_GetStateName(state_t state) {
		return stateFunctionA[state].name;
	}
}
