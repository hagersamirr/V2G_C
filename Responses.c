

#include "Responses.h"
#include "TCP_Server.h"
#include "main_example.h"
#include "Presentation.h"
uint8_t State = 0;
unsigned char sense;


/** Global Variables for sending the stream ****/
bitstream_t Stream_Response;
#define BUFFER_RESPONSE 256
uint8_t array[BUFFER_RESPONSE];

bitstream_t Stream_Response_APP_HAND;
#define BUFFER_RESPONSE_APP_HAND 256
uint8_t array_APP_HAND[BUFFER_RESPONSE_APP_HAND];


void SetUp_Response_APP__HAND()
{
	uint8_t errn;
	size_t pos_APP_HAND;
	Stream_Response_APP_HAND.size = BUFFER_RESPONSE_APP_HAND;
	Stream_Response_APP_HAND.data = array_APP_HAND;
	Stream_Response_APP_HAND.pos = &pos_APP_HAND;
	errn = serializeAppHandShakeEXIstream(&APP_RESPONSE, &Stream_Response_APP_HAND);
	if(errn == 0)
	{
		printf("Data Serialized \n");
	}

	socket_send_packet((Stream_Response_APP_HAND.data),*(Stream_Response_APP_HAND.pos));
}



//void SetUp_Response()
//{
//	uint8_t errn;
//	uint8_t check;
//	size_t pos1;
//	Stream_Response.size = BUFFER_RESPONSE;
//	Stream_Response.data = array;
//	Stream_Response.pos = &pos1;
//	errn = serialize2EXI2Stream(&res, &Stream_Response);
//	if(errn == 0)
//	{
//		printf("Data Serialized \n");
//	}
//	check = socket_send_packet((Stream_Response.data),*(Stream_Response.pos));
//
//	if(check == 0)
//	{
//		printf("\n ===============Data Sent .....");
//	}
//	else
//		printf("\n ERROR SEND");
//}


void IDLE ()
{
	printf("Waiting......");
}


void appHandshakeHandler(struct appHandEXIDocument* REQ_HANDLER, struct appHandEXIDocument* RES_HANDLER) {


	int i =0;

	struct appHandEXIDocument PROTOCOL_VERSION ;

	PROTOCOL_VERSION.HANDLING.ResProtocol.array[0].VersionNumberMajor = 2;
	PROTOCOL_VERSION.HANDLING.ResProtocol.array[0].VersionNumberMinor = 0;


	//	char* ns0 = "urn:iso:15118:2:2013:MsgDef";
	//	char* ns1 = "urn:din:70121:2012:MsgDef";

	//	writeStringToEXIString(ns0,PROTOCOL_VERSION.HANDLING.ResProtocol.array[0].ProtocolNamespace.characters);
	//	writeStringToEXIString(ns1,PROTOCOL_VERSION.HANDLING.ResProtocol.array[1].ProtocolNamespace.characters);


	for(i=0; i<REQ_HANDLER->supportedAppProtocolReq.AppProtocol.arrayLen; i++)
	{
		if(  (REQ_HANDLER->supportedAppProtocolReq.AppProtocol.array[i].VersionNumberMajor == PROTOCOL_VERSION.HANDLING.ResProtocol.array[i].VersionNumberMajor) && (REQ_HANDLER->supportedAppProtocolReq.AppProtocol.array[i].VersionNumberMinor == PROTOCOL_VERSION.HANDLING.ResProtocol.array[i].VersionNumberMinor) )
		{
			init_appHandEXIDocument(RES_HANDLER);
			RES_HANDLER->supportedAppProtocolRes_isUsed = 1u;

			RES_HANDLER->supportedAppProtocolRes.type.VersionNumberMajor = REQ_HANDLER->supportedAppProtocolReq.AppProtocol.array->VersionNumberMajor;
			RES_HANDLER->supportedAppProtocolRes.type.VersionNumberMinor = REQ_HANDLER->supportedAppProtocolReq.AppProtocol.array->VersionNumberMinor;
			RES_HANDLER->supportedAppProtocolRes.SchemaID_isUsed = 1u;

			RES_HANDLER->supportedAppProtocolRes.SchemaID = REQ_HANDLER->supportedAppProtocolReq.AppProtocol.array->SchemaID;

			RES_HANDLER->supportedAppProtocolRes.type.Priority = REQ_HANDLER->supportedAppProtocolReq.AppProtocol.array->Priority;
			RES_HANDLER->supportedAppProtocolRes.ResponseCode = appHandresponseCodeType_OK_SuccessfulNegotiation;

			break;
		}
		else
		{

			RES_HANDLER->supportedAppProtocolRes.ResponseCode = appHandresponseCodeType_Failed_NoNegotiation;
			RES_HANDLER->supportedAppProtocolRes_isUsed = 1u;
		}
	}

	uint8_t errn;
	size_t pos_APP_HAND;
	Stream_Response_APP_HAND.size = BUFFER_RESPONSE_APP_HAND;
	Stream_Response_APP_HAND.data = array_APP_HAND;
	Stream_Response_APP_HAND.pos = &pos_APP_HAND;
	errn = serializeAppHandShakeEXIstream(RES_HANDLER, &Stream_Response_APP_HAND);

	if(errn == 0)
	{
		printf("Data Serialized \n");
	}


	socket_send_packet((Stream_Response_APP_HAND.data), *(Stream_Response_APP_HAND.pos));
	//APP_RESPONSE = *RES_HANDLER;
	//SetUp_Response_APP__HAND();

}




