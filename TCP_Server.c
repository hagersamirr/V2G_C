/*
 * TCP_Server.c
 *
 *  Created on: Dec 23, 2022
 *      Author: Ali Hany
 */


#include<stdio.h>
#include<winsock2.h>
#include "iso2EXIDatatypes.h"
#include "EXITypes.h"
#include "TCP_Server.h"
#include <time.h>

uint8_t gTime_Flag=0;

int new_sock;

bitstream_t stream1;
uint8_t buffer1[BUFFER_SIZE];

uint8_t Performance_Time(int number_of_seconds)
{
	// Converting time into milli_seconds
	int milli_seconds = 1000 * number_of_seconds;

	// Storing start time
	clock_t start_time = clock();

	// looping till required time is not achieved
	while (clock() < start_time + milli_seconds)
		;
	return gTime_Flag=1;
}



void Socket_Init()
{
	int server_fd;

	struct sockaddr_in address;
	int addrlen = sizeof(address);

	WSADATA wsa;

	printf("\nInitialising Winsock...");

	if (WSAStartup(MAKEWORD(2,2),&wsa) != 0)
	{
		printf("Failed. Error Code : %d",WSAGetLastError());
		exit(1);
	}

	printf("Initialised.\n");

	//Create a socket

	if((server_fd = socket(AF_INET , SOCK_STREAM , 0 )) < 0)
	{
		printf("Could not create socket : %d" , WSAGetLastError());
	}

	printf("Socket created.\n");

	//Prepare the sockaddr_in structure

	address.sin_family = AF_INET;
	address.sin_addr.s_addr = INADDR_ANY;

	//address.sin_addr.s_addr = inet_addr("192.168.1.12");
	address.sin_port = htons( 8080 );

	//Bind

	if( bind(server_fd ,(struct sockaddr *)&address , sizeof(address)) <0)
	{
		printf("Bind failed with error code : %d" , WSAGetLastError());
	}

	puts("Bind done");


	//Listen to incoming connections

	if (listen(server_fd ,3) < 0)
	{
		puts ("listen error");
	}
	puts("listening...");

	if ((new_sock = accept(server_fd , (struct sockaddr *)&address, &addrlen)) < 0)
	{
		printf("accept failed with error code : %d" , WSAGetLastError());
	}

	puts("Connection accepted");

}

int socket_recive_packet(uint8_t* stream,size_t len)
{
	int bytes;


    //memset(stream, 0, BUFFER_SIZE);

	bytes = recv(new_sock, (char*)stream, BUFFER_SIZE, 0);

	return bytes;
}

int socket_send_packet(uint8_t* stream,size_t len)
{
	int bytes;

	bytes = send(new_sock, (char*)stream, len, 0);

	if(bytes < 0)
	{
		printf("Error: send\n");

	}
	else {
		printf("\n =========Data Sent===========\n");
	}
	return bytes;
}
