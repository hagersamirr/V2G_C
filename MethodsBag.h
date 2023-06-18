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
* \file 	MethodsBag.h
* \brief 	Method bag for bit and octet functions
*
*/

#ifndef METHODS_BAG_H
#define METHODS_BAG_H



#include <stdint.h>
#include <stddef.h>

/**
 * \brief  	Returns the number of bits to identify the characteristics.
 *
 * \param       characteristics	number of characteristics
 * \param       codingLength   	number of bits
 * \return                  	Error-Code <> 0
 *
 */
int exiGetCodingLength(size_t characteristics, size_t* codingLength);


/**
 * \brief  	Returns the least number of 7 bit-blocks that is needed to represent the passed integer value
 *
 *			Note: Returns 1 if passed parameter is 0.
 *
 * \param       n				integer value
 * \return                  	Error-Code <> 0
 *
 */
uint8_t numberOf7BitBlocksToRepresent(uint32_t n);


#endif