void sessionSetup1(struct iso1EXIDocument* REQ_MES, struct iso1EXIDocument* RES_MES) {
	unsigned char y;
	init_iso1EXIDocument(RES_MES);

	// --->	y = Check_SESSION_ID(REQ_MES->V2G_Message.Header.SessionID.bytes, REQ_MES->V2G_Message.Header.SessionID.bytesLen);
	//for(int i=0; i<REQ_MES->V2G_Message.Header.SessionID.bytesLen; i++)
	//{
	//	uint8_t arrayOFzeroes [REQ_MES->V2G_Message.Header.SessionID.bytesLen] =0;
	//	for(int j=0; j<REQ_MES->V2G_Message.Header.SessionID.bytesLen; j++)

	// H: Case of session id in request = 0 SO generate new session id and start new session
	// with the generated id
#if 0
	if(REQ_MES->V2G_Message.Header.SessionID.bytes[REQ_MES->V2G_Message.Header.SessionID.bytesLen] == 0 )
	{
		//GENERATING_SESSION_ID(SE_SESSION_ID,SESSION_LENGTH);

		//RES_MES->V2G_Message_isUsed = 1;

		//RES_MES->SessionSetupRes.

		for(int i=0; i<SESSION_LENGTH; i++)
		{
			RES_MES->V2G_Message.Header.SessionID.bytes[i] = 1;
		}

		RES_MES->V2G_Message.Header.SessionID.bytesLen = 8;

		init_iso1BodyType(&RES_MES->V2G_Message.Body);

		RES_MES->V2G_Message.Body.BodyElement_isUsed = 1u;

		RES_MES->SessionSetupRes_isUsed = 1u;


		//RES_MES->V2G_Message.Body.SessionSetupRes_isUsed = 1u;
		RES_MES->V2G_Message.Body.SessionSetupRes.ResponseCode = iso1responseCodeType_OK_NewSessionEstablished;
		// EVSEID: Any  ID that uniquely  identifies the EVSE  and
		// the power outlet the  vehicle  is  connected to
		// LAW el station m3ndhash el m3lomat dy bt-set el EVSEID B ZEROS "ZZ00000"

		// example for EVSEID "FR*A23*E45B*78C" from ISO -2
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[0] = 'F';
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[1] = 'R';
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[2] = '*';
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[3] = 'A';
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[4] =  2 ;
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[5] =  3 ;
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[6] = '*';
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[7] = 'E';
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[8] =  4 ;
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[9] =  5 ;
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[10]= 'B';
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[11]= '*';
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[12]=  7 ;
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[13]=  8 ;
		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[14]= 'C';

		RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.charactersLen = 15;

		RES_MES->V2G_Message.Body.SessionSetupRes.EVSETimeStamp = 10;

		RES_MES->V2G_Message.Body.SessionSetupRes.EVSETimeStamp_isUsed = 1u;
	}
	// H: Case of session id = 0 or (!=0) =  preceding id -> old session joined or = any number -> establish new session
	else
	{    unsigned char OLD_SESSION_ID[8];
	// hena na2s elhaga ele btemla el old session id
	for(int i=0; i<SESSION_LENGTH; i++)
	{
		if (RES_MES->V2G_Message.Header.SessionID.bytes[i] == OLD_SESSION_ID[i])
		{
			init_iso1BodyType(&RES_MES->V2G_Message.Body);
			RES_MES->V2G_Message_isUsed = 1;
			RES_MES->SessionSetupRes_isUsed = 1u;
			init_iso1MessageHeaderType(&RES_MES->V2G_Message.Header);
			for(int i=0; i<SESSION_LENGTH; i++)
			{
				RES_MES->V2G_Message.Header.SessionID.bytes[i] = OLD_SESSION_ID[i];
			}
			RES_MES->V2G_Message.Body.SessionSetupRes_isUsed = 1u;
			RES_MES->V2G_Message.Body.SessionSetupRes.ResponseCode = iso1responseCodeType_OK_OldSessionJoined;
			// haga btshawer ala el data bta3t elsession el adema

		}
		else
		{
			GENERATING_SESSION_ID(SE_SESSION_ID,SESSION_LENGTH);
			init_iso1BodyType(&RES_MES->V2G_Message.Body);
			RES_MES->V2G_Message_isUsed = 1;
			RES_MES->V2G_Message.Body.SessionSetupRes_isUsed = 1u;
			init_iso1MessageHeaderType(&RES_MES->V2G_Message.Header);
			for(int i=0; i<SESSION_LENGTH; i++)
			{
				RES_MES->V2G_Message.Header.SessionID.bytes[i] = SE_SESSION_ID[i];
			}
			RES_MES->V2G_Message.Body.SessionSetupRes_isUsed = 1u;
			RES_MES->V2G_Message.Body.SessionSetupRes.ResponseCode = iso1responseCodeType_OK_NewSessionEstablished;
		}
	}

	}
	//}
#endif
#if 1
	if (y == 0)

	{
		struct iso1BodyType bodyType;
		struct iso1MessageHeaderType header;



		//init_iso1BodyType(&RES_MES->V2G_Message.Body);
		init_iso1BodyType(&bodyType);
		(RES_MES)->V2G_Message_isUsed = 1;
		//bodyType.BodyElement_isUsed=1;
		//bodyType.SessionSetupReq_isUsed = 1u;
		bodyType.SessionSetupRes_isUsed=1;
	 for (int i = 0; i < sizeof(SE_SESSION_ID); i++) {
		        SE_SESSION_ID[i] = rand() % 256;
		    }

	 //GENERATING_SESSION_ID(SE_SESSION_ID,SESSION_LENGTH);
//		for (int i; i<8; i++)
//		{
//			header.SessionID.bytes[i] = 0x[i][i];
//		}

		 for (int i = 0; i < 4; i++)
		 {
		        sprintf(&header.SessionID.bytes[i*2], "%02x", (unsigned char)SE_SESSION_ID[i]);
         }
		 header.SessionID.bytesLen = 8;

		 for(int i=0; i<8; i++)
		 {
			 SE_SESSION_ID[i] = header.SessionID.bytes[i];
		 }

		//GENERATING_SESSION_ID(SE_SESSION_ID,SESSION_LENGTH);
	//	header.SessionID.bytes[8]= {0x12,0x22,0x15,0x12,0x22,0x56,0x43,0x22};

		//	(RES_MES)->V2G_Message.Body.SessionSetupRes_isUsed = 1u;
		//RES_MES->SessionSetupRes.=1;
		//		init_iso1MessageHeaderType(&RES_MES->V2G_Message.Header);
//char hexstr[8][2];
//
//		for(int i=0; i<SESSION_LENGTH; i++)
//		{
//			sprintf(hexstr[i], "%02X",SE_SESSION_ID );
//		}
//
//
//		for(char i=0; i<SESSION_LENGTH; i++)
//		{
//			header.SessionID.bytes[i]  = SE_SESSION_ID[i];
//		}
//

		//RES_MES->V2G_Message.Body.BodyElement.name.namespaceURL = "urn:iso:15118:2:2013:MsgDef";
		//	RES_MES->V2G_Message.Body.BodyElement.name.localPart    = "SessionSetupRes";

		//(RES_MES->V2G_Message).Body.BodyElement_isUsed = 1u;
		//	RES_MES->V2G_Message.Body.SessionSetupRes_isUsed = 1u;

		bodyType.SessionSetupRes.ResponseCode = iso1responseCodeType_OK_NewSessionEstablished;

		//	bodyType.SessionSetupRes.EVSEID.characters= 0;
		for(int i=0; i<37; i++)
		{
			bodyType.SessionSetupRes.EVSEID.characters [i] = i;

		}

		//bodyType.SessionSetupRes.EVSEID.charactersLen = 2;
		//		bodyType.SessionSetupRes.EVSETimeStamp_isUsed = 1u;
		//		bodyType.SessionSetupRes.EVSETimeStamp = 10;
		//	}
		//	else
		//	{
		//		if(checkBinaryArray(REQ_MES->V2G_Message.Header.SessionID.bytes, REQ_MES->V2G_Message.Header.SessionID.bytesLen) == 0)
		//		{
		//
		//			init_iso1BodyType(&RES_MES->V2G_Message.Body);
		//
		//			RES_MES->V2G_Message_isUsed = 1u;
		//
		//
		//			GENERATING_SESSION_ID(SE_SESSION_ID,SESSION_LENGTH);
		//
		//
		//			init_iso1MessageHeaderType(&RES_MES->V2G_Message.Header);
		//
		//			for(int i=0; i<SESSION_LENGTH; i++)
		//			{
		//				RES_MES->V2G_Message.Header.SessionID.bytes[i] = SE_SESSION_ID[i];
		//			}
		//
		//			//RES_MES->V2G_Message.Body.BodyElement.localPart = "HISHAM";
		//
		//
		//
		//			RES_MES->V2G_Message.Body.SessionSetupRes_isUsed = 1u;
		//			RES_MES->V2G_Message.Body.SessionSetupRes.ResponseCode = iso1responseCodeType_OK_NewSessionEstablished;
		//			RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[0] = 0;
		//			RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.characters[1] = 20;
		//			RES_MES->V2G_Message.Body.SessionSetupRes.EVSEID.charactersLen = 2;
		//			RES_MES->V2G_Message.Body.SessionSetupRes.EVSETimeStamp_isUsed = 1u;
		//			RES_MES->V2G_Message.Body.SessionSetupRes.EVSETimeStamp = 10;
		//		}
		//
		//
		//		else
		//		{
		//			init_iso1BodyType(&RES_MES->V2G_Message.Body);
		//			RES_MES->V2G_Message.Body.SessionSetupRes_isUsed = 1u;
		//			RES_MES->V2G_Message.Body.SessionSetupRes.ResponseCode = iso1responseCodeType_FAILED;
		//		}
		//	}
#endif
		//	res = *RES_MES;
		//	printf("Session Setup 5lst....");
		//	SetUp_Response();
//		uint8_t errn;
//		uint8_t check;
//		size_t pos1;
//		Stream_Response.size = BUFFER_RESPONSE;
//		Stream_Response.data = array;
//		Stream_Response.pos = &pos1;
//		RES_MES->V2G_Message.Header = header;
//		RES_MES->V2G_Message.Body = bodyType;
//
//		errn = serialize1EXI2Stream(RES_MES, &Stream_Response);
//
//
//		if(errn == 0)
//		{
//			printf("Data Serialized \n");
//		}
//		else
//		{
//			printf("Data Not serialized");
//		}
//		socket_send_packet((Stream_Response.data),*(Stream_Response.pos));

		uint8_t errn;
		uint8_t check;
		size_t pos1;
		Stream_Response.size = BUFFER_RESPONSE;
		Stream_Response.data = array;
		Stream_Response.pos = &pos1;
		RES_MES -> V2G_Message.Header = header;
		RES_MES -> V2G_Message.Body = bodyType;

		errn = serialize1EXI2Stream(RES_MES , &Stream_Response);
		if(errn == 0)
		{
			printf("Data is SERIALIZED");

		}
		else
		{
			printf("Data NOTT serialized");
		}

		socket_send_packet((Stream_Response.data) , *(Stream_Response.pos));

	}
}




