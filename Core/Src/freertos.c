/**
  ******************************************************************************
  * File Name          : freertos.c
  * Description        : Code for freertos applications
  ******************************************************************************
  * This notice applies to any and all portions of this file
  * that are not between comment pairs USER CODE BEGIN and
  * USER CODE END. Other portions of this file, whether
  * inserted by the user or by software development tools
  * are owned by their respective copyright owners.
  *
  * Copyright (c) 2018 STMicroelectronics International N.V.
  * All rights reserved.
  *
  * Redistribution and use in source and binary forms, with or without
  * modification, are permitted, provided that the following conditions are met:
  *
  * 1. Redistribution of source code must retain the above copyright notice,
  *    this list of conditions and the following disclaimer.
  * 2. Redistributions in binary form must reproduce the above copyright notice,
  *    this list of conditions and the following disclaimer in the documentation
  *    and/or other materials provided with the distribution.
  * 3. Neither the name of STMicroelectronics nor the names of other
  *    contributors to this software may be used to endorse or promote products
  *    derived from this software without specific written permission.
  * 4. This software, including modifications and/or derivative works of this
  *    software, must execute solely and exclusively on microcontroller or
  *    microprocessor devices manufactured by or for STMicroelectronics.
  * 5. Redistribution and use of this software other than as permitted under
  *    this license is void and will automatically terminate your rights under
  *    this license.
  *
  * THIS SOFTWARE IS PROVIDED BY STMICROELECTRONICS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS, IMPLIED OR STATUTORY WARRANTIES, INCLUDING, BUT NOT
  * LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
  * PARTICULAR PURPOSE AND NON-INFRINGEMENT OF THIRD PARTY INTELLECTUAL PROPERTY
  * RIGHTS ARE DISCLAIMED TO THE FULLEST EXTENT PERMITTED BY LAW. IN NO EVENT
  * SHALL STMICROELECTRONICS OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT,
  * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
  * LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA,
  * OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF
  * LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING
  * NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE,
  * EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include <GUI.h>
#include <GuiShell.h>
#include "FreeRTOS.h"
#include "task.h"
#include "cmsis_os.h"

/* USER CODE BEGIN Includes */
#include "Board.h"
#include "WM.h"
#include "Board_keypad.h"
/* USER CODE END Includes */

/* Variables -----------------------------------------------------------------*/
osThreadId keyboardTaskHandle;
osThreadId guiTaskHandle;
osThreadId CalculateTaskHandle;
osThreadId EventTaskHandle;
osTimerId StatusTimerHandle;
osSemaphoreId CalculateNeededSemHandle;

/* USER CODE BEGIN Variables */
uint32_t ledTim[4];
uint32_t ledTimStart[4] = { 1, 2, 3, 4 };
/* USER CODE END Variables */

/* Function prototypes -------------------------------------------------------*/

void CalculationProc(void const * argument);
void StatusShowCallback(void const * argument);

extern void ToolbarFirstButtonProc();
extern void ToolbarSecondButtonProc();

void MX_FREERTOS_Init(void); /* (MISRA C 2004 rule 8.1) */

/* USER CODE BEGIN FunctionPrototypes */

/* USER CODE END FunctionPrototypes */

/* Hook prototypes */
void vApplicationIdleHook(void);
void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName);
void vApplicationMallocFailedHook(void);

/* USER CODE BEGIN 2 */
__weak void vApplicationIdleHook(void) {
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	 to 1 in FreeRTOSConfig.h. It will be called on each iteration of the idle
	 task. It is essential that code added to this hook function never attempts
	 to block in any way (for example, call xQueueReceive() with a block time
	 specified, or call vTaskDelay()). If the application makes use of the
	 vTaskDelete() API function (as this demo application does) then it is also
	 important that vApplicationIdleHook() is permitted to return to its calling
	 function, because it is the responsibility of the idle task to clean up
	 memory allocated by the kernel to any task that has since been deleted. */
}
/* USER CODE END 2 */

/* USER CODE BEGIN 4 */
__weak void vApplicationStackOverflowHook(xTaskHandle xTask, signed char *pcTaskName)
{
	while(1)
	{

	}
   /* Run time stack overflow checking is performed if
   configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2. This hook function is
   called if a stack overflow is detected. */
}
/* USER CODE END 4 */

