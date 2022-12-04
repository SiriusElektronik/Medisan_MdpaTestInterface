/**
 * @file swl_TestFunctions.h
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-10-12
 * 
 * @copyright Copyright (c) 2022
 * 
 */
 
 #include "swl_Communication.h"
 #include "swl_HardwareControl.h"
 
void swl_InfoFunction(swl_CommandCodes cmd, swl_ProcessCodes process);
void swl_TestFuction(swl_TestResults *hardware, swl_CommandCodes cmd, swl_ProcessCodes process);
void swl_SendCmd(swl_CommandCodes cmd, swl_ProcessCodes process);