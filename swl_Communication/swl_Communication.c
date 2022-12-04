/**
 * @file swl_Communication.c
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-10-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "swl_Communication.h"
#include "usbd_cdc_if.h"

osThreadId	swl_Communicationtaskhandle = NULL;

#define UsbRxBufferSize 8
#define UsbTxBufferSize 8
uint8_t UsbRxBuffer[UsbRxBufferSize];
uint8_t UsbRxDataBuffer[UsbRxBufferSize];
uint8_t UsbTxBuffer[19];

swl_ProcessCodes USBProcessCode;
swl_CommandCodes USBCommandCode;

void swl_CommunicationTask(const void * argv)
{	
    for(;;)
    {	
		uint32_t CheckSumUSBRx = Crc32b(UsbRxBuffer, UsbRxBufferSize - 4);
		if((CheckSumUSBRx & 0xFF) == UsbRxBuffer[UsbRxBufferSize - 4] && ((CheckSumUSBRx >> 8)& 0xFF) == UsbRxBuffer[UsbRxBufferSize - 3] &&
			((CheckSumUSBRx >> 16) & 0xFF) == UsbRxBuffer[UsbRxBufferSize - 2] && ((CheckSumUSBRx >> 24) & 0xFF) == UsbRxBuffer[UsbRxBufferSize - 1])
		{
			swl_BufferCopy(UsbRxBuffer, UsbRxDataBuffer, UsbRxBufferSize);
			USBCommandCode = (swl_CommandCodes)UsbRxDataBuffer[1];
			USBProcessCode = (swl_ProcessCodes)UsbRxDataBuffer[2];
			swl_BufferClear(UsbRxBuffer, UsbRxBufferSize);
		}
		osDelay(1);
    }
}

void swl_UsbTransmitt(uint8_t data[], uint8_t length)
{
	uint32_t CheckSumTx = Crc32b(data, length - 4);
	data[0] = 0xAA;
	data[length - 4] = CheckSumTx & 0xFF;
	data[length - 3] = (CheckSumTx >> 8) & 0xFF;
	data[length - 2] = (CheckSumTx >> 16) & 0xFF;
	data[length - 1] = (CheckSumTx >> 24) & 0xFF;
	CDC_Transmit_FS(data, length);
	for(uint8_t i = 1; i < length - 1; i++)
	{
		data[i] = 0x00;
	}
}

void swl_InitCommunication(void)
{
	if(swl_IsCommunicationOngoing() == FALSE)
	{
		osThreadDef(CommunicationProcessTask, swl_CommunicationTask, osPriorityNormal, 0 ,128);
		swl_Communicationtaskhandle = osThreadCreate(osThread(CommunicationProcessTask), (void *)NULL);
	}
}

uint8_t swl_IsCommunicationOngoing(void)
{
	return (swl_Communicationtaskhandle == NULL) ? FALSE : TRUE;
}


void swl_BufferClear(uint8_t *arr, uint8_t size)
{
    for(int i = 0 ; i < size ; i++)
    {
        arr[i] = 0x00;
    }
}

void swl_BufferCopy(uint8_t CopiedBuffer[], uint8_t CopyBuffer[], uint8_t Length)
{
	for(uint8_t i = 0; i < Length; i++)
	{
		CopyBuffer[i] = CopiedBuffer[i];
	}
}

uint32_t Crc32b(uint8_t Data[], uint8_t Length)
{
    uint32_t i, j;
    uint32_t crc, msb;

    crc = 0xFFFFFFFF;
    for (i = 0; i < Length; i++)
    {   // xor next byte to upper bits of crc
        crc ^= (((uint32_t)Data[i]) << 24);
        for (j = 0; j < 8; j++)
        {  // Do eight times.
            msb = crc >> 31;
            crc <<= 1;
            crc ^= (0 - msb) & 0x04C11DB7;
        }
    }
    return crc; // don't complement crc on output
}
