/*
 * DataService.c
 *
 *  Created on: Jan 9, 2019
 *      Author: HP
 */


#include "DateService.h"


static void RTC_CalendarGet(RTC_DateTypeDef *sdatestructureget,
		RTC_TimeTypeDef *stimestructureget);

RTC_HandleTypeDef RtcHandle;

void DateService_Init() {

	RtcHandle.Instance = RTC;
	RtcHandle.Init.AsynchPrediv = RTC_AUTO_1_SECOND;

	HAL_RTC_Init(&RtcHandle);
}



/**
 * @brief  Configure the current time and date.
 * @param  None
 * @retval None
 */
void DateService_Config(struct tm _tm) {
	RTC_DateTypeDef sdatestructure;
	RTC_TimeTypeDef stimestructure;

	/*##-1- Configure the Date #################################################*/
	/* Set Date: Tuesday February 18th 2014 */
	sdatestructure.Year = _tm.tm_year - 100;
	sdatestructure.Month = _tm.tm_mon + 1;
	sdatestructure.Date = _tm.tm_mday;

	if (HAL_RTC_SetDate(&RtcHandle, &sdatestructure, RTC_FORMAT_BIN)
			!= HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	/*##-2- Configure the Time #################################################*/
	/* Set Time: 02:00:00 */
	stimestructure.Hours = _tm.tm_hour;
	stimestructure.Minutes = _tm.tm_min;
	stimestructure.Seconds = _tm.tm_sec;

	if (HAL_RTC_SetTime(&RtcHandle, &stimestructure, RTC_FORMAT_BIN)
			!= HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	/*##-3- Writes a data in a RTC Backup data Register1 #######################*/
	HAL_RTCEx_BKUPWrite(&RtcHandle, RTC_BKP_DR1, 0x32F2);
}

/**
 * @brief  Display the current time and date.
 * @param  showtime : pointer to buffer
 * @param  showdate : pointer to buffer
 * @retval None
 */
void DateService_Get(struct tm * _tm) {
	RTC_DateTypeDef *sdatestructureget;
	RTC_TimeTypeDef *stimestructureget;
	/* Get the RTC current Time */
	HAL_RTC_GetTime(&RtcHandle, stimestructureget, RTC_FORMAT_BIN);
	/* Get the RTC current Date */
	HAL_RTC_GetDate(&RtcHandle, sdatestructureget, RTC_FORMAT_BIN);
	_tm.tm_year = sdatestructure.Year + 30;
	sdatestructure.Month = _tm.tm_mon + 1;
	sdatestructure.Date = _tm.tm_mday;

	if (HAL_RTC_SetDate(&RtcHandle, &sdatestructure, RTC_FORMAT_BIN)
			!= HAL_OK) {
		/* Initialization Error */
		Error_Handler();
	}

	/*##-2- Configure the Time #################################################*/
	/* Set Time: 02:00:00 */
	stimestructure.Hours = _tm.tm_hour;
	stimestructure.Minutes = _tm.tm_min;
	stimestructure.Seconds = _tm.tm_sec;
}
