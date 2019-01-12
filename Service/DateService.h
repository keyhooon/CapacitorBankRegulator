/*
 * DateService.h
 *
 *  Created on: Jan 9, 2019
 *      Author: HP
 */

#ifndef DATESERVICE_H_
#define DATESERVICE_H_

#include "stm32f1xx_hal.h"
#include "time.h"

extern RTC_HandleTypeDef RtcHandle;
#define DATE_SERVICE_ISVALID (HAL_RTCEx_BKUPRead(&RtcHandle, RTC_BKP_DR1) == 0x32F2)

void DateService_Init();
void DateService_Config(struct tm _tm);

#endif /* DATESERVICE_H_ */
