/*
 * Presentation.c
 *
 *  Created on: Mar 20, 2023
 *      Author: Ahmed Yasser
 */
#include "Presentation.h"

int serialize1EXI2Stream(struct iso1EXIDocument* exiIn, bitstream_t* stream) {
	int errn;
	*stream->pos = V2GTP_HEADER_LENGTH;  // v2gtp header //
	if( (errn = encode_iso1ExiDocument(stream, exiIn)) == 0) {
		errn = write_v2gtpHeader(stream->data, (*stream->pos)-V2GTP_HEADER_LENGTH, V2GTP_EXI_TYPE);
	}
	return errn;
}

int deserialize1Stream2EXI(bitstream_t* streamIn, struct iso1EXIDocument* exi) {
	int errn;
	uint32_t payloadLength;

	*streamIn->pos = 0;

	if ( (errn = read_v2gtpHeader(streamIn->data, &payloadLength)) == 0) {
		*streamIn->pos += V2GTP_HEADER_LENGTH;
	}

	errn = decode_iso1ExiDocument(streamIn, exi);

	return errn;
}

