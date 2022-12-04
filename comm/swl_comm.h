#ifndef __swl_comm_H
#define __swl_comm_H

#define DELAYTIME  1
#define MEMORYTIME 10

#include "main.h"

typedef enum
{
	bufferfull = 0x00,
	bufferempty = 0x01,
	transmittime = 0x02,
	rxenable = 0x03
}comm;

int DataBufferControl(int s);

void CommBufferDataClear(uint8_t *data);
uint8_t Checksum(uint8_t *chcksum,uint8_t size);

void swl_UartCommunicationTask(const void * argv);
void swl_InitUartCommunication(void);
uint8_t swl_IsUartCommunicationOngoing(void);
void swl_UartTransmitt(uint8_t data[], uint8_t length);

#endif

