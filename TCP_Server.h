/*
 * TCP_Server.h
 *
 *  Created on: Dec 23, 2022
 *      Author: Ali Hany
 */

#ifndef TCP_SERVER_H_
#define TCP_SERVER_H_

#include "iso2EXIDatatypes.h"

extern int new_sock;
#define BUFFER_SIZE 2048
extern bitstream_t stream1;
extern uint8_t buffer1[BUFFER_SIZE];


void Socket_Init();
int socket_recive_packet(uint8_t *stream,size_t len);
int socket_send_packet(uint8_t* stream,size_t len);




#endif /* TCP_SERVER_H_ */
