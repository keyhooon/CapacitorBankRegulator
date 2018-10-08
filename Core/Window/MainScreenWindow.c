/*
 * MainScreenWindow.c
 *
 *  Created on: Oct 2, 2018
 *      Author: HP
 */

/*********************************************************************
 *
 *       Includes
 *
 **********************************************************************
 */
#include "DIALOG.h"
#include "MainWindow.h"





/*********************************************************************
 *
 *       _cbView
 *
 * Purpose:
 *   Callback function of view window.
 */

static void _cbView(WM_MESSAGE * pMsg) {
	int xSize, ySize, i, Id, NCode;
	WM_MOTION_INFO * pInfo;
	WM_HWIN hWin, hButton;
	static int IsPressed;

	hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_CREATE:

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
//		xPos = xSize;
		GUI_SetColor(GUI_GRAY_D0);
		GUI_FillRect(1, 1, xSize - 2, ySize - 2);
		//
		// Draw logo, battery and clock
		//
//		xPos = xSize;
		GUI_SetBkColor(GUI_GRAY_D0);
		GUI_SetColor(GUI_BLACK);
		GUI_SetFont(&GUI_Font32_ASCII);
		GUI_DispStringAt("MAIN", 180, 100);
		GUI_SetFont(&GUI_Font20_ASCII);
		GUI_DispStringAt("kW", 550, 160);
		GUI_DispStringAt("kvarL", 550, 220);
		GUI_DispStringAt("V", 550, 340);
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

void MainScreenShow(void) {
	int xSize, ySize;
	WM_HWIN hWin;  // window
	//
	// Create windows
	//
//	hWin = WM_CreateWindowAsChild(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT,
//			hWinViewport,
//	WM_CF_SHOW, _cbView, 0);
}
