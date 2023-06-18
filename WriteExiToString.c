/*
 * WriteExiToString.c
 *
 *  Created on: Mar 22, 2023
 *      Author: Ahmed Yasser
 */

#include "WriteExiToString.h"
int writeStringToEXIString(char* string, exi_string_character_t* exiString) {
	int pos = 0;
	while(string[pos]!='\0')
	{
		exiString[pos] = string[pos];
		pos++;
	}
for(int i=pos+1; i<=100; i++)
{
	exiString[pos] = 0;
	pos++;
}

	return pos;
}
