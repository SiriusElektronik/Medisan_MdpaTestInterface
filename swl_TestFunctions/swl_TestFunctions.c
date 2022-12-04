/**
 * @file swl_TestFunctions.c
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-10-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */


#include "swl_TestFunctions.h"
#include "swl_comm.h"
#define TransmittBufferSize 8
extern swl_HardwareControl hardwareControl;
uint8_t TransmittBuffer[TransmittBufferSize];

void swl_InfoFunction(swl_CommandCodes cmd, swl_ProcessCodes process)
{
	uint8_t count = 0;
	TransmittBuffer[1] = cmd;
	TransmittBuffer[2] = process;
	if(process == UniqueID_Control)
	{
		while(hardwareControl.UniqueId1 == 0xFFFFFFFF && hardwareControl.UniqueId2 == 0xFFFFFFFF && hardwareControl.UniqueId3 == 0xFFFFFFFF)
		{
			swl_UartTransmitt(TransmittBuffer, TransmittBufferSize);
			osDelay(200);
			count++;
			if(count > 20)
			{
				hardwareControl.UniqueId1 = 0xFFFFFFFF;
				hardwareControl.UniqueId2 = 0xFFFFFFFF;
				hardwareControl.UniqueId3 = 0xFFFFFFFF;
				break;
			}
		}
	}
}

void swl_TestFuction(swl_TestResults *hardware, swl_CommandCodes cmd, swl_ProcessCodes process)
{
	uint8_t count = 0;
	TransmittBuffer[1] = cmd;
	TransmittBuffer[2] = process;
	while(*hardware == None)
	{
		swl_UartTransmitt(TransmittBuffer, TransmittBufferSize);
		osDelay(200);
		count++;
		if(count > 20)
		{
			*hardware = TimeOut;
			break;
		}
	}
}

void swl_SendCmd(swl_CommandCodes cmd, swl_ProcessCodes process)
{
	TransmittBuffer[1] = cmd;
	TransmittBuffer[2] = process,
	swl_UartTransmitt(TransmittBuffer, TransmittBufferSize);
}