//void serviceDiscovery2(struct iso2EXIDocument* REQ_MES, struct iso2EXIDocument* RES_MES) {
//	unsigned char x;
//	x = Check_SESSION_ID(REQ_MES->V2G_Message.Header.SessionID.bytes, REQ_MES->V2G_Message.Header.SessionID.bytesLen);
//
//	if(x==0)
//	{
//		init_iso2BodyType(&RES_MES->V2G_Message.Body);
//		/*
//			printf("Data Received from EV Side Successfully \n"); // service discovery request processed successfully
//			printf("EVSE side: serviceDiscovery called \n" );
//			printf("\t Header SessionID = ");
//
//			printBinaryArray(RES_MES->V2G_Message.Header.SessionID.bytes, RES_MES->V2G_Message.Header.SessionID.bytesLen);
//
//			printf("\t\tSupportedServiceID = iso2serviceCategoryType_EVCharging \n");*/
//
//		init_iso2MessageHeaderType(&RES_MES->V2G_Message.Header);
//
//		for(int i=0; i<SESSION_LENGTH; i++)
//		{
//			RES_MES->V2G_Message.Header.SessionID.bytes[i] = SE_SESSION_ID[i];
//		}
//
//		/* Prepare data for EV */
//		RES_MES->V2G_Message_isUsed = 1u;
//
//		init_iso2ServiceDiscoveryResType(&RES_MES->V2G_Message.Body.ServiceDiscoveryRes);
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes_isUsed = 1u;
//
//		//first response code
//		//exiOut->V2G_Message.Body.ServiceDiscoveryRes.VASList_isUsed = 0u;  /* we do not provide VAS */
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.ResponseCode = iso2responseCodeType_OK;
//
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.PaymentOptionList.PaymentOption.array[0] = iso2paymentOptionType_ExternalPayment; /* EVSE handles the payment */
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.PaymentOptionList.PaymentOption.array[1] = iso2paymentOptionType_Contract;
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.PaymentOptionList.PaymentOption.arrayLen = 2;
//
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.EnergyTransferServiceList.Service.arrayLen = 4;
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.EnergyTransferServiceList.Service.array[0].ServiceID = 1; /* ID of the charge service */
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.EnergyTransferServiceList.Service.array[0].FreeService = False;
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.EnergyTransferServiceList.Service.array[0].Service_Name = AC_EV_CHARGING;
//
//
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.EnergyTransferServiceList.Service.array[1].ServiceID = 2; /* ID of the charge service */
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.EnergyTransferServiceList.Service.array[1].FreeService = False;
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.EnergyTransferServiceList.Service.array[1].Service_Name = AC_EV_CHARGING;
//
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.VASList_isUsed = 0u; /* no value added service requested */
//
//
//		printf(" Response Data Sent to EV \n");
//		//	return 0;
//	}
//	else if(x==1)
//	{
//		// second response code
//		printf("Response code: FAILED_UnknownSession \n");// session id doesn't match
//
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.ResponseCode = iso2responseCodeType_FAILED_UnknownSession;
//	}
//	else
//	{ //third response code
//		printf("Response code: FAILED \n");// any internal errors
//
//		RES_MES->V2G_Message.Body.ServiceDiscoveryRes.ResponseCode = iso2responseCodeType_FAILED;
//	}
//
//	//	res = *RES_MES;
//	//	SetUp_Response();
//}
void serviceDiscovery1(struct iso1EXIDocument* REQ_MES, struct iso1EXIDocument* RES_MES) {
	unsigned char x;
	init_iso1EXIDocument(RES_MES);
	struct iso1BodyType bodyType;
	struct iso1MessageHeaderType header;
	init_iso1BodyType(&bodyType);


	//----->>>> w hna ya hager l mfrod n init l header
	init_iso1MessageHeaderType(&header);

	(RES_MES)->V2G_Message_isUsed = 1;
	//------>>> w hna nty konty nasya l isUsed bt3 l serviceDiscover
	bodyType.ServiceDiscoveryRes_isUsed = 1u;


	x = Check_SESSION_ID(REQ_MES->V2G_Message.Header.SessionID.bytes, REQ_MES->V2G_Message.Header.SessionID.bytesLen);
	//x = Check_SESSION_ID(header.SessionID.bytes, header.SessionID.bytesLen);
#if 1
	if(x==0)
	{

		for(int i=0; i<SESSION_LENGTH; i++)
		{
			header.SessionID.bytes[i] = SE_SESSION_ID[i];

		}
		//----->>>>>>Bosy ya hager hna kona lazm n7ot l bytelen = 8
		header.SessionID.bytesLen = 8;


		//first response code
		//exiOut->V2G_Message.Body.ServiceDiscoveryRes.VASList_isUsed = 0u;  /* we do not provide VAS */
		//	RES_MES->V2G_Message.Body.ServiceDiscoveryRes.ResponseCode = iso1responseCodeType_OK;
		bodyType.ServiceDiscoveryRes.ResponseCode = iso1responseCodeType_OK;

		bodyType.ServiceDiscoveryRes.PaymentOptionList.PaymentOption.array[0] = iso1paymentOptionType_ExternalPayment; /* EVSE handles the payment */
		bodyType.ServiceDiscoveryRes.PaymentOptionList.PaymentOption.array[1] = iso1paymentOptionType_Contract;
		bodyType.ServiceDiscoveryRes.PaymentOptionList.PaymentOption.arrayLen = 2;


		bodyType.ServiceDiscoveryRes.ChargeService.ServiceName.charactersLen = 4;
		bodyType.ServiceDiscoveryRes.ChargeService.ServiceID = 1; /* ID of the charge service */
		bodyType.ServiceDiscoveryRes.ChargeService.FreeService = False;
		bodyType.ServiceDiscoveryRes.ChargeService.SupportedEnergyTransferMode.EnergyTransferMode.array[0] = iso1EnergyTransferModeType_AC_single_phase_core;


		bodyType.ServiceDiscoveryRes.ChargeService.ServiceID = 2; /* ID of the charge service */
		bodyType.ServiceDiscoveryRes.ChargeService.FreeService = False;
		bodyType.ServiceDiscoveryRes.ChargeService.SupportedEnergyTransferMode.EnergyTransferMode.array[1] = iso1EnergyTransferModeType_AC_three_phase_core;



		//----->>>> hna brdo lazm yt7t l array length b kam
		bodyType.ServiceDiscoveryRes.ChargeService.SupportedEnergyTransferMode.EnergyTransferMode.arrayLen=2;

		bodyType.ServiceDiscoveryRes.ServiceList_isUsed = 1u; /* no value added service requested */
        bodyType.ServiceDiscoveryRes.ServiceList.Service.array[0].FreeService=False;
        bodyType.ServiceDiscoveryRes.ServiceList.Service.array[0].ServiceID=24;
        bodyType.ServiceDiscoveryRes.ServiceList.Service.arrayLen=1;






#endif
		/*	else if(x==1)
	{
		// second response code
		printf("Response code: FAILED_UnknownSession \n");// session id doesn't match

		bodyType.ServiceDiscoveryRes.ResponseCode = iso1responseCodeType_FAILED_UnknownSession;
	}
	else
	{ //third response code
		printf("Response code: FAILED \n");// any internal errors

		bodyType.ServiceDiscoveryRes.ResponseCode = iso1responseCodeType_FAILED;
	}*/


		//------->> w hna 34an ndmn an hwa byb3t stream gded 3rft Stream_Service mn no3 bitstream
		bitstream_t Stream_Service;
		uint8_t errn;

		uint8_t array_ser [BUFFER_RESPONSE];
		size_t pos_serv;
		Stream_Service.size = BUFFER_RESPONSE;
		Stream_Service.data = array_ser;
		Stream_Service.pos = &pos_serv;
		RES_MES->V2G_Message.Header = header;
		RES_MES->V2G_Message.Body = bodyType;

		//----->>>>
		errn = serialize1EXI2Stream(RES_MES, &Stream_Service);


		if(errn == 0)
		{
			printf("Data Serialized \n");
		}
		else
		{
			printf("Data Not serialized");
		}
		socket_send_packet((Stream_Service.data),*(Stream_Service.pos));



		//	res = *RES_MES;
		//	SetUp_Response();
	}

}
void serviceDetail1(struct iso1EXIDocument* REQ_MES, struct iso1EXIDocument* RES_MES) {

	init_iso1EXIDocument(RES_MES);
	struct iso1BodyType bodyType;
	struct iso1MessageHeaderType header;
	init_iso1BodyType(&bodyType);
	init_iso1MessageHeaderType(&header);

	(RES_MES)->V2G_Message_isUsed = 1;
	bodyType.ServiceDetailRes_isUsed = 1u;
	unsigned char x;
	x = Check_SESSION_ID(REQ_MES->V2G_Message.Header.SessionID.bytes, REQ_MES->V2G_Message.Header.SessionID.bytesLen);

	if(x==0){


		//
		//		printf("Data Received from EV Side Successfully \n");
		//		printf("EVSE side: service Detail called\n"  );
		//		printf("\t Header SessionID = ");
	for(int i=0; i<SESSION_LENGTH; i++)
	{
		header.SessionID.bytes[i] = SE_SESSION_ID[i];

	}
				//----->>>>>>Bosy ya hager hna kona lazm n7ot l bytelen = 8
	header.SessionID.bytesLen = 8;
	//printBinaryArray(header.SessionID.bytes, header.SessionID.bytesLen);





		/* Prepare data for EV */

		//exiOut->V2G_Message_isUsed = 1u;
		//init_iso1BodyType(&exiOut->V2G_Message.Body);

		//init_iso1ServiceDetailResType(&RES_MES->V2G_Message.Body.ServiceDetailRes);

		// el mafrod z == ServiceID
		//int z;
//		switch (bodyType.ServiceDetailRes.ServiceID)
//		{
//		/service details for ServiceID 2 'Certificate' is requested/
//		case 2:
//			/* TO DO */
//			break;
//			//service details for ServiceID 3 'InternetAccess' is requested.
//		case 3:
//
//			//parameterSetID = 1
//			//Service  to  use  internet  access  using  FTP  protocol  via  port  20
//
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceID = 3;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList_isUsed = 1u;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.arrayLen = 2;
//
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].ParameterSetID = 1;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.arrayLen = 2;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.charactersLen = 8;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[0] = 'P';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[1] = 'r';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[2] = 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[3] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[4]= 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[5] = 'c';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[6] = 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[7] = 'l';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue_isUsed = 1u;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.charactersLen = 3;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[0] = 'f';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[1] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[2] = 'p';
//
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.charactersLen = 4;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[0] = 'P';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[1] = 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[2] = 'r';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[3] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].intValue = 20;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].intValue_isUsed = 1u;
//
//			//parameterSetID = 2
//			//Service  to  use  internet  access  using  FTP  protocol  via  port  21
//
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceID = 3;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList_isUsed = 1u;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.arrayLen = 2;
//
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].ParameterSetID = 2;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.arrayLen = 2;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.charactersLen = 8;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[0] = 'P';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[1] = 'r';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[2] = 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[3] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[4]= 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[5] = 'c';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[6] = 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[7] = 'l';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue_isUsed = 1u;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.charactersLen = 3;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[0] = 'f';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[1] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[2] = 'p';
//
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.charactersLen = 4;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[0] = 'P';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[1] = 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[2] = 'r';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[3] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].intValue = 21;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].intValue_isUsed = 1u;
//
//
//
//			//parameterSetID = 3
//			//Service  to  use  internet  access  using  HTTP  protocol  via  port  80
//
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceID = 3;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList_isUsed = 1u;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.arrayLen = 2;
//
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].ParameterSetID = 3;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.arrayLen = 2;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.charactersLen = 8;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[0] = 'P';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[1] = 'r';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[2] = 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[3] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[4]= 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[5] = 'c';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[6] = 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[7] = 'l';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue_isUsed = 1u;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.charactersLen = 4;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[0] = 'h';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[1] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[2] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[3] = 'p';
//
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.charactersLen = 4;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[0] = 'P';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[1] = 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[2] = 'r';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[3] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].intValue = 80;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].intValue_isUsed = 1u;
//
//
//
//			//parameterSetID = 4
//			//Service  to  use  internet  access  using  HTTPS  protocol  via  port  443
//
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceID = 3;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList_isUsed = 1u;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.arrayLen = 2;
//
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].ParameterSetID = 4;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.arrayLen = 2;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.charactersLen = 8;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[0] = 'P';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[1] = 'r';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[2] = 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[3] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[4]= 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[5] = 'c';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[6] = 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].Name.characters[7] = 'l';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue_isUsed = 1u;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.charactersLen = 5;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[0] = 'h';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[1] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[2] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[3] = 'p';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].stringValue.characters[4] = 's';
//
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.charactersLen = 4;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[0] = 'P';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[1] = 'o';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[2] = 'r';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[1].Name.characters[3] = 't';
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].intValue = 443;
//			exiOut->V2G_Message.Body.ServiceDetailRes.ServiceParameterList.ParameterSet.array[0].Parameter.array[0].intValue_isUsed = 1u;
//
//		}

		bodyType.ServiceDetailRes.ResponseCode = iso1responseCodeType_OK;

		//socket_value++;
		//socket_send_packet(socket_value);
		printf(" Response Data SERVICE DETAILS Sent to EV \n");
		//	return 0;
	}
	else if (x==1)
	{
		// second response code
		printf("Response code: FAILED_UnknownSession \n");// session id doesn't match

		bodyType.ServiceDetailRes.ResponseCode = iso1responseCodeType_FAILED_UnknownSession;
	}

	else if(bodyType.ServiceDetailRes.ServiceID > 8)   // na max services 3andy 8, bs deh lsa hatet3adel b3d ma service discovery t5ls
	{
		printf("Response code: FAILED_ServiceIdInvalid \n");

		bodyType.ServiceDetailRes.ResponseCode = iso1responseCodeType_FAILED_ServiceSelectionInvalid;
	}
	else
	{
		//third response code
		printf("Response code: FAILED \n");// any internal errors

		bodyType.ServiceDetailRes.ResponseCode =  iso1responseCodeType_FAILED;
	}
	//res = *exiOut;
	bitstream_t Stream_Service;
	uint8_t errn;

	uint8_t array_ser [BUFFER_RESPONSE];
	size_t pos_serv;
	Stream_Service.size = BUFFER_RESPONSE;
	Stream_Service.data = array_ser;
	Stream_Service.pos = &pos_serv;
	RES_MES->V2G_Message.Header = header;
	RES_MES->V2G_Message.Body = bodyType;

	//----->>>>
	errn = serialize1EXI2Stream(RES_MES, &Stream_Service);


	if(errn == 0)
	{
		printf("Data Serialized \n");
	}
	else
	{
		printf("Data Not serialized");
	}
	socket_send_packet((Stream_Service.data),*(Stream_Service.pos));

}


