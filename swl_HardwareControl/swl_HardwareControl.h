/**
 * @file swl_HardwareControl.h
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-10-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SWL_HARDWARECONTROL_H
#define SWL_HARDWARECONTROL_H

#include "main.h"
#include "swl_HardwareControl.h"
#include "hwl_HardwareControl.h"

void swl_PowerControl(uint8_t state);
void swl_InitServoControl(void);
void swl_StopServo(void);
void swl_ServoControl(int position, int direction);
void swl_IndicatorLedControl(hwl_Colors color);
uint8_t swl_InputLimitSwitchControl(void);
void swl_InputControlTask(const void * argv);
void swl_InitInputControl(void);
uint8_t swl_IsInputControlOngoing(void);
void swl_ServoPosition(int pos, uint16_t pot_val, int power);
void swl_ServoBrake(int power);
typedef enum
{
	None,
    Success,
    Error,
	TimeOut,
}swl_TestResults;

typedef enum
{
	Unknown,
    Inserted,
	Removed,
}swl_CardState;

typedef struct
{
	swl_CardState CardState;
	swl_TestResults Communication;
	uint32_t UniqueId1;
	uint32_t UniqueId2;
	uint32_t UniqueId3;
	swl_TestResults InputVoltage;
	swl_TestResults RegulatorVoltage;
	swl_TestResults Motor;
	swl_TestResults Encoder;
	swl_TestResults PressureSensor;
	swl_TestResults FlowSensor;
	swl_TestResults Heater;
	swl_TestResults SdCard;
	swl_TestResults Button1;
	swl_TestResults Button2;
	swl_TestResults EncoderButton;
}swl_HardwareControl;

#endif