/* USER CODE BEGIN 5 */
__weak void vApplicationMallocFailedHook(void)
{
	while(1)
	{

	}
   /* vApplicationMallocFailedHook() will only be called if
   configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h. It is a hook
   function that will get called if a call to pvPortMalloc() fails.
   pvPortMalloc() is called internally by the kernel whenever a task, queue,
   timer or semaphore is created. It is also called by various parts of the
   demo application. If heap_1.c or heap_2.c are used, then the size of the
   heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
   FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
   to query the size of free heap space that remains (although it does not
   provide information on how the remaining heap might be fragmented). */
}
/* USER CODE END 5 */

/* Init FreeRTOS */

void MX_FREERTOS_Init(void) {
  /* USER CODE BEGIN Init */
  /* USER CODE END Init */

  /* USER CODE BEGIN RTOS_MUTEX */
  /* add mutexes, ... */
  /* USER CODE END RTOS_MUTEX */

  /* Create the semaphores(s) */
  /* definition and creation of CalculateNeededSem */
	osSemaphoreDef(CalculateNeededSem);
	CalculateNeededSemHandle = osSemaphoreCreate(
			osSemaphore(CalculateNeededSem), 1);

  /* USER CODE BEGIN RTOS_SEMAPHORES */
  /* add semaphores, ... */
  /* USER CODE END RTOS_SEMAPHORES */

  /* Create the timer(s) */
  /* definition and creation of StatusTimer */
	osTimerDef(StatusTimer, StatusShowCallback);
	StatusTimerHandle = osTimerCreate(osTimer(StatusTimer), osTimerPeriodic,
			NULL);

	/* USER CODE BEGIN RTOS_TIMERS */
	/* start timers, add new ones, ... */
	osTimerStart(StatusTimerHandle, 100);
	/* USER CODE END RTOS_TIMERS */

	/* Create the thread(s) */
	/* definition and creation of guiTask */
	osThreadDef(guiTask, GuiProc, osPriorityNormal, 0, 1500);
	guiTaskHandle = osThreadCreate(osThread(guiTask), NULL);

	/* definition and creation of defaultTask */
	osThreadDef(keyboardTask, KeyboardProc, osPriorityNormal, 0, 256);
	keyboardTaskHandle = osThreadCreate(osThread(keyboardTask), NULL);

	/* definition and creation of CalculateTask */
	osThreadDef(CalculateTask, CalculationProc, osPriorityIdle, 0, 128);
	CalculateTaskHandle = osThreadCreate(osThread(CalculateTask), NULL);

  /* USER CODE BEGIN RTOS_THREADS */
  /* add threads, ... */
  /* USER CODE END RTOS_THREADS */

  /* USER CODE BEGIN RTOS_QUEUES */
  /* add queues, ... */
  /* USER CODE END RTOS_QUEUES */
}

/* DefaultProc function */


/* GuiProc function */

/* CalculationProc function */
void CalculationProc(void const * argument)
{
  /* USER CODE BEGIN CalculationProc */
  /* Infinite loop */
  for(;;)
  {
		osDelay(1000);
  }
  /* USER CODE END CalculationProc */
}


/* StatusShowCallback function */
void StatusShowCallback(void const * argument)
{
  /* USER CODE BEGIN StatusShowCallback */
	if (ledTim[0]-- == 0)
	{
		ledTim[0] = ledTimStart[0];
		BSP_LED_Toggle(LED1);
	}
	if (ledTim[1]-- == 0)
	{
		ledTim[1] = ledTimStart[1];
		BSP_LED_Toggle(LED2);
	}
	if (ledTim[2]-- == 0)
	{
		ledTim[2] = ledTimStart[2];
		BSP_LED_Toggle(LED3);
	}
	if (ledTim[3]-- == 0)
	{
		ledTim[3] = ledTimStart[3];
		BSP_LED_Toggle(LED4);
	}

  /* USER CODE END StatusShowCallback */
}

/* USER CODE BEGIN Application */

/* USER CODE END Application */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