void chargeParameterDiscovery1(struct iso1EXIDocument* REQ_MES, struct iso1EXIDocument* RES_MES) {
	unsigned char x ;
	init_iso1EXIDocument(RES_MES);
	struct iso1BodyType bodyType;
	struct iso1MessageHeaderType header;
	init_iso1BodyType(&bodyType);
	init_iso1MessageHeaderType(&header);
	(RES_MES)->V2G_Message_isUsed = 1;
	bodyType.ChargeParameterDiscoveryRes_isUsed = 1u;
	myGrid AC_Grid = {8800,40,10,220,50,210};


	x = Check_SESSION_ID(REQ_MES->V2G_Message.Header.SessionID.bytes, REQ_MES->V2G_Message.Header.SessionID.bytesLen);

		if(x == 1)
		{



			for(int i=0; i<SESSION_LENGTH; i++)
			{
				RES_MES->V2G_Message.Header.SessionID.bytes[i] = SE_SESSION_ID[i];
			}
			header.SessionID.bytesLen = 8;


			bodyType.ChargeParameterDiscoveryRes.ResponseCode = iso1responseCodeType_FAILED_UnknownSession;
	//		bodyType.ServiceDiscoveryRes.ChargeService.SupportedEnergyTransferMode.EnergyTransferMode.arrayLen=2;
		//	bodyType.ChargeParameterDiscoveryRes.
		}

		else if(x == 0)
		{

			if(REQ_MES->V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter_isUsed)
			{

				//(RES_MES)->V2G_Message_isUsed = 1;
				//init_iso1MessageHeaderType(&header);

				for(int i=0 ; i<SESSION_LENGTH ; i++)
				{
					RES_MES->V2G_Message.Header.SessionID.bytes[i] = SE_SESSION_ID[i];
				}
			//	init_iso1BodyType(&bodyType);
				header.SessionID.bytesLen = 8;

			    bodyType.ChargeParameterDiscoveryRes.ResponseCode = iso1responseCodeType_OK;
				bodyType.ChargeParameterDiscoveryRes.EVSEProcessing = iso1EVSEProcessingType_Finished;
			    bodyType.ChargeParameterDiscoveryRes.SAScheduleList_isUsed=1u;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SAScheduleTupleID = 55; //iso ex
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval_isUsed=1u;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval.start = 0;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].PMaxSchedule.PMaxScheduleEntry.array[0].RelativeTimeInterval.duration = 30000;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].PMaxSchedule.PMaxScheduleEntry.array[0].PMax.Value = 9600;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].PMaxSchedule.PMaxScheduleEntry.arrayLen=1;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff_isUsed=1u;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.SalesTariffID = 67;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.Id.characters[0]='h';
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.Id.charactersLen=1;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.Id_isUsed=1u;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.NumEPriceLevels_isUsed=1u;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.SalesTariffDescription_isUsed=1u;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.SalesTariffDescription.charactersLen = 1;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.SalesTariffDescription.characters [0] = 's';
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.NumEPriceLevels = 3;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.SalesTariffEntry.array[0].RelativeTimeInterval.start = 0;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.SalesTariffEntry.array[0].RelativeTimeInterval_isUsed=1u;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.SalesTariffEntry.array[0].EPriceLevel = 1;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.SalesTariffEntry.array[0].EPriceLevel_isUsed=1u;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array[0].SalesTariff.SalesTariffEntry.arrayLen=1;

				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.arrayLen=1;
