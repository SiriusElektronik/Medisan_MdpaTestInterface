/**
 * @file hwl_HardwareControl.h
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-10-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef HWL_HARDWARECONTROL_H
#define HWL_HARDWARECONTROL_H

#include "main.h"
#include "hwl_HardwareControl.h"

#define INPUTLIMITSWITCH HAL_GPIO_ReadPin(M_INP1_GPIO_Port, M_INP1_Pin)
#define OUTPUTRGBRHIGH HAL_GPIO_WritePin(M_RGB_R_GPIO_Port, M_RGB_R_Pin, GPIO_PIN_SET);
#define OUTPUTRGBGHIGH HAL_GPIO_WritePin(M_RGB_G_GPIO_Port, M_RGB_G_Pin, GPIO_PIN_SET);
#define OUTPUTRGBBHIGH HAL_GPIO_WritePin(M_RGB_B_GPIO_Port, M_RGB_B_Pin, GPIO_PIN_SET);
#define OUTPUTRGBRLOW HAL_GPIO_WritePin(M_RGB_R_GPIO_Port, M_RGB_R_Pin, GPIO_PIN_RESET);
#define OUTPUTRGBGLOW HAL_GPIO_WritePin(M_RGB_G_GPIO_Port, M_RGB_G_Pin, GPIO_PIN_RESET);
#define OUTPUTRGBBLOW HAL_GPIO_WritePin(M_RGB_B_GPIO_Port, M_RGB_B_Pin, GPIO_PIN_RESET);

typedef enum 
{
    Off,
    Red,
    Green,
    Blue,
    Yellow,
    White,
    Magenta,
    Cyan
}hwl_Colors;

void hwl_PowerControl(uint8_t state);
void hwl_InitServoControl(void);
void hwl_StopServo(void);
void hwl_ServoControl(int position, int direction);
void hwl_IndicatorLedControl(hwl_Colors color);
uint8_t hwl_InputLimitSwitchControl(void);
void hwl_ServoBrake(int power);
#endif
