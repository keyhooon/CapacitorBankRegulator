/*
 * DesktopWindow.c
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
#include "ViewContainer/ViewNavigator.h"
#include "Board.h"

#include "cmsis_os.h"

/*********************************************************************
 *
 *       Defines
 *
 **********************************************************************
 */




/*********************************************************************
 *
 *       Static (const) data
 *
 **********************************************************************
 */

extern GUI_CONST_STORAGE GUI_BITMAP bmsepah;







static void _cbDesktop(WM_MESSAGE * pMsg);

static GUI_HWIN show(void);
static uint8_t hide(GUI_HWIN hWin);
static void MenuCallback(void);



extern View_Typedef MenuView;
const View_Typedef DesktopView = { DESKTOP_VIEW_ID, (const char*) "Desktop",
		(const char*) "Desk", (void*) 0, show, hide, NULL, (const char*) "Menu",
		NULL, MenuCallback, NULL, NULL };


/*********************************************************************
 *
 *       _cbDesktop
 *
 * Purpose:
 *   Callback function of desktop window containing time and background icon.
 */
static void _cbDesktop(WM_MESSAGE * pMsg) {
	int xSize, ySize, xPos;
	WM_HWIN hWin;

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
		GUI_SetColor(GUI_WHITE);
		GUI_FillRect(0, 0, xSize - 1, ySize);
		GUI_SetColor(GUI_BLACK);
		GUI_FillRect(0, 0, xSize - 1,
		2);
		GUI_DrawBitmap(&bmsepah, 0, 0);
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}


static GUI_HWIN show(void) {
	int xSize, ySize;
	xSize = LCD_GetXSize();
	ySize = LCD_GetYSize();
	WM_HWIN hWin = WM_CreateWindowAsChild(0, 0, xSize, ySize, 0,
	WM_CF_SHOW, _cbDesktop, 0);
	return hWin;
}
static uint8_t hide(GUI_HWIN hWin) {
	return 0;
}
static void MenuCallback(void) {
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &MenuView, NULL);
}

