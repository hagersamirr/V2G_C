/*
 * App_Presentation.c
 *
 *  Created on: Mar 23, 2023
 *      Author: Ahmed Yasser
 */

#include "App_Presentation.h"

int deserializeAppHandShakeEXIstream(bitstream_t* iStream, struct appHandEXIDocument* exi)
{
	int errn=0;
	uint32_t payloadLengthDec;
	if ( (errn = read_v2gtpHeader(iStream->data, &payloadLengthDec)) == 0) {
		*iStream->pos = V2GTP_HEADER_LENGTH;
		if( (errn = decode_appHandExiDocument(iStream, exi)) ) {
			/* an error occurred */
			return errn;
		}

	}
	return errn;


}

int serializeAppHandShakeEXIstream(struct appHandEXIDocument* appHandResp, bitstream_t* oStream)
{
	int errn = 0;
	*oStream->pos = V2GTP_HEADER_LENGTH;
	if( (errn = encode_appHandExiDocument(oStream, appHandResp)) == 0) {
		errn = write_v2gtpHeader(oStream->data, (*oStream->pos)-V2GTP_HEADER_LENGTH, V2GTP_EXI_TYPE);
	}
	return errn;

}
