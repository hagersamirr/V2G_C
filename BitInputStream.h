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
 * @version 2017-03-02 
 * @contact Richard.Kuntschke@siemens.com
 *
 * <p>Code generated by EXIdizer</p>
 * <p>Schema: V2G_CI_MsgDef.xsd</p>
 *
 *
 ********************************************************************/



/**
 * \file 	BitInputStream.h
 * \brief 	Bit Input Stream
 *
 * 			Read bits and bytes from an underlying input stream.
 *
 */

#ifndef BIT_INPUT_STREAM_H
#define BIT_INPUT_STREAM_H

#ifdef __cplusplus
extern "C" {
#endif

#include "EXITypes.h"

/**
 * \brief 		Read bits
 *
 * 				Read the next num_bits bits and returns result an integer.
 *
 * \param       stream   		Input Stream
 * \param       num_bits		Number of bits
 * \param       b		   		Integer value (out)
 * \return                  	Error-Code <> 0
 *
 */
int readBits(bitstream_t* stream, size_t num_bits, uint32_t* b);


#ifdef __cplusplus
}
#endif

#endif
