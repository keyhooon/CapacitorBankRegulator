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


/*********************************************************************
 *
 *       Defines
 *
 **********************************************************************
 */
#define ID_WINDOW_02     (GUI_ID_USER + 0x00)
#define ID_HEADER_0     (GUI_ID_USER + 0x01)
#define ID_BUTTON_0     (GUI_ID_USER + 0x02)
#define ID_BUTTON_1     (GUI_ID_USER + 0x03)

/*********************************************************************
 *
 *       Static (const) data
 *
 **********************************************************************
 */
extern GUI_CONST_STORAGE GUI_BITMAP bmClock_16x16_black;
extern GUI_CONST_STORAGE GUI_BITMAP _bmBatteryEmpty_27x14;

extern GUI_CONST_STORAGE GUI_BITMAP * _apbmCharge[];

/*********************************************************************
 *
 *       _aDialogCreate
 */
static const GUI_WIDGET_CREATE_INFO _aToolbarCreate[] = { {
		BUTTON_CreateIndirect, "SelectButton", ID_BUTTON_0, 3,
		106, 60, 20, 0, 0x0, 0 }, { BUTTON_CreateIndirect, "BackButton",
		ID_BUTTON_1, 98, 106, 60, 20, 0, 0x0, 0 },
// USER START (Optionally insert additional widgets)
// USER END
		};

/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */
static void _cbHeading(WM_MESSAGE * pMsg);
static void _cbDesktop(WM_MESSAGE * pMsg);
static void _cbToolbar(WM_MESSAGE * pMsg);
extern void ShowSmallDesktopWindow(void);



/*********************************************************************
 *
 *       _cbHeading
 *
 * Purpose:
 *   Callback function of heading window containing logo and battery symbol.
 */
static void _cbHeading(WM_MESSAGE * pMsg) {
	int xSize, xPos;
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
		//
		// Draw logo, battery and clock
		//
		xPos = xSize;
		GUI_SetColor(GUI_WHITE);
		GUI_FillRect(0, 0, xSize - 1, 20);
		GUI_SetColor(GUI_GRAY_3F);
		GUI_FillRect(0, 20, xSize - 1, 21);
//		pBm = &bmClock_16x16_black;
//		xPos -= (pBm->XSize + 5);
//		GUI_DrawBitmap(pBm, xPos, 2);
		pBm = &_bmBatteryEmpty_27x14;
		xPos -= pBm->XSize + 5;
		GUI_DrawBitmap(pBm, xPos, 3);
		pBm = _apbmCharge[Index];
		GUI_DrawBitmap(pBm, xPos, 3);

		xPos -= 30;
		GUI_SetPenSize(1);
		GUI_POINT aPoints[] = { { 0, 0 }, { 4, 0 }, { 4, -3 }, { 0, -1 } };
		for (int i = 1; i <= 4; i++) {
			if (i > Antenna)
				GUI_SetColor(GUI_GRAY_D0);
			else
				GUI_SetColor(GUI_BLACK);
			GUI_FillPolygon(aPoints, GUI_COUNTOF(aPoints), xPos, 15);

			xPos += 6;
			aPoints[2].y -= 3;
			aPoints[3].y -= 3;
		}

		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

/*********************************************************************
 *
 *       _cbDesktop
 *
 * Purpose:
 *   Callback function of desktop window containing time and background icon.
 */
static void _cbDesktop(WM_MESSAGE * pMsg) {
	int xSize, ySize;
	WM_HWIN hWin;

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
		GUI_SetColor(GUI_WHITE);
		GUI_FillRect(0, 0, xSize - 1, ySize + 40);
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

/*********************************************************************
 *
 *       _cbToolbar
 *
 * Purpose:
 *   Callback function of toolbar window containing buttons.
 */
static void _cbToolbar(WM_MESSAGE * pMsg) {
	int xSize, ySize;
	WM_HWIN hWin;
	WM_HWIN hButton[2];
	static int IsPressed;
	hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_CREATE:

		hButton[0] = BUTTON_CreateUser(5, 5, 55, 25, hWin, WM_CF_SHOW, 0,
		GUI_ID_BUTTON0, 0);

		xSize = WM_GetWindowSizeX(hWin);
		hButton[1] = BUTTON_CreateUser(xSize - 5 - 55, 5, 55, 25, hWin,
				WM_CF_SHOW, 0,
		GUI_ID_BUTTON1, 0);
		BUTTON_SetText(hButton[1], "OK");
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
		GUI_FillRect(0, 0, xSize, 2);

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
void ShowSmallDesktopWindow(void) {
	int xSize, ySize;
	int yPos;
	WM_HWIN hWinHeading;  // Heading window
	WM_HWIN hWin;     // Menu window moveable within viewport window
	//
	// Get display dimension
	//
	xSize = LCD_GetXSize();
	ySize = LCD_GetYSize();
	yPos = 0;
	//
	// Limit desktop window to display size
	//
	WM_SetSize(WM_HBKWIN, xSize, ySize);
	//
	// Create heading windows
	//
	hWinHeading = WM_CreateWindowAsChild(0, yPos, xSize, 22, WM_HBKWIN,
	WM_CF_SHOW, _cbHeading, 0);
	yPos += 22;
	//
	// Create desktop windows
	//
	hWin = WM_CreateWindowAsChild(0, yPos, xSize, 100, WM_HBKWIN,
	WM_CF_SHOW, _cbDesktop, sizeof(void *) * 2);
	yPos += 100;

	//
	// Create toolbar windows
	//
	hWin = WM_CreateWindowAsChild(0, yPos, xSize, 40, WM_HBKWIN,
	WM_CF_SHOW, _cbToolbar, sizeof(void *) * 2);
	yPos += 100;






}
