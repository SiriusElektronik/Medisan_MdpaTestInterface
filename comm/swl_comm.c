#include "swl_comm.h"
#include "comm.h"
#include "swl_Communication.h"
#include "swl_TestFunctions.h"
#include "swl_HardwareControl.h"
#include <stdio.h>
#include <stdlib.h>

osThreadId	swl_UartCommunicationtaskhandle = NULL;
extern UART_HandleTypeDef huart2;
extern Data485 Buffer485;
extern logic transmitcomplete;
logic receiveflag;
extern uint8_t datasend;
uint32_t receivecounter1 = 0;
uint32_t receivecounter2 = 0;
extern swl_HardwareControl hardwareControl;
void swl_UartCommunicationTask(const void * argv)
{	
	UART_Start(&huart2);
    for(;;)
    {
		if(receiveflag)
		{
			receiveflag = FALSE;
			receivecounter1++;
			uint8_t *TempReceivedBuffer;
			TempReceivedBuffer = Buffer485.Received;
			uint32_t CheckSumRx = Crc32b(Buffer485.Received, Buffer485.ReceivedLengthBuffer - 4);
			uint32_t *receivedChecksum = (uint32_t*)&TempReceivedBuffer[Buffer485.ReceivedLengthBuffer - 4];
			if(CheckSumRx == *receivedChecksum)
			{
				receivecounter2++;
				if(Buffer485.Received[0] == 0x23)
				{
					switch(Buffer485.Received[1])
					{
						case HeartBeat:
							switch(Buffer485.Received[2])
							{
								case Idle:
									
									break;
								default:
									break;
							}
							break;
						case Info:
							switch(Buffer485.Received[2])
							{
								case UniqueID_Control:
									hardwareControl.UniqueId1 = ((Buffer485.Received[6] << 24) + (Buffer485.Received[5] << 16) + (Buffer485.Received[4] << 8) + Buffer485.Received[3]);
									hardwareControl.UniqueId2 = ((Buffer485.Received[10] << 24) + (Buffer485.Received[9] << 16) + (Buffer485.Received[8] << 8) + Buffer485.Received[7]);
									hardwareControl.UniqueId3 = ((Buffer485.Received[14] << 24) + (Buffer485.Received[13] << 16) + (Buffer485.Received[12] << 8) + Buffer485.Received[11]);
									break;
								default:
									break;
							}
							break;
						case Test:
							switch(Buffer485.Received[2])
							{
								case Communication_Control:
									hardwareControl.Communication = Buffer485.Received[3];
									break;
								case Input_Voltage:
									hardwareControl.InputVoltage = Buffer485.Received[3];
									break;
								case Regulator_Voltage:
									hardwareControl.RegulatorVoltage = Buffer485.Received[3];
									break;
								case Motor:
									hardwareControl.Motor = Buffer485.Received[3];
									break;
								case Encoder:
									hardwareControl.Encoder = Buffer485.Received[3];
									break;
								case Pressure_Sensor:
									hardwareControl.PressureSensor = Buffer485.Received[3];
									break;
								case Flow_Sensor:
									hardwareControl.FlowSensor = Buffer485.Received[3];
									break;
								case Heater:
									hardwareControl.Heater = Buffer485.Received[3];
									break;
								case SdCard:
									hardwareControl.SdCard = Buffer485.Received[3];
									break;
								case Button1:
									hardwareControl.Button1 = Buffer485.Received[3];
									break;
								case Button2:
									hardwareControl.Button2 = Buffer485.Received[3];
									break;
								case Encoder_Button:
									hardwareControl.EncoderButton = Buffer485.Received[3];
									break;
								default:
									break;
							}
							break;
					}				
				}
			}
			for(uint8_t i = 0; i < 8; i++)
			{
				Buffer485.Received[i] = 0x00;
			}
		}
		else
		{
			UART_Start(&huart2);
		}
		osDelay(1);
    }
}

void swl_UartTransmitt(uint8_t data[], uint8_t length)
{
	uint32_t CheckSumTx = Crc32b(data, length - 4);
	data[0] = 0xAA;
	data[length - 4] = CheckSumTx & 0xFF;
	data[length - 3] = (CheckSumTx >> 8) & 0xFF;
	data[length - 2] = (CheckSumTx >> 16) & 0xFF;
	data[length - 1] = (CheckSumTx >> 24) & 0xFF;
	TransmitDataBuffer(data, length);
}

void swl_InitUartCommunication(void)
{
	if(swl_IsUartCommunicationOngoing() == FALSE)
	{
		osThreadDef(UartCommunicationProcessTask, swl_UartCommunicationTask, osPriorityNormal, 0 ,64);
		swl_UartCommunicationtaskhandle = osThreadCreate(osThread(UartCommunicationProcessTask), (void *)NULL);
	}
}

uint8_t swl_IsUartCommunicationOngoing(void)
{
	return (swl_UartCommunicationtaskhandle == NULL) ? FALSE : TRUE;
}

uint8_t Checksum(uint8_t *chcksum,uint8_t size)
{
	uint8_t temp = 0;
	for(uint8_t i = 0; i < size; i++)
	{
			temp += chcksum[i];
	}
	return temp;
}
