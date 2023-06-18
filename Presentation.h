/*
 * Presentation.h
 *
 *  Created on: Mar 20, 2023
 *      Author: Ahmed Yasser
 */

#ifndef PRESENTATION_H_
#define PRESENTATION_H_

#include "main_example.h"
int serialize1EXI2Stream(struct iso1EXIDocument* exiIn, bitstream_t* stream) ;
int deserialize1Stream2EXI(bitstream_t* streamIn, struct iso1EXIDocument* exi) ;

#endif /* PRESENTATION_H_ */
