/**
 * @file swl_Application.c
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-10-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

#include "swl_Application.h"
#include "swl_Communication.h"
#include "swl_HardwareControl.h"	
#include "swl_comm.h"
#include "swl_TestFunctions.h"

extern ADC_HandleTypeDef hadc1;
osThreadId	swl_applicationtaskhandle = NULL;
extern swl_ProcessCodes USBProcessCode;
extern swl_CommandCodes USBCommandCode;
extern uint8_t UsbTxBuffer[19];
extern uint8_t INPUTLIMITSWICTHVALUE;
swl_HardwareControl hardwareControl;
uint32_t transmittcounter = 0;
uint8_t datasend = FALSE;
uint16_t AD_RES = 0;
extern uint8_t pwmvalue;
extern uint16_t PeriodTime;

void HAL_ADC_ConvCpltCallback(ADC_HandleTypeDef* hadc)
{
    AD_RES = HAL_ADC_GetValue(&hadc1);
	HAL_ADC_Start_IT(&hadc1);
}

void swl_ApplicationTask(const void * argv)
{
	HAL_ADCEx_Calibration_Start(&hadc1);
	HAL_ADC_Start_IT(&hadc1);
	swl_InitCommunication();
	swl_InitInputControl();
	swl_InitUartCommunication();
	swl_InitServoControl();
    for(;;)
    {	
		 //Debug Codes
		 PeriodTime = 500;
		 while(TRUE)
		 {
			swl_InfoFunction(Info, UniqueID_Control);
			swl_TestFuction(&hardwareControl.Communication, Test, Communication_Control);
			swl_TestFuction(&hardwareControl.InputVoltage, Test, Input_Voltage);
			swl_TestFuction(&hardwareControl.RegulatorVoltage, Test, Regulator_Voltage);
			swl_TestFuction(&hardwareControl.Motor, Test, Motor);
			swl_TestFuction(&hardwareControl.Encoder, Test, Encoder);
			swl_TestFuction(&hardwareControl.PressureSensor, Test, Pressure_Sensor);
			swl_TestFuction(&hardwareControl.FlowSensor, Test, Flow_Sensor);
			swl_TestFuction(&hardwareControl.Heater, Test, Heater);
			swl_TestFuction(&hardwareControl.SdCard, Test, SdCard);
			swl_TestFuction(&hardwareControl.Button1, Test, Button1);
			swl_TestFuction(&hardwareControl.Button2, Test, Button2);
			swl_TestFuction(&hardwareControl.EncoderButton, Test, Encoder_Button);
		 }
		 //----------------------------------
		 
		 
		hardwareControl.UniqueId1 = 0xFFFFFFFF;
		hardwareControl.UniqueId2 = 0xFFFFFFFF;
		hardwareControl.UniqueId3 = 0xFFFFFFFF;
		switch(USBCommandCode)
		{
			case HeartBeat:
				swl_SendCmd(HeartBeat, Idle);
				UsbTxBuffer[1] = HeartBeat;
				switch(USBProcessCode)
				{
					case CardState:
						UsbTxBuffer[2] = CardState;
						if(INPUTLIMITSWICTHVALUE)
						{
							UsbTxBuffer[3] = Removed;
						}
						else
						{
							UsbTxBuffer[3] = Inserted;
						}
						swl_UsbTransmitt(UsbTxBuffer, 8);
						USBProcessCode = Idle;
						break;
					default:
						break;
				}
				USBCommandCode = CommandIdle;
				break;
			case Info:
				UsbTxBuffer[1] = Info;
				switch(USBProcessCode)
				{
					case Power_On:
						swl_PowerControl(TRUE);
						break;
					case Power_Off:
						swl_PowerControl(FALSE);
						break;
					case UniqueID_Control:
						swl_InfoFunction(Info, UniqueID_Control);
						UsbTxBuffer[2] = UniqueID_Control;
						
						UsbTxBuffer[3] = hardwareControl.UniqueId1 & 0xFF;
						UsbTxBuffer[4] = (hardwareControl.UniqueId1 >> 8) & 0xFF;
						UsbTxBuffer[5] = (hardwareControl.UniqueId1 >> 16) & 0xFF;
						UsbTxBuffer[6] = (hardwareControl.UniqueId1 >> 24) & 0xFF;
						 
						UsbTxBuffer[7] = hardwareControl.UniqueId2 & 0xFF;
						UsbTxBuffer[8] = (hardwareControl.UniqueId2 >> 8) & 0xFF;
						UsbTxBuffer[9] = (hardwareControl.UniqueId2 >> 16) & 0xFF;
						UsbTxBuffer[10] = (hardwareControl.UniqueId2 >> 24) & 0xFF;
						
						UsbTxBuffer[11] = hardwareControl.UniqueId3 & 0xFF;
						UsbTxBuffer[12] = (hardwareControl.UniqueId3 >> 8) & 0xFF;
						UsbTxBuffer[13] = (hardwareControl.UniqueId3 >> 16) & 0xFF;
						UsbTxBuffer[14] = (hardwareControl.UniqueId3 >> 24) & 0xFF;
					
						swl_UsbTransmitt(UsbTxBuffer, 19);
						break;
					default:
						break;
				}
				break;
			case Test:
				UsbTxBuffer[1] = Test;
				switch(USBProcessCode)
				{
					case Communication_Control:
						swl_TestFuction(&hardwareControl.Communication, Test, Communication_Control);
						UsbTxBuffer[2] = Communication_Control;
						
						UsbTxBuffer[3] = hardwareControl.Communication;
						swl_UsbTransmitt(UsbTxBuffer, 8);
						break;
					case Input_Voltage:
						swl_TestFuction(&hardwareControl.InputVoltage, Test, Input_Voltage);
						UsbTxBuffer[2] = Input_Voltage;
						UsbTxBuffer[3] = hardwareControl.InputVoltage;
						swl_UsbTransmitt(UsbTxBuffer, 8);
						break;
					case Regulator_Voltage:
						swl_TestFuction(&hardwareControl.RegulatorVoltage, Test, Regulator_Voltage);
						UsbTxBuffer[2] = Regulator_Voltage;
						
						UsbTxBuffer[3] = hardwareControl.RegulatorVoltage;
						swl_UsbTransmitt(UsbTxBuffer, 8);
						break;
					case Motor:
						swl_TestFuction(&hardwareControl.Motor, Test, Motor);
						UsbTxBuffer[2] = Motor;
						
						UsbTxBuffer[3] = hardwareControl.Motor;
						swl_UsbTransmitt(UsbTxBuffer, 8);
						break;
					case Encoder:
						swl_TestFuction(&hardwareControl.Encoder, Test, Encoder);
						UsbTxBuffer[2] = Encoder;
						
						UsbTxBuffer[3] = hardwareControl.Encoder;
						swl_UsbTransmitt(UsbTxBuffer, 8);
						break;
					case Pressure_Sensor:
						swl_TestFuction(&hardwareControl.PressureSensor, Test, Pressure_Sensor);
						UsbTxBuffer[2] = Pressure_Sensor;
						
						UsbTxBuffer[3] = hardwareControl.PressureSensor;
						swl_UsbTransmitt(UsbTxBuffer, 8);
						break;
					case Flow_Sensor:
						swl_TestFuction(&hardwareControl.FlowSensor, Test, Flow_Sensor);
						UsbTxBuffer[2] = Flow_Sensor;
						
						UsbTxBuffer[3] = hardwareControl.FlowSensor;
						swl_UsbTransmitt(UsbTxBuffer, 8);
						break;
					case Heater:
						swl_TestFuction(&hardwareControl.Heater, Test, Heater);
						UsbTxBuffer[2] = Heater;
						
						UsbTxBuffer[3] = hardwareControl.Heater;
						swl_UsbTransmitt(UsbTxBuffer, 8);
						break;
					case SdCard:
						swl_TestFuction(&hardwareControl.SdCard, Test, SdCard);
						UsbTxBuffer[2] = SdCard;
						
						UsbTxBuffer[3] = hardwareControl.SdCard;
						swl_UsbTransmitt(UsbTxBuffer, 8);
						break;
					case Button1:
						swl_TestFuction(&hardwareControl.Button1, Test, Button1);
						UsbTxBuffer[2] = Button1;
						
						UsbTxBuffer[3] = hardwareControl.Button1;
						swl_UsbTransmitt(UsbTxBuffer, 8);
						break;
					case Button2:
						swl_TestFuction(&hardwareControl.Button2, Test, Button2);
						UsbTxBuffer[2] = Button2;
						
						UsbTxBuffer[3] = hardwareControl.Button2;
						swl_UsbTransmitt(UsbTxBuffer, 8);
						break;
					case Encoder_Button:
						swl_TestFuction(&hardwareControl.EncoderButton, Test, Encoder_Button);
						UsbTxBuffer[2] = Encoder_Button;
						
						UsbTxBuffer[3] = hardwareControl.EncoderButton;
						swl_UsbTransmitt(UsbTxBuffer, 8);
						break;
					default:
						break;
				}
				break;
			case InsertCard:
				pwmvalue = 20;
				break;
			case RemoveCard:
				pwmvalue = 90;
			hardwareControl.UniqueId1 = 0xFFFFFFFF;
			hardwareControl.UniqueId2 = 0xFFFFFFFF;
			hardwareControl.UniqueId3 = 0xFFFFFFFF;
			hardwareControl.Communication = None;
			hardwareControl.InputVoltage = None;
			hardwareControl.RegulatorVoltage = None;
			hardwareControl.Motor = None;
			hardwareControl.Encoder = None;
			hardwareControl.PressureSensor = None;
			hardwareControl.FlowSensor = None;
			hardwareControl.Heater = None;
			hardwareControl.SdCard = None;
			hardwareControl.Button1 = None;
			hardwareControl.Button2 = None;
			hardwareControl.EncoderButton = None;
			default:
				break;
		}
		USBCommandCode = CommandIdle;
		USBProcessCode = Idle;
		osDelay(1);
    }
}

void swl_InitApplication(void)
{
	if(swl_IsApplicationOngoing() == FALSE)
	{
		osThreadDef(ApplicationProcessTask, swl_ApplicationTask, osPriorityNormal, 0 ,128);
		swl_applicationtaskhandle = osThreadCreate(osThread(ApplicationProcessTask), (void *)NULL);
	}
}

uint8_t swl_IsApplicationOngoing(void)
{
	return (swl_applicationtaskhandle == NULL) ? FALSE : TRUE;
}
