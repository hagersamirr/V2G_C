/*
 * Copyright (C) 2007-2018 Siemens AG
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU Lesser General Public License as published
 * by the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public License
 * along with this program. If not, see <http://www.gnu.org/licenses/>.
 */

/*******************************************************************
 *
 * @author Daniel.Peintner.EXT@siemens.com
 * @author Sebastian.Kaebisch@siemens.com
 * @version 0.9.4
 * @contact Richard.Kuntschke@siemens.com
 *
 *
 ********************************************************************/



#include "main_example.h"
#include "State_Machine.h"
#include "Responses.h"
#include "Presentation.h"
#include "ByteStream.h"

/*Global Object to Init the State machine*/
stateMachine_t SM;

//Global Variables
//uint8_t buffer1[BUFFER_SIZE];
uint8_t buffer2[BUFFER_SIZE];
bitstream_t stream2;
bitstream_t streamin;
bitstream_t streamOut;
#define BUFFER 256

/*Global Variables for Storing and Sending the requests and responses from & to  EV*/

struct iso1EXIDocument req;

struct iso1EXIDocument res;
struct appHandEXIDocument r;
struct appHandEXIDocument APP_RESPONSE;



#define Socket_Program_Flow 1
#define Reading_Writing_Program_Flow 2

#define Program_FLow Socket_Program_Flow

void printBinaryArray(uint8_t* byte, uint16_t len) {
	unsigned int i;
	for(i=0; i<len; i++) {
		printf("%d ",byte[i]);
	}
	printf("\n");
}






void MessageTesting_APP_HAND (const char * inputfile,const char * outputfile)
{

	int error;
	/* Declaring Buffer for Input Message */
	size_t posDecode = 0 ;
	uint8_t buffer_In[BUFFER_SIZE];

	/* Read Input File Stream */
	error = readBytesFromFile(inputfile, buffer_In , BUFFER_SIZE, &posDecode);

	if (error == 0){
		printf("1- File Is read Successfully!!\n");
	}else{
		printf("File is NOT Read!!");
	}
	/* *****Declaring Input Stream**** */
	bitstream_t Stream_In;
	posDecode = 0;
	Stream_In.size 		= BUFFER_SIZE;
	Stream_In.data 		= buffer_In;
	Stream_In.pos 		= &posDecode;  /* Check */
	Stream_In.buffer  	= 0;
	Stream_In.capacity	= 0;
	buffer_In[BUFFER_SIZE] = 0;



	/**** Decode the Input Stream ****/



	error = decode_appHandExiDocument(&Stream_In, &r);
	if (error == 0){
		printf("2- Message Is Decoded Successfully\n");
	}else{
		printf("Message Decoding FAILED!!\n");
	}

	/***** Message Arrived and Decoded ******/
	Runnable_State();

	/***** Declaring Output Stream *****/
	uint8_t buffer_Out[BUFFER_SIZE];
	bitstream_t Stream_Out;
	size_t pos = 0;
	Stream_Out.size = BUFFER_SIZE;
	Stream_Out.data = buffer_Out;
	Stream_Out.pos = &pos;
	/*****************/

	error = encode_appHandExiDocument(&Stream_Out, &r);
	if(error == 0){
		printf("3- Message is Encoded Successfully\n");
		writeBytesToFile(Stream_Out.data, *Stream_Out.pos, outputfile);
	}

	init_appHandEXIDocument(&r);
}


