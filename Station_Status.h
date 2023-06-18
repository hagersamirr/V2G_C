/*
 * Station_Status.h
 *
 *  Created on: Mar 4, 2023
 *      Author: Ahmed Yasser
 */

#ifndef STATION_STATUS_H_
#define STATION_STATUS_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <stdint.h>


/*Hna baa fe awl l session setup response h3ml generate l Session id gded mo5tlf 3n l session l ableh w hyt5zn fe l global arrar aly asmo SE_SESSION_ID 34an n2dr n3ml check 3aleh fe ay response*/

void GENERATING_SESSION_ID(unsigned int *arr,int n);
/*l function de baa bttcheck fe kol response an l session id al gded aly na 3mltlo generation fe l function l fo2 mashy s7 w tmm hn3ml check kol shwya*/
int Check_SESSION_ID(unsigned char* REQ_MESSAGE_SESSION_ID, int len);

int checkBinaryArray(uint8_t* byte, uint16_t len);

#endif /* STATION_STATUS_H_ */