/*
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array->SalesTariff.SalesTariffEntry.array->RelativeTimeInterval.start = 2147;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array->SalesTariff.SalesTariffEntry.array->EPriceLevel = 2;

				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array->SalesTariff.SalesTariffEntry.array->RelativeTimeInterval.start = 9874;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array->SalesTariff.SalesTariffEntry.array->EPriceLevel = 3;

				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array->SalesTariff.SalesTariffEntry.array->RelativeTimeInterval.start = 14937;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array->SalesTariff.SalesTariffEntry.array->EPriceLevel = 2;

				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array->SalesTariff.SalesTariffEntry.array->RelativeTimeInterval.start = 24431;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array->SalesTariff.SalesTariffEntry.array->RelativeTimeInterval.duration = 30000;
				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array->SalesTariff.SalesTariffEntry.array->EPriceLevel = 1;


				bodyType.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.arrayLen=3;

*/
				bodyType.ChargeParameterDiscoveryRes.EVSEStatus_isUsed=1u;
				bodyType.ChargeParameterDiscoveryRes.EVSEStatus.NotificationMaxDelay = 0;
				bodyType.ChargeParameterDiscoveryRes.EVSEStatus.EVSENotification = iso1EVSENotificationType_None;
				bodyType.ChargeParameterDiscoveryRes.EVSEStatus.RCD = FALSE;
				bodyType.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter_isUsed=1u;
				//bodyType.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter_isUsed=1u;
				bodyType.ChargeParameterDiscoveryRes.SASchedules.noContent=5;
				//RES_MES->V2G_Message.Body.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter.EVSEMaximumChargeCurrent.Value =AC_Grid.available_Max_Current;
			//RES_MES->V2G_Message.Body.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter.EVSEMaximumChargeCurrent.unit = Ampere;

				//RES_MES->V2G_Message.Body.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter.EVSENominalFrequency.Value = AC_Grid.Freq;
				//RES_MES->V2G_Message.Body.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter.EVSENominalFrequency.unit = Hertz;
				bodyType.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter.EVSENominalVoltage.Value = AC_Grid.nominal_voltage;
				bodyType.ChargeParameterDiscoveryRes.AC_EVSEChargeParameter.EVSENominalVoltage.Unit = iso1unitSymbolType_V;

			}

			else if(REQ_MES->V2G_Message.Body.ChargeParameterDiscoveryReq.DC_EVChargeParameter_isUsed)
			{
				/* TO Do */
			}

		}

		else if (REQ_MES->V2G_Message.Body.ChargeParameterDiscoveryReq.RequestedEnergyTransferMode > 5)
		{
		//	(RES_MES)->V2G_Message_isUsed = 1;
		//	init_iso1MessageHeaderType(&header);

			for(int i=0; i<SESSION_LENGTH; i++)
				{
					RES_MES->V2G_Message.Header.SessionID.bytes[i] = SE_SESSION_ID[i];
				}
			header.SessionID.bytesLen = 8;
		//	init_iso1BodyType(&bodyType);
			bodyType.ChargeParameterDiscoveryRes_isUsed = 1u;
			bodyType.ChargeParameterDiscoveryRes.ResponseCode = iso1responseCodeType_FAILED_WrongEnergyTransferMode;

		}

		else if (REQ_MES->V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter.EVMaxCurrent.Value > 400
				// || REQ_MES->V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter.EVMaximumChargePower.Value > 200000
				 || REQ_MES->V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter.EVMaxVoltage.Value > 1000
				// || REQ_MES->V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter.EVMaximumEnergyRequest.Value > 200000
				 || REQ_MES->V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter.EVMinCurrent.Value < 0)
				// || REQ_MES->V2G_Message.Body.ChargeParameterDiscoveryReq.AC_EVChargeParameter.EVMinimumEnergyRequest.Value < 0)
		{

			//(RES_MES)->V2G_Message_isUsed = 1;
			//init_iso1MessageHeaderType(&header);

			for(int i=0; i<SESSION_LENGTH; i++)
				{
					RES_MES->V2G_Message.Header.SessionID.bytes[i] = SE_SESSION_ID[i];
				}
			header.SessionID.bytesLen = 8;
			//init_iso1BodyType(&bodyType);
			bodyType.ChargeParameterDiscoveryRes_isUsed = 1u;
			bodyType.ChargeParameterDiscoveryRes.ResponseCode = iso1responseCodeType_FAILED_WrongChargeParameter;

		}

		else
		{
			//(RES_MES)->V2G_Message_isUsed = 1;
			//init_iso1MessageHeaderType(&header);

			for(int i=0; i<SESSION_LENGTH; i++)
				{
					RES_MES->V2G_Message.Header.SessionID.bytes[i] = SE_SESSION_ID[i];
				}
			header.SessionID.bytesLen = 8;
			//init_iso1BodyType(&bodyType);
			bodyType.ChargeParameterDiscoveryRes_isUsed = 1u;
			bodyType.ChargeParameterDiscoveryRes.ResponseCode = iso1responseCodeType_FAILED;
		}



	//socket_value++;
	//socket_send_packet(socket_value);
		bitstream_t Stream_Service;
		uint8_t errn;
		uint8_t check;
		size_t pos1;
		Stream_Service.size = BUFFER_RESPONSE;
		Stream_Service.data = array;
		Stream_Service.pos = &pos1;
		RES_MES -> V2G_Message.Header = header;
		RES_MES -> V2G_Message.Body = bodyType;
		errn = serialize1EXI2Stream(RES_MES , &Stream_Service);
		if(errn == 0)
		{
			printf("Data is SERIALIZED");

		}
		else
		{
			printf("Data NOTT serialized");
		}

		socket_send_packet((Stream_Service.data) , *(Stream_Service.pos));
}

