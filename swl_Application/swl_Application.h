/**
 * @file swl_Application.h
 * @author Furkan AYDOĞAN (furkan.aydogan@siriuselektronik.com.tr)
 * @brief 
 * @version 0.1
 * @date 2022-10-04
 * 
 * @copyright Copyright (c) 2022
 * 
 */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef SWL_APPLICATION_H
#define SWL_APPLICATION_H

#include "main.h"
#include "swl_Application.h"
#include "hwl_Application.h"

void swl_ApplicationTask(const void * argv);
void swl_InitApplication(void);
uint8_t swl_IsApplicationOngoing(void);

#endif
