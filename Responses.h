/*
 * Responses.h
 *
 *  Created on: Mar 20, 2023
 *      Author: Ahmed Yasser
 */

#ifndef RESPONSES_H_
#define RESPONSES_H_
#include "main_example.h"
//extern char sending_flag;
//extern char reciving_flag;

typedef struct myGrid
{
	int available_Power;
	int available_Max_Current;
	int available_Min_Current;
	int available_Max_Voltage;
	int Freq;
	int nominal_voltage;
}myGrid;

/************ Responses Prototypes *******************/
void IDLE ();
void appHandshakeHandler(struct appHandEXIDocument* REQ_HANDLER, struct appHandEXIDocument* RES_HANDLER);
void sessionSetup1(struct iso1EXIDocument* REQ_MES, struct iso1EXIDocument* RES_MES);
void serviceDiscovery1(struct iso1EXIDocument* REQ_MES, struct iso1EXIDocument* RES_MES);
void serviceDetail1(struct iso1EXIDocument* exiIn, struct iso1EXIDocument* exiOut);
void chargeParameterDiscovery1(struct iso1EXIDocument* REQ_MES, struct iso1EXIDocument* RES_MES);
void powerDelivery1(struct iso1EXIDocument* exiIn, struct iso1EXIDocument* exiOut);
void  sessionStop1(struct iso1EXIDocument* REQ_MES, struct iso1EXIDocument* RES_MES);
void relayClosed(void);
void Waiting();
/********************** Prototypes *******************/


#endif /* RESPONSES_H_ */