void relayClosed(void)
{
	printf("Closing relay..\n");
}


void powerDelivery1(struct iso1EXIDocument* REQ_MES, struct iso1EXIDocument* RES_MES) {
                                            //exiIn
	//iso1chargingSessionType ChargingSession ;
	//ChargingSession=iso1chargingSessionType_Terminate;
	init_iso1EXIDocument(RES_MES);
	struct iso1BodyType bodyType;
	struct iso1MessageHeaderType header;
	unsigned char x;
	init_iso1MessageHeaderType(&header);
	init_iso1BodyType(&bodyType);

	(RES_MES)->V2G_Message_isUsed = 1;
	bodyType.PowerDeliveryRes_isUsed = 1u;

	x = Check_SESSION_ID(REQ_MES->V2G_Message.Header.SessionID.bytes, REQ_MES->V2G_Message.Header.SessionID.bytesLen);

	if(x==1)
	{


		printf("Response code: FAILED_UnknownSession \n");// session id doesn't match
		bodyType.PowerDeliveryRes.ResponseCode = iso1responseCodeType_FAILED_UnknownSession;

	}


/*
	//EVSE is not able to deliver energy.
	else if((REQ_MES->V2G_Message.Body.ChargeParameterDiscoveryRes.EVSEChargeParameter.noContent) == 0) // m7taga tet3adal baynn
	{

		bodyType.PowerDeliveryRes.ResponseCode=iso1responseCodeType_FAILED_PowerDeliveryNotApplied;

	}*/

	// EVCC  sends a  ChargingProfile which  is  not  adhering  to  the  PMax  values  of  all  PMaxScheduleEntry  elements according to the chosen SAScheduleTuple element
	//in the last ChargeParameterDiscoveryRes message
	else if(REQ_MES->V2G_Message.Body.PowerDeliveryReq.ChargingProfile.ProfileEntry.array->ChargingProfileEntryMaxPower.Value > RES_MES->V2G_Message.Body.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array->PMaxSchedule.PMaxScheduleEntry.array->PMax.Value )
	{
		bodyType.PowerDeliveryRes.ResponseCode=iso1responseCodeType_FAILED_ChargingProfileInvalid;
	}

	//attribute 'ChargingProfile' in the PowerDeliveryReq message contains a SAtupleID which was not contained in the 'SASchedules' attribute provided in 'ChargeParameterDiscoveryRes'.
	else if(REQ_MES->V2G_Message.Body.PowerDeliveryReq.SAScheduleTupleID != RES_MES->V2G_Message.Body.ChargeParameterDiscoveryRes.SAScheduleList.SAScheduleTuple.array->SAScheduleTupleID)
	{ //ezay bykarn array b int??????????????
		bodyType.PowerDeliveryRes.ResponseCode=iso1responseCodeType_FAILED_TariffSelectionInvalid;
	}



	else if(x==0)
	{
		/* Prepare data for EV */

		for(int i=0; i<SESSION_LENGTH; i++)
		{
			header.SessionID.bytes[i] = SE_SESSION_ID[i];
		}

		header.SessionID.bytesLen = 8;

	//	init_iso1PowerDeliveryResType(&RES_MES->V2G_Message.Body.PowerDeliveryRes);

		//exiOut->V2G_Message.Body.PowerDeliveryRes.EVSEStatus.RCD = FALSE; // INFORMATIVE FLAG

		bodyType.PowerDeliveryRes.ResponseCode = iso1responseCodeType_OK;
		bodyType.PowerDeliveryRes.EVSEStatus_isUsed=1u;
		bodyType.PowerDeliveryRes.EVSEStatus.NotificationMaxDelay = 0;
		bodyType.PowerDeliveryRes.EVSEStatus.EVSENotification =iso1EVSENotificationType_StopCharging;
;
		bodyType.PowerDeliveryRes.EVSEStatus.RCD = FALSE;
		bodyType.PowerDeliveryRes.AC_EVSEStatus_isUsed=1u;
		bodyType.PowerDeliveryRes.AC_EVSEStatus.EVSENotification=iso1EVSENotificationType_StopCharging;
		bodyType.PowerDeliveryRes.AC_EVSEStatus.NotificationMaxDelay=0;
		bodyType.PowerDeliveryRes.AC_EVSEStatus.RCD=FALSE;

		//bodyType.PowerDeliveryRes.
		///	bodyType.PowerDeliveryRes.EVSEStatus.EVSENotification
		if (REQ_MES->V2G_Message.Body.PowerDeliveryReq.ChargeProgress == iso1chargeProgressType_Start)
		{
			printf("\t\t  ChargeProgress=%d\n", REQ_MES->V2G_Message.Body.PowerDeliveryReq.ChargeProgress);

			//if (exiIn->V2G_Message.Body.PowerDeliveryReq.SAScheduleTupleID > 0 && exiIn->V2G_Message.Body.PowerDeliveryReq.SAScheduleTupleID < 256 )

			//printf("\t\t  SAScheduleTupleID=%d\n", exiIn->V2G_Message.Body.PowerDeliveryReq.SAScheduleTupleID);
			//exiOut->V2G_Message.Body.PowerDeliveryRes.ResponseCode = iso2responseCodeType_OK;
			//exiOut->V2G_Message.Body.PowerDeliveryRes.EVSEStatus.EVSENotification = iso2EVSENotificationType_None;




		}
		else if  (REQ_MES->V2G_Message.Body.PowerDeliveryReq.ChargeProgress == iso1chargeProgressType_Stop)
		{
			printf("\t\t  ChargeProgress=%d\n", REQ_MES->V2G_Message.Body.PowerDeliveryReq.ChargeProgress);
		bodyType.PowerDeliveryRes.EVSEStatus.EVSENotification = iso1EVSENotificationType_StopCharging;



		}
		else if (REQ_MES->V2G_Message.Body.PowerDeliveryReq.ChargeProgress == iso1chargeProgressType_Renegotiate)
		{
			printf("\t\t  ChargeProgress=%d\n", REQ_MES->V2G_Message.Body.PowerDeliveryReq.ChargeProgress);
			bodyType.PowerDeliveryRes.EVSEStatus.EVSENotification = iso1EVSENotificationType_ReNegotiation;
			//exiOut->V2G_Message.Body.PowerDeliveryRes.EVSEProcessing = iso2EVSEProcessingType_Ongoing_WaitingForCustomerInteraction;

		}

		bodyType.PowerDeliveryRes.EVSEStatus_isUsed = 1;
		bodyType.PowerDeliveryRes.EVSEStatus.NotificationMaxDelay=12;
	}
	else
	{

		printf("\t\t  Internal errors\n");
		bodyType.PowerDeliveryRes.ResponseCode = iso1responseCodeType_FAILED;
	}


	bitstream_t Stream_Service;
	uint8_t errn;

	uint8_t array_ser [BUFFER_RESPONSE];
	size_t pos_serv;
	Stream_Service.size = BUFFER_RESPONSE;
	Stream_Service.data = array_ser;
	Stream_Service.pos = &pos_serv;
	RES_MES->V2G_Message.Header = header;
	RES_MES->V2G_Message.Body = bodyType;

	//----->>>>
	errn = serialize1EXI2Stream(RES_MES, &Stream_Service);


	if(errn == 0)
	{
		printf("Data Serialized \n");
	}
	else
	{
		printf("Data Not serialized");
	}
	socket_send_packet((Stream_Service.data),*(Stream_Service.pos));

}
void  sessionStop1(struct iso1EXIDocument* REQ_MES, struct iso1EXIDocument* RES_MES) {

	init_iso1EXIDocument(RES_MES);
	struct iso1BodyType bodyType;
	struct iso1MessageHeaderType header;
	init_iso1BodyType(&bodyType);
	init_iso1MessageHeaderType(&header);

	(RES_MES)->V2G_Message_isUsed = 1;
	bodyType.SessionStopRes_isUsed = 1u;

	printf("Data received From the EV side Successfully \n");
	printf("EVSE side: sessionStop called\n"  );
//	printf("\t Header SessionID = ");
	printBinaryArray(RES_MES->V2G_Message.Header.SessionID.bytes, RES_MES->V2G_Message.Header.SessionID.bytesLen);





	if (sense == 0)
	{
		printf("\t\t ChargingSession = iso2chargingSessionType_Terminated \n");
		for(int i=0; i<SESSION_LENGTH; i++)
			{
				header.SessionID.bytes[i] = SE_SESSION_ID[i];

			}
			//----->>>>>>Bosy ya hager hna kona lazm n7ot l bytelen = 8
			header.SessionID.bytesLen = 8;

		/* Prepare data for EV */

	//	init_iso1SessionStopResType(&RES_MES->V2G_Message.Body.SessionStopRes);
		bodyType.SessionStopRes_isUsed = 1u;


		bodyType.SessionStopRes.ResponseCode = iso1responseCodeType_OK;

	}
	else if (sense == 1)
	{
		printf("\t\t Pantograpgh is not in the upper home position or there is an internal error\n");

		/* Prepare data for EV */



		//init_iso1SessionStopResType(&RES_MES->V2G_Message.Body.SessionStopRes);


		bodyType.SessionStopRes.ResponseCode = iso1responseCodeType_FAILED;
		printf("\t\t Send another Session Stop Request\n");
	}

	else if ( Check_SESSION_ID(REQ_MES->V2G_Message.Header.SessionID.bytes, REQ_MES->V2G_Message.Header.SessionID.bytesLen) == 1)
	{



		bodyType.SessionStopRes.ResponseCode = iso1responseCodeType_FAILED_UnknownSession;
	}






	printf(" Response SESSION STOP Data Sent to EV \n");
	//serialize2EXI2Stream(RES_MES,&streamOut);

	bitstream_t Stream_Service;
	uint8_t errn;

	uint8_t array_ser [BUFFER_RESPONSE];
	size_t pos_serv;
	Stream_Service.size = BUFFER_RESPONSE;
	Stream_Service.data = array_ser;
	Stream_Service.pos = &pos_serv;
	RES_MES->V2G_Message.Header = header;
	RES_MES->V2G_Message.Body = bodyType;

	//----->>>>
	errn = serialize1EXI2Stream(RES_MES, &Stream_Service);


	if(errn == 0)
	{
		printf("Data Serialized \n");
	}
	else
	{
		printf("Data Not serialized");
	}
	socket_send_packet((Stream_Service.data),*(Stream_Service.pos));

}


