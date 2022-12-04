#ifndef __comm_H
#define __comm_H

#include "usart.h"
#include "swl_comm.h"

#define UART_BUFFER_SIZE		(uint8_t)40

#define DATACOMMAND 	(uint8_t)0xCB
#define POLLCOMMAND 	(uint8_t)0xBA
#define ADDRESSCOMAND (uint8_t)0x99
#define DATAOK 				(uint8_t)0xCC
#define DATAERR 			(uint8_t)0xCD

typedef enum
{
	False = 0,
	True = 1
	
}logic;

typedef struct rs485
{
		uint8_t ReceivedLengthBuffer;
		uint8_t Transmited[UART_BUFFER_SIZE];
		comm transmitflag;
		uint8_t Received[UART_BUFFER_SIZE];
}Data485;


void UART_Start(UART_HandleTypeDef *huart);
void USER_UART_IRQHandler(UART_HandleTypeDef *huart);
void AllClearFlags(void);
void TransmitDataBuffer(uint8_t *data,uint8_t size);
void hwl_DisableITSources(void);

#endif

