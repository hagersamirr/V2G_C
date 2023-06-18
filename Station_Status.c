/*
 * Station_Status.c
 *
 *  Created on: Mar 4, 2023
 *      Author: Ahmed Yasser
 */

#include "Station_Status.h"
#include "main.h"
#include <stdint.h>



void GENERATING_SESSION_ID(unsigned int *arr,int n)
{
	for(int i=0; i<n; i++)
	{
		arr[i]= rand()%10;
	}
	for(int i =0; i<n; i++)
	{
		printf("%d",arr[i]);
	}
}

int Check_SESSION_ID(unsigned char* REQ_MESSAGE_SESSION_ID, int len)
{
	int i;
		for(i=0;i<len;i++)
		{
			if((unsigned char )REQ_MESSAGE_SESSION_ID[i]!=SE_SESSION_ID[i])
				return 1;
		}
		return 0;
	}


int checkBinaryArray(uint8_t* byte, uint16_t len)
{
	unsigned char i,x;
	for (i = 0; i < len; i++)
	{
		if(byte[i] == 0)
		{
			printf("%d ",byte[i]);

		}
		else
		{
			printf(" error\n");
		return	x = 1;

		}
		x=0;

	}
	return x;
}

char V2G_SECC_MSG_Performance_Time()
{
	char errn;
	int i=0;
	for(; i<1000; i++);
	errn = 1;
	return errn;
}





#define TIME_OUT 0;