//The following functions was for testing
//
//void Waiting_For_Request()
//{
//	int bytes = 0;
//	char total;
//	size_t pos1;
//	streamin.size = BUFFER_SIZE;
//	streamin.data = buffer1;
//	streamin.pos = &pos1;
//	bytes = 0;
//			while ((bytes = recv(new_sock, &streamin.data, 256 - total, 0)) > 0)
//			{
//			    total += bytes;
//			    // At this point the buffer is valid from 0..total-1, if that's enough then process it and break, otherwise continue
//			}



//
//void RECIVING()
//{
//	int bytes;
//	size_t pos1;
//	streamin.size = BUFFER_SIZE;
//	streamin.data = buffer1;
//	streamin.pos = &pos1;
//	do
//	{
//		bytes =  socket_recive_packet(streamin.data,&(streamin.pos));
//	}while(bytes<0);
//	//reciving_flag = 1;
//}
//
//void SENDING()
//{
//	int bytes;
//		size_t pos1;
//		streamin.size = BUFFER_SIZE;
//		streamin.data = buffer1;
//		streamin.pos = &pos1;
//		do
//		{
//			bytes =  socket_send_packet(streamin.data,&(streamin.pos));
//
//		}while(bytes<0);
//	//	sending_flag = 1;
//
//}


