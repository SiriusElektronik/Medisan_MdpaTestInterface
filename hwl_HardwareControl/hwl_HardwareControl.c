/**
 * @file hwl_HardwareControl.c
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2022-10-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "hwl_HardwareControl.h"

extern TIM_HandleTypeDef htim2;

void hwl_PowerControl(uint8_t state)
{
	if(state)
	{
		HAL_GPIO_WritePin(M_POWER_GPIO_Port,M_POWER_Pin,GPIO_PIN_SET);
	}
	else
	{
		HAL_GPIO_WritePin(M_POWER_GPIO_Port,M_POWER_Pin,GPIO_PIN_RESET);
	}
}

void hwl_InitServoControl(void)
{
	TIM2->CCR3 = 0;
	TIM2->CCR4 = 0;
    HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Start(&htim2, TIM_CHANNEL_4);
}

void hwl_StopServo(void)
{
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_3);
	HAL_TIM_PWM_Stop(&htim2, TIM_CHANNEL_4);
}

void hwl_ServoBrake(int power)
{
	TIM2->CCR3 = power;
	TIM2->CCR4 = power;
}

void hwl_ServoControl(int position, int direction)
{
	if(direction == 1)
	{
		TIM2->CCR3 = 0;
		TIM2->CCR4 = position;
	}
	else if(direction == 2)
	{
		TIM2->CCR4 = 0;
		TIM2->CCR3 = position;
	}
}

void hwl_IndicatorLedControl(hwl_Colors color)
{
	switch (color)
	{
	case Off:
		OUTPUTRGBRHIGH;
		OUTPUTRGBGHIGH;
		OUTPUTRGBBHIGH;
		break;
	case Red:
		OUTPUTRGBRLOW;
		OUTPUTRGBGHIGH;
		OUTPUTRGBBHIGH;
		break;
	case Green:
		OUTPUTRGBRHIGH;
		OUTPUTRGBGLOW;
		OUTPUTRGBBHIGH;
		break;
	case Blue:
		OUTPUTRGBRHIGH;
		OUTPUTRGBGHIGH;
		OUTPUTRGBBLOW;
		break;
	case Yellow:
		OUTPUTRGBRLOW;
		OUTPUTRGBGLOW;
		OUTPUTRGBBHIGH;
		break;
	case White:
		OUTPUTRGBRLOW;
		OUTPUTRGBGLOW;
		OUTPUTRGBBLOW;
		break;
	case Magenta:
		OUTPUTRGBRLOW;
		OUTPUTRGBGHIGH;
		OUTPUTRGBBLOW;
		break;
	case Cyan:
		OUTPUTRGBRHIGH;
		OUTPUTRGBGLOW;
		OUTPUTRGBBLOW;
		break;
	default:
		break;
	}
}

uint8_t hwl_InputLimitSwitchControl(void)
{
	uint8_t state;
	if(GPIO_PIN_RESET == INPUTLIMITSWITCH)
	{
	for(uint8_t i = 0; i < 20; i++)
	{
		osDelay(1);
		if(GPIO_PIN_RESET == INPUTLIMITSWITCH)
		{
			state = GPIO_PIN_RESET;
		}
		else
		{
			state = GPIO_PIN_SET;
			break;
		}
	}
	}
	else
	{
		state = GPIO_PIN_SET;
	}
	return state;
}
