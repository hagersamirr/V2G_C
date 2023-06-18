/*
 * App_Presentation.h
 *
 *  Created on: Mar 23, 2023
 *      Author: Ahmed Yasser
 */

#ifndef APP_PRESENTATION_H_
#define APP_PRESENTATION_H_

#include "main_example.h"
int deserializeAppHandShakeEXIstream(bitstream_t* iStream, struct appHandEXIDocument* exi);
int serializeAppHandShakeEXIstream(struct appHandEXIDocument* appHandResp, bitstream_t* oStream);

#endif /* APP_PRESENTATION_H_ */
