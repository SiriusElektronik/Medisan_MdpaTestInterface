/**
 * @file swl_Communication.h
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-10-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SWL_COMMUNICATION_H
#define SWL_COMMUNICATION_H

#include "main.h"
#include "swl_Communication.h"
#include "hwl_Communication.h"

typedef enum
{
	Idle,
    CardState,
    UniqueID_Control,
    Communication_Control,
    Input_Voltage,
    Regulator_Voltage,
    Motor,
    Encoder,
    Pressure_Sensor,
    Flow_Sensor,
    Heater,
    SdCard,
    Button1,
    Button2,
    Encoder_Button,
	Power_On,
	Power_Off
}swl_ProcessCodes;

typedef enum
{
	CommandIdle,
    HeartBeat,
    Info,
    Test,
    InsertCard,
    RemoveCard
}swl_CommandCodes;

void swl_UsbTransmitt(uint8_t data[], uint8_t length);
void swl_CommunicationTask(const void * argv);
void swl_InitCommunication(void);
uint8_t swl_IsCommunicationOngoing(void);
void swl_BufferClear(uint8_t *arr, uint8_t size);
void swl_BufferCopy(uint8_t CopiedBuffer[], uint8_t CopyBuffer[], uint8_t Length);
uint32_t Crc32b(uint8_t Data[], uint8_t Length);
#endif
