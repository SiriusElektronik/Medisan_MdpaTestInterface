/**
 * @file swl_HardwareControl.c
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-10-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "swl_HardwareControl.h"

uint32_t AD_RES1 = 0;
uint16_t AD_RES2 = 0;
uint8_t count = 0;
uint8_t pwmvalue = 65;
extern uint16_t AD_RES;
osThreadId	swl_InputControltaskhandle = NULL;

uint8_t INPUTLIMITSWICTHVALUE;

void swl_PowerControl(uint8_t state)
{
	hwl_PowerControl(state);
}
void swl_InitServoControl(void)
{
    hwl_InitServoControl();
}

void swl_StopServo(void)
{
	hwl_StopServo();
}

void swl_ServoControl(int position, int direction)
{
	hwl_ServoControl(position, direction);
}

void swl_ServoPosition(int pos, uint16_t pot_val, int power)
{
	if(AD_RES > pos)
	{
		swl_ServoControl(power, 1);
		while(AD_RES > pos);
		swl_StopServo();
	}
	if(AD_RES < pos)
	{
		swl_ServoControl(power, 2);
		while(AD_RES < pos);
		swl_StopServo();
	}
}

void swl_ServoBrake(int power)
{
	hwl_ServoBrake(power);
}

void swl_IndicatorLedControl(hwl_Colors color)
{
    hwl_IndicatorLedControl(color);
}

uint8_t swl_InputLimitSwitchControl(void)
{
	return hwl_InputLimitSwitchControl();
}

void swl_InputControlTask(const void * argv)
{	
    for(;;)
    {	
        INPUTLIMITSWICTHVALUE = swl_InputLimitSwitchControl();	
		if(count < 64)
		{
			count++;
			AD_RES1 = AD_RES1 + AD_RES;
		}
		else if(count == 64)
		{
			AD_RES1 = AD_RES1 / 64;
			AD_RES2 = AD_RES1 / 34;
			if(AD_RES2 > pwmvalue)
			{
				swl_ServoControl(120, 1);
			}
			else if(AD_RES2 > pwmvalue - 10 && AD_RES2 < pwmvalue + 10)
			{
				swl_ServoBrake(179);
			}
			else
			{
				swl_ServoControl(120, 2);
			}
			count = 0;
		}
		osDelay(1);
    }
}

void swl_InitInputControl(void)
{
	if(swl_IsInputControlOngoing() == FALSE)
	{
		osThreadDef(InputControlProcessTask, swl_InputControlTask, osPriorityNormal, 0, 128);
		swl_InputControltaskhandle = osThreadCreate(osThread(InputControlProcessTask), (void *)NULL);
	}
}

uint8_t swl_IsInputControlOngoing(void)
{
	return (swl_InputControltaskhandle == NULL) ? FALSE : TRUE;
}
