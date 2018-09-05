/*
 * StartupWindow.c
 *
 *  Created on: Sep 5, 2018
 *      Author: HP
 */

#include "DIALOG.h"
/* Private function prototypes -----------------------------------------------*/
static void BackGroundCallback(WM_MESSAGE * pMsg);
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Backbground callbacsk
 * @param  pMsg: pointer to data structure of type WM_MESSAGE
 * @retval None
 */

static void BackGroundCallback(WM_MESSAGE * pMsg) {
	switch (pMsg->MsgId) {
	case WM_PAINT:

		GUI_SetBkColor(GUI_WHITE);
		GUI_Clear();
		break;

	default:
		WM_DefaultProc(pMsg);
	}
}

/**
 * @brief  Startup
 * @param  None
 * @retval None
 */
void CreateStartUpWindow(void) {
	WM_SetCallback(WM_GetDesktopWindowEx(0), BackGroundCallback);

	GUI_SetFont(&GUI_Font13_1);
	GUI_SetColor(GUI_LIGHTBLUE);
	GUI_SetBkColor(GUI_WHITE);
	GUI_Delay(20);
	GUI_DispStringAt("l", 220, 330);
	GUI_Delay(20);
	GUI_DispStringAt("i", 230, 330);
	GUI_Delay(20);
	GUI_DispStringAt("f", 240, 330);
	GUI_Delay(20);
	GUI_DispStringAt("e", 250, 330);
	GUI_Delay(20);
	GUI_DispStringAt(".", 265, 330);
	GUI_Delay(20);
	GUI_SetColor(GUI_DARKBLUE);
	GUI_SetFont(&GUI_Font16_1);
	GUI_DispStringAt("a", 280, 330);
	GUI_Delay(20);
	GUI_DispStringAt("u", 297, 330);
	GUI_Delay(20);
	GUI_DispStringAt("g", 312, 330);
	GUI_Delay(20);
	GUI_DispStringAt("m", 329, 330);
	GUI_Delay(20);
	GUI_DispStringAt("e", 354, 330);
	GUI_Delay(20);
	GUI_DispStringAt("n", 369, 330);
	GUI_Delay(20);
	GUI_DispStringAt("t", 384, 330);
	GUI_Delay(20);
	GUI_DispStringAt("e", 392, 330);
	GUI_Delay(20);
	GUI_DispStringAt("d", 407, 330);

	GUI_Delay(1000);
}