void MessageTesting(const char * inputfile,const char * outputfile)
{

	int error;
	/* Declaring Buffer for Input Message */
	size_t posDecode = 0 ;
	//	size_t deco = 0;
	uint8_t buffer_In[BUFFER_SIZE];


	/* Read Input File Stream */
	error = readBytesFromFile(inputfile, buffer_In , BUFFER_SIZE, &posDecode);

	if (error == 0){
		printf("1- File Is read Successfully!!\n");
	}else{
		printf("File is NOT Read!!");
	}
	/* *****Declaring Input Stream**** */
	bitstream_t Stream_In;
	posDecode = 0;
	Stream_In.size 		= BUFFER_SIZE;
	Stream_In.data 		= buffer_In;
	Stream_In.pos 		= &posDecode;  /* Check */
	Stream_In.buffer  	= 0;
	Stream_In.capacity	= 0;
	buffer_In[BUFFER_SIZE] = 0;



	/**** Decode the Input Stream ****/


	error = decode_iso1ExiDocument(&Stream_In, &req);
	if (error == 0){
		printf("2- Message Is Decoded Successfully\n");
	}else{
		printf("Message Decoding FAILED!!\n");
	}

	/***** Message Arrived and Decoded ******/
	Runnable_State();

	/***** Declaring Output Stream *****/
	uint8_t buffer_Out[BUFFER_SIZE];
	bitstream_t Stream_Out;
	size_t pos = 0;
	Stream_Out.size = BUFFER_SIZE;
	Stream_Out.data = buffer_Out;
	Stream_Out.pos = &pos;
	/*****************/

	error = encode_iso1ExiDocument(&Stream_Out, &res);
	if(error == 0){
		printf("3- Message is Encoded Successfully\n");
		writeBytesToFile(Stream_Out.data, *Stream_Out.pos, outputfile);
	}
	else{
		printf("Encoding Failed\n");
	}
	init_iso1BodyType(&req.V2G_Message.Body);
}



void State_Init()
{
	StateMachine_Init(&SM);
}



/*************************************************************************************************************
 *                          			 Important Note
 *     If you want to work with the flow of Socket please check line no 58 and change the mode of program flow
 *                                 *
 ************************************************************************************************************/

#if Program_FLow == Socket_Program_Flow
int main_example(int argc, char *argv[]) {

	State_Init();
	Socket_Init();
	uint8_t posRE = 0;
	streamin.size 		= BUFFER_SIZE;
	streamin.data 		= buffer2;
	streamin.pos 		= &posRE;  /* Check */

	while(1)
	{


		if(socket_recive_packet(streamin.data,256)>0)
		{
			deserializeAppHandShakeEXIstream(&streamin,&r);
			//deserialize2Stream2EXI(&streamin, &req);
			deserialize1Stream2EXI(&streamin, &req) ;
			Runnable_State();

		}
		//	Performance_Time(5);

	}
	return 0;

}

#elif Program_FLow == Reading_Writing_Program_Flow
int main_example(int argc, char *argv[]) {

	State_Init();
	printf("---------------Handshake Response Start ---------------\n");
	MessageTesting_APP_HAND ("EvAppHandshakeReqEXI","SEAppHandshakeResEXI");
	printf("---------------Handshake Response End ---------------\n\n\n");


	printf("---------------Session Setup Response Start ---------------\n");
	MessageTesting("EvSessionSetupReqEXI","SESessionSetupResEXI");
	printf("---------------Session Setup Response End---------------\n\n\n");

	printf("---------------Service Discovery Response Start ---------------\n");
	MessageTesting("EvServiceDiscoveryReqEXI","SEServiceDiscoveryResEXI");
	printf("---------------Service Discovery Response End ---------------\n\n\n");

	printf("---------------Service Discovery Response Start ---------------\n");
	MessageTesting("EvServiceDetailReqEXI","SEServiceDetailResEXI");
	printf("---------------Service Discovery Response End ---------------\n\n\n");


	printf("---------------Charging Parameter Discovery Response Start ---------------\n");
	MessageTesting("EvChargingParameterDiscoveryReqEXI","SEChargingParameterDiscoveryResEXI");
	printf("---------------Charging Parameter Discovery Response End ---------------\n\n\n");


	printf("---------------Power Delivery Initial Response Start ---------------\n");
	MessageTesting("EvPowerDeliveryInitReqEXI","SEPowerDeliveryInitResEXI");
	printf("---------------Power Deliver Initial Response End ---------------\n\n\n");

	printf("---------------Session Stop Response Start ---------------\n");
	MessageTesting("EvSessionStopReqEXI","SESessionStopResEXI");
	printf("---------------Session Stop Response End ---------------\n\n\n");


	return 0;



}

#endif
