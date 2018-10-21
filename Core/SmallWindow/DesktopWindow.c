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
#include "ViewNavigator.h"
#include "Board.h"

#include "cmsis_os.h"

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
#define ID_WINDOW_03     (GUI_ID_USER + 0x20)
#define ID_IMAGE_0     (GUI_ID_IMAGE0)

#define HEADER_SIZE		20
#define DESKTOP_SIZE	115
#define	TOOLBAR_SIZE	25
#define SEPERATOR_SIZE	2
#define BUTTON_WIDTH	55
#define BUTTON_HEIGHT	20



/*********************************************************************
 *
 *       Static (const) data
 *
 **********************************************************************
 */
extern GUI_CONST_STORAGE GUI_BITMAP bmClock_16x16_black;
extern GUI_CONST_STORAGE GUI_BITMAP _bmBatteryEmpty_27x14;

extern GUI_CONST_STORAGE GUI_BITMAP * _apbmCharge[];
extern GUI_CONST_STORAGE GUI_BITMAP bmsepah;


WM_HWIN hWinHeading;  // Heading window
WM_HWIN hWin;     // Menu window moveable within viewport window
WM_HWIN hWinToolbar;

extern osThreadId EventTaskHandle;

/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */
void ToolbarFirstButtonProc();
void ToolbarSecondButtonProc();

static void CurrentMenuPageChanged(void);
static void _cbHeading(WM_MESSAGE * pMsg);
static void _cbViewPort(WM_MESSAGE * pMsg);
static void _cbDesktop(WM_MESSAGE * pMsg);
static void _cbToolbar(WM_MESSAGE * pMsg);
static GUI_HWIN show(void);
static uint8_t hide(GUI_HWIN hWin);
static void MenuCallback(void);
extern void ShowSmallDesktopWindow(void);


extern View_Typedef MenuView;
View_Typedef DesktopView = { DESKTOP_VIEW_ID, (const char*) "Desktop",
		(const char*) "Desk", (void*) 0, show, hide, NULL, (const char*) "Menu",
		NULL, MenuCallback, NULL, NULL };

/*********************************************************************
 *
 *       _cbHeading
 *
 * Purpose:
 *   Callback function of heading window containing logo and battery symbol.
 */
static void _cbHeading(WM_MESSAGE * pMsg) {
	int xSize, xPos, ySize;
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
				GUI_SetColor(GUI_GRAY_E7);
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
 *       _cbViewPort
 *
 * Purpose:
 *   Callback function of desktop window containing time and background icon.
 */
static void _cbViewPort(WM_MESSAGE * pMsg) {
	int xSize, ySize;
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
		SEPERATOR_SIZE);

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
		SEPERATOR_SIZE);
		GUI_DrawBitmap(&bmsepah, 0, 0);
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
		xSize = WM_GetWindowSizeX(hWin);

		hButton[0] = BUTTON_CreateUser(5, 4, BUTTON_WIDTH, BUTTON_HEIGHT, hWin,
				WM_CF_SHOW, 0,
		GUI_ID_BUTTON0, 0);
		BUTTON_SetText(hButton[0], "Back");


		hButton[1] = BUTTON_CreateUser(xSize - 5 - BUTTON_WIDTH, 4,
				BUTTON_WIDTH, BUTTON_HEIGHT, hWin,
				WM_CF_SHOW, 0,
		GUI_ID_BUTTON1, 0);
		BUTTON_SetText(hButton[1], "Menu");
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
		GUI_FillRect(0, 0, xSize, SEPERATOR_SIZE);

		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

void BSP_PB_EXTI_Callback(Button_TypeDef Button, int state) {
	View_Typedef *view = ViewNavigator_GetCurrentView(&DefaultViewNavigator);


	if (Button == BUTTON_KEY1 && view->firstButtonCallback != NULL)
	{
		GUI_HWIN firstButton = WM_GetDialogItem(hWinToolbar, GUI_ID_BUTTON0);
		if (state == GPIO_PIN_SET)
			osSignalSet(EventTaskHandle, 1 << BUTTON_KEY1);
		BUTTON_SetState(firstButton, !state);
	}
	if (Button == BUTTON_KEY2 && view->SecondButtonCallback != NULL)
	{
		GUI_HWIN secondButton = WM_GetDialogItem(hWinToolbar, GUI_ID_BUTTON1);
		if (state == GPIO_PIN_SET)
			osSignalSet(EventTaskHandle, 1 << BUTTON_KEY2);
		BUTTON_SetState(secondButton, !state);
	}
}
void ToolbarFirstButtonProc() {
	View_Typedef *view = ViewNavigator_GetCurrentView(&DefaultViewNavigator);
	view->firstButtonCallback();
}
void ToolbarSecondButtonProc() {
	View_Typedef *view = ViewNavigator_GetCurrentView(&DefaultViewNavigator);
	view->SecondButtonCallback();
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
	hWinHeading = WM_CreateWindowAsChild(0, yPos, xSize, HEADER_SIZE, WM_HBKWIN,
	WM_CF_SHOW, _cbHeading, 0);
	yPos += HEADER_SIZE;
	//
	// Create desktop windows
	//
	hWin = WM_CreateWindowAsChild(0, yPos, xSize, DESKTOP_SIZE, WM_HBKWIN,
	WM_CF_SHOW, _cbViewPort, 0);
	yPos += DESKTOP_SIZE;

	//
	// Create toolbar windows
	//
	hWinToolbar = WM_CreateWindowAsChild(0, yPos, xSize, TOOLBAR_SIZE,
	WM_HBKWIN,
	WM_CF_SHOW, _cbToolbar, 0);

	ViewNavigator_Init(&DefaultViewNavigator, hWin);
	DefaultViewNavigator.currentViewChanged = CurrentMenuPageChanged;
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &DesktopView);
}

static void CurrentMenuPageChanged(void) {
	GUI_HWIN firstButton = WM_GetDialogItem(hWinToolbar, GUI_ID_BUTTON0);
	GUI_HWIN secondButton = WM_GetDialogItem(hWinToolbar, GUI_ID_BUTTON1);
	View_Typedef * CurrentView = ViewNavigator_GetCurrentView(
			&DefaultViewNavigator);

	if (CurrentView->firstButtonCallback == NULL)
		WM_HideWindow(firstButton);
	else
	{
		WM_ShowWindow(firstButton);
		BUTTON_SetText(firstButton, CurrentView->firstButtonText);
	}
	if (CurrentView->SecondButtonCallback == NULL)
		WM_HideWindow(secondButton);
	else
	{
		WM_ShowWindow(secondButton);
		BUTTON_SetText(secondButton, CurrentView->SecondButtonText);
	}

}


static GUI_HWIN show(void) {
	int xSize, ySize;
	xSize = LCD_GetXSize();
	ySize = LCD_GetYSize();
	hWin = WM_CreateWindowAsChild(0, 0, xSize, ySize, WM_HBKWIN,
	WM_CF_SHOW, _cbDesktop, 0);
	return hWin;
}
static uint8_t hide(GUI_HWIN hWin) {

}
static void MenuCallback(void) {
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &MenuView);
}

