/*
 * Gui.c
 *
 *  Created on: Oct 23, 2018
 *      Author: HP
 */

#include <GUI.h>
#include <keypad.h>
#include "Board.h"
#include "WM.h"
#include "cmsis_os.h"
#include "ViewNavigator.h"

#include "Api/3GPP_TS27.h"

osThreadId guiTaskHandle;

#define HEADER_SIZE		20
#define DESKTOP_SIZE	115
#define	TOOLBAR_SIZE	25
#define SEPERATOR_SIZE	2
#define BUTTON_WIDTH	55
#define BUTTON_HEIGHT	20

extern GUI_CONST_STORAGE GUI_BITMAP _bmBatteryEmpty_27x14;
extern GUI_CONST_STORAGE GUI_BITMAP * _apbmCharge[];
extern View_Typedef DesktopView;

WM_HWIN hWinHeading;  // Heading window
WM_HWIN hWin;     // Menu window moveable within viewport window
WM_HWIN hWinToolbar;

extern void ShowSmallDesktopWindow(void);
void GUI_Main(void const * argument);


static void CurrentMenuPageChanged(void);
static void _cbHeading(WM_MESSAGE * pMsg);
static void _cbViewPort(WM_MESSAGE * pMsg);
static void _cbToolbar(WM_MESSAGE * pMsg);


void GuiShell_init() {
	osThreadDef(guiTask, GUI_Main, osPriorityNormal, 0, 1000);
	guiTaskHandle = osThreadCreate(osThread(guiTask), NULL);
}


void GUI_Main(void const * argument) {
	SeedContact();
	SeedMessage();
	/* Init the STemWin GUI Library */
	GUI_Init();
	/* Activate the use of memory device feature */
	WM_SetCreateFlags(WM_CF_MEMDEV | WM_CF_MEMDEV_ON_REDRAW | WM_CF_SHOW);
//	GUI_SelectLayer(0);
//	MainWindow();
	GUI_SelectLayer(1);
	ShowSmallDesktopWindow();


  /* Infinite loop */
	for (;;) {
		osEvent event;
		GUI_Exec();
		event = osSignalWait(1 << BUTTON_KEY1 | 1 << BUTTON_KEY2,
		0);
		if (event.status == osEventSignal)
			if (event.value.signals == (1 << BUTTON_KEY1)) {
				View_Typedef *view = ViewNavigator_GetCurrentView(
						&DefaultViewNavigator);
				if (view->firstButtonCallback)
					view->firstButtonCallback();
			} else if (event.value.signals == (1 << BUTTON_KEY2)) {
				View_Typedef *view = ViewNavigator_GetCurrentView(
						&DefaultViewNavigator);
				if (view->SecondButtonCallback)
					view->SecondButtonCallback();
			}
		osDelay(100);
	}
}


void BSP_PB_EXTI_Callback(Button_TypeDef Button, int state) {
	if (state)
		osSignalSet(guiTaskHandle, 1 << Button);
	BUTTON_SetState(
			WM_GetDialogItem(hWinToolbar,
					(Button == BUTTON_KEY1) ? GUI_ID_BUTTON0 : GUI_ID_BUTTON1),
			!state);
}

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
	static int batteryChargeStatus;
	static int battryLevel;
	static int signalQuality;

	hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_CREATE:
		//
		// Create timer to be used to modify the battery symbol
		//
		WM_CreateTimer(hWin, 0, 0, 0);
		break;
	case WM_TIMER:

//		GSM_Battery_Charge(&batteryChargeStatus, &battryLevel)
//
//		GSM_Signal_Quality_Report(&signalQuality)
		WM_InvalidateWindow(hWin);
		WM_RestartTimer(pMsg->Data.v, 10000);
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
		GUI_SetTextMode(GUI_TEXTMODE_XOR);
		GUI_FillRect(0, 0, xSize - 1, ySize);

		{


			pBm = &_bmBatteryEmpty_27x14;
			xPos -= pBm->XSize + 5;
			GUI_DrawBitmap(pBm, xPos, 3);
			pBm = _apbmCharge[battryLevel / 25];
			GUI_DrawBitmap(pBm, xPos, 3);

			xPos -= 20;
			GUI_GotoXY(xPos, 6);
			GUI_DispChar('%');
			GUI_DispDecMin(battryLevel);
		}
		{
			int Antenna;

			if (signalQuality < 32)
				Antenna = signalQuality / 7;
			else
				Antenna = 0;

			xPos = 5;
			GUI_SetPenSize(1);
			GUI_POINT aPoints[] = { { 0, 0 }, { 4, 0 }, { 4, -3 }, { 0, -1 } };
			for (int i = 0; i <= 3; i++) {
				if (i >= Antenna)
					GUI_SetColor(GUI_GRAY_E7);
				else
					GUI_SetColor(GUI_BLACK);
				GUI_FillPolygon(aPoints, GUI_COUNTOF(aPoints), xPos, 15);

				xPos += 6;
				aPoints[2].y -= 3;
				aPoints[3].y -= 3;
			}
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
		GUI_FillRect(0, 0, xSize - 1, SEPERATOR_SIZE);

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

	if (CurrentView->firstButtonCallback == NULL
			|| CurrentView->firstButtonText == NULL)
		WM_HideWindow(firstButton);
	else {
		WM_ShowWindow(firstButton);
		BUTTON_SetText(firstButton, CurrentView->firstButtonText);
	}
	if (CurrentView->SecondButtonCallback == NULL
			|| CurrentView->SecondButtonText == NULL)
		WM_HideWindow(secondButton);
	else {
		WM_ShowWindow(secondButton);
		BUTTON_SetText(secondButton, CurrentView->SecondButtonText);
	}
}

void ChangeFirstButtonText(char *text) {
	GUI_HWIN firstButton = WM_GetDialogItem(hWinToolbar, GUI_ID_BUTTON0);
	BUTTON_SetText(firstButton, text);
}

void ChangeSecondButtonText(char *text) {
	GUI_HWIN secondButton = WM_GetDialogItem(hWinToolbar, GUI_ID_BUTTON1);
	BUTTON_SetText(secondButton, text);
}



