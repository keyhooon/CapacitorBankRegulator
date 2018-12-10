/*
 * EditView.c
 *
 *  Created on: Oct 7, 2018
 *      Author: HP
 */
/*********************************************************************
 *
 *       Includes
 *
 **********************************************************************
 */
#include "DIALOG.h"
#include "EditView.h"

/*********************************************************************
 *
 *       Static (const) data
 *
 **********************************************************************
 */

#define MY_WIDGET_ID_0 (GUI_ID_USER + 0)
#define MY_WIDGET_ID_1 (GUI_ID_USER + 1)
#define MY_WIDGET_ID_2 (GUI_ID_USER + 2)
#define MY_WIDGET_ID_3 (GUI_ID_USER + 3)


extern GUI_CONST_STORAGE GUI_BITMAP bmClock_16x16_black;
extern GUI_CONST_STORAGE GUI_BITMAP _bmBatteryEmpty_27x14;

extern GUI_CONST_STORAGE GUI_BITMAP * _apbmCharge[];

/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */
static void _cbView(WM_MESSAGE * pMsg);

extern void ShowEditView(EditViewParam_Typedef Param);
/*********************************************************************
 *
 *       _cbHeading
 *
 * Purpose:
 *   Callback function of heading window containing logo and battery symbol.
 */
static void _cbView(WM_MESSAGE * pMsg) {
	int xSize, ySize, xPos, yPos;
	const GUI_BITMAP * pBm;
	WM_HWIN hWin;
	static int Index;
	static int Antenna;

	hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_CREATE:
		//
		// Create timer to be used to modify the battery symbol
		//
		WM_CreateTimer(hWin, 0, 1000, 0);

		break;
	case WM_TIMER:
		//
		// Modify battery symbol on timer message
		//
		Index++;
		if (Index == 5) {
			Index = 0;
		}
		Antenna++;
		if (Antenna == 5) {
			Antenna = 0;
		}
		WM_InvalidateWindow(hWin);
		WM_RestartTimer(pMsg->Data.v, 0);
		break;
	case WM_PAINT:
		//
		// Get window dimension
		//
		xSize = WM_GetWindowSizeX(hWin);
		ySize = WM_GetWindowSizeY(hWin);
		//
		// Draw logo, battery and clock
		//
		xPos = xSize;
		GUI_SetColor(GUI_WHITE);
		GUI_FillRect(0, 0, xSize - 1, ySize);

		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

/*********************************************************************
 *
 *       Public code
 *
 **********************************************************************
 */
/*********************************************************************
 *
 *       MainTask
 *
 * Purpose:
 *
 */
void ShowEditView(View_Typedef *view) {
	int xSize, ySize;


	WM_HWIN hWin;     // Menu window moveable within viewport window
	EditViewParam_Typedef* param = (EditViewParam_Typedef*) (view->param);
	EditViewState_TypeDef* state =
			(EditViewState_TypeDef*) (view->state->States);
	//
	// Get display dimension
	//
	xSize = LCD_GetXSize();
	ySize = LCD_GetYSize();
	//
	// Limit desktop window to display size
	//
	WM_SetSize(WM_HBKWIN, xSize, ySize);
	//
	// Create windows
	//
	hWin = WM_CreateWindowAsChild(0, 22, xSize, 168, WM_HBKWIN,
	WM_CF_SHOW, _cbView, sizeof(void *) * 2);
	TEXT_CreateEx(25, 5, 178, 30, hWin, WM_CF_SHOW, TEXT_CF_VCENTER,
	MY_WIDGET_ID_0, param->infoText);
	EDIT_CreateEx(25, 35, 78, 30, hWin, WM_CF_SHOW, TEXT_CF_VCENTER,
	MY_WIDGET_ID_1, state->value);
}
void HideEditView(WM_HWIN hWin) {

}
