/*
 * main_example.h
 *
 *  Created on: Mar 20, 2023
 *      Author: Ahmed Yasser
 */
#define SESSION_LENGTH 8

#define ERROR_UNEXPECTED_REQUEST_MESSAGE -88
#define ERROR_UNEXPECTED_SESSION_SETUP_RESP_MESSAGE -602
#define ERROR_UNEXPECTED_SERVICE_DISCOVERY_RESP_MESSAGE -602
#define ERROR_UNEXPECTED_SERVICE_DETAILS_RESP_MESSAGE -603
#define ERROR_UNEXPECTED_PAYMENT_SERVICE_SELECTION_RESP_MESSAGE -604
#define ERROR_UNEXPECTED_PAYMENT_DETAILS_RESP_MESSAGE -605
#define ERROR_UNEXPECTED_AUTHORIZATION_RESP_MESSAGE -606
#define ERROR_UNEXPECTED_CHARGE_PARAMETER_DISCOVERY_RESP_MESSAGE -607
#define ERROR_UNEXPECTED_POWER_DELIVERY_RESP_MESSAGE -608
#define ERROR_UNEXPECTED_CHARGING_STATUS_RESP_MESSAGE -609
#define ERROR_UNEXPECTED_METERING_RECEIPT_RESP_MESSAGE -610
#define ERROR_UNEXPECTED_SESSION_STOP_RESP_MESSAGE -611
#define ERROR_UNEXPECTED_CABLE_CHECK_RESP_MESSAGE -612
#define ERROR_UNEXPECTED_PRE_CHARGE_RESP_MESSAGE -612
#define ERROR_UNEXPECTED_CURRENT_DEMAND_RESP_MESSAGE -613
#define ERROR_UNEXPECTED_WELDING_DETECTION_RESP_MESSAGE -614

#define ERROR_UNSUPPORTED_APP_PROTOCOL -601
#define ERROR_UNEXPECTED_SESSION_ID -108

//Counter For calling the sequence of the program



//unsigned int socket_value;

#ifndef MAIN_EXAMPLE_H_
#define MAIN_EXAMPLE_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#include <string.h>

#include "EXITypes.h"

#include "appHandEXIDatatypes.h"
#include "appHandEXIDatatypesEncoder.h"
#include "appHandEXIDatatypesDecoder.h"
#include "Station_Status.h"
#include "main.h"
//#include "Presentation.h"
#include "iso2EXIDatatypes.h"
//#if DEPLOY_ISO2_CODEC == SUPPORT_YES
#include "iso2EXIDatatypesEncoder.h"
#include "iso2EXIDatatypesDecoder.h"
//#endif /* DEPLOY_ISO1_CODEC == SUPPORT_YES */
#include "iso1EXIDatatypesEncoder.h"
#include "iso1EXIDatatypesDecoder.h"
#include "v2gtp.h"
#include "TCP_Server.h"
//#include "State_Machine.h"
#include "Responses.h"
#include "iso2EXIDatatypes.h"
#include "iso1EXIDatatypes.h"


extern struct iso1EXIDocument req;
extern struct iso1EXIDocument res;
extern struct appHandEXIDocument r;
extern struct appHandEXIDocument APP_RESPONSE;

int writeStringToEXIString(char* string, exi_string_character_t* exiString);
void printBinaryArray(uint8_t* byte, uint16_t len);
int serializeAppHandShakeEXIstream(struct appHandEXIDocument* appHandResp, bitstream_t* oStream);
int deserializeAppHandShakeEXIstream(bitstream_t* iStream, struct appHandEXIDocument* exi);
/*****************************************************************************************/



#endif /* MAIN_EXAMPLE_H_ */
