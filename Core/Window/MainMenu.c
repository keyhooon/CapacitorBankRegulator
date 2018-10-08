/*********************************************************************
 *                SEGGER Microcontroller GmbH & Co. KG                *
 *        Solutions for real time microcontroller applications        *
 **********************************************************************
 *                                                                    *
 *        (c) 1996 - 2017  SEGGER Microcontroller GmbH & Co. KG       *
 *                                                                    *
 *        Internet: www.segger.com    Support:  support@segger.com    *
 *                                                                    *
 **********************************************************************

 ** emWin V5.46 - Graphical user interface for embedded applications **
 emWin is protected by international copyright laws.   Knowledge of the
 source code may not be used to write a similar product.  This file may
 only  be used  in accordance  with  a license  and should  not be  re-
 distributed in any way. We appreciate your understanding and fairness.
 ----------------------------------------------------------------------
 File        : MOTION_SmartPhoneMenu.c
 Purpose     : Shows how to create a radial menu with motion support
 Requirements: WindowManager - (x)
 MemoryDevices - (x)
 AntiAliasing  - (x)
 VNC-Server    - ( )
 PNG-Library   - ( )
 TrueTypeFonts - ( )
 ----------------------------------------------------------------------
 */
//
// Recommended memory to run the sample with adequate performance
//


/*********************************************************************
 *
 *       Includes
 *
 **********************************************************************
 */
#include "DIALOG.h"

/*********************************************************************
 *
 *       Static (const) data
 *
 **********************************************************************
 */
extern GUI_CONST_STORAGE GUI_BITMAP bmSpeedometer_32;
extern GUI_CONST_STORAGE GUI_BITMAP bmLight_Blob_32;
extern GUI_CONST_STORAGE GUI_BITMAP bmSetup_simple_32;
extern GUI_CONST_STORAGE GUI_BITMAP bmcapacitor_simple_32;
extern GUI_CONST_STORAGE GUI_BITMAP bmHistory_32;
extern GUI_CONST_STORAGE GUI_BITMAP bmEthernet_simple_32;
extern GUI_CONST_STORAGE GUI_BITMAP bmSetting_simple_32;

extern GUI_CONST_STORAGE GUI_BITMAP bmArrowRigth_15x24;
extern GUI_CONST_STORAGE GUI_BITMAP bmLogo_40x20;
extern GUI_CONST_STORAGE GUI_BITMAP bmClock_16x16_black;
extern GUI_CONST_STORAGE GUI_BITMAP _bmBatteryEmpty_27x14;

extern GUI_CONST_STORAGE GUI_BITMAP * _apbmCharge[];






extern void MainScreenShow(void);


/*********************************************************************
 *
 *       _aMenu
 */
const struct MENU_ITEM {
	GUI_COLOR Color;
	const GUI_BITMAP * pBm;
	const char * pText;
} _aMenu[] = { { GUI_DARKGREEN, &bmSpeedometer_32, "P.Factor" }, {
GUI_DARKGREEN,
		&bmLight_Blob_32, "States" }, { GUI_BROWN, &bmcapacitor_simple_32,
		"Capacitors" }, { GUI_BROWN, &bmSetup_simple_32, "Setup" }, {
GUI_DARKYELLOW, &bmHistory_32, "History" }, { GUI_DARKYELLOW,
		&bmEthernet_simple_32, "Comm" }, { GUI_GRAY, &bmSetting_simple_32,
		"Settings" } };

WM_HWIN hWinViewport; // Viewport window


/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */
static void _cbHeading(WM_MESSAGE * pMsg);
static void _cbMenu(WM_MESSAGE * pMsg);
static void _cbView(WM_MESSAGE * pMsg);
static void _cbSelected(WM_MESSAGE * pMsg);
static int _ButtonSkin(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);
static void _CreateSelected(int Index, WM_HWIN hWin);
static void _cbDummy(WM_MESSAGE * pMsg);

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
		GUI_SetColor(GUI_GRAY_E7);
		GUI_FillRect(0, 0, xSize - 1, 57);
		GUI_SetColor(GUI_GRAY_AA);
		GUI_FillRect(0, 58, xSize - 1, 59);
		pBm = &_bmBatteryEmpty_27x14;
		xPos -= pBm->XSize + 3;
		GUI_DrawBitmap(pBm, xPos, 3);
		pBm = _apbmCharge[Index];
		GUI_DrawBitmap(pBm, xPos, 3);
		pBm = &bmClock_16x16_black;
		xPos -= pBm->XSize + 10;
		GUI_DrawBitmap(pBm, xPos, 2);
		//
		// Draw 'Settings'
		//
		GUI_SetFont(&GUI_Font32B_ASCII);
		GUI_SetColor(GUI_BLACK);
		GUI_SetTextMode(GUI_TM_TRANS);
		GUI_DispStringHCenterAt("Settings", xSize / 2, 3);
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}


/*********************************************************************
 *
 *       _cbMenu
 *
 * Purpose:
 *   Callback function of menu window.
 */

static void _cbMenu(WM_MESSAGE * pMsg) {
	int xSize, i, Id, NCode;
	WM_MOTION_INFO * pInfo;
	WM_HWIN hWin, hButton;
	static int IsPressed;

	hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);      // Id of widget
		NCode = pMsg->Data.v;                 // Notification code
		switch (NCode) {
		case WM_NOTIFICATION_CLICKED:
			IsPressed = 1;
			break;
		case WM_NOTIFICATION_RELEASED:
			if (IsPressed) {
				//
				// React only if window is not moving
				//
				_CreateSelected(Id - GUI_ID_BUTTON0, pMsg->hWin);
				IsPressed = 0;
			}
			break;
		}
		break;
	case WM_MOTION:
		pInfo = (WM_MOTION_INFO *) pMsg->Data.p;
		switch (pInfo->Cmd) {
		case WM_MOTION_MOVE:
			//
			// Button should not react if window is moving
			//
			IsPressed = 0;
			break;
		case WM_MOTION_INIT:
			//
			// Activate snapping
			//
			//pInfo->SnapY = 60;
			break;
		}
		break;
	case WM_CREATE:
		//
		// Create all buttons
		//
		xSize = WM_GetWindowSizeX(hWin);
		for (i = 0; (unsigned) i < GUI_COUNTOF(_aMenu); i++) {
			hButton = BUTTON_CreateUser(0, i * 60, xSize, 60, hWin, WM_CF_SHOW,
					0, GUI_ID_BUTTON0 + i, sizeof(i));
			BUTTON_SetSkin(hButton, _ButtonSkin);
			BUTTON_SetUserData(hButton, &i, sizeof(i));
		}
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

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
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);      // Id of widget
		NCode = pMsg->Data.v;                 // Notification code
		switch (NCode) {
		case WM_NOTIFICATION_CLICKED:
			IsPressed = 1;
			break;
		case WM_NOTIFICATION_RELEASED:
			if (IsPressed) {
				//
				// React only if window is not moving
				//
				_CreateSelected(Id - GUI_ID_BUTTON0, pMsg->hWin);
				IsPressed = 0;
			}
			break;
		}
		break;
	case WM_CREATE:
		//
		// Create all buttons
		//
		xSize = WM_GetWindowSizeX(hWin);

//		for (i = 0; (unsigned) i < GUI_COUNTOF(_aMenu); i++) {
//			hButton = BUTTON_CreateUser(0, i * 60, xSize, 60, hWin, WM_CF_SHOW,
//					0, GUI_ID_BUTTON0 + i, sizeof(i));
//			BUTTON_SetSkin(hButton, _ButtonSkin);
//			BUTTON_SetUserData(hButton, &i, sizeof(i));
//		}
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
		GUI_SetColor(GUI_GRAY_E7);
		GUI_FillRect(1, 1, xSize - 2, ySize - 2);

		GUI_SetFont(&GUI_Font32B_ASCII);
		GUI_SetBkColor(GUI_BLACK);
		for (int i = 1; i <= 14; i++) {
			GUI_SetColor(GUI_GRAY_E7);
			GUI_DispDecAt(i, i * 40 - 30, 10, 2);
			GUI_SetColor(GUI_BLACK);
			GUI_FillRect(i * 40 - 30, 47, i * 40 - 1, 52);
		}


		GUI_SetFont(&GUI_Font20B_1);
		GUI_SetBkColor(GUI_GRAY_E7);
		GUI_SetColor(GUI_BLACK);
		GUI_DispStringAt("%", 7, 60);
		GUI_DispStringAt("I", 40, 60);
		GUI_DispStringAt("TDH", 63, 60);


		GUI_POINT aPoints[] =
				{ { 0, 0 }, { 0, 20 }, { 4, 20 }, { 6, 0 } };
		for (int i = 1; i <= 12; i++) {
			GUI_GotoXY(5, 420 - i * 25 - 40);
			GUI_DispDecSpace(i * 10, 3);
			GUI_FillPolygon(aPoints, GUI_COUNTOF(aPoints), 40,
					420 - i * 25 - 40);
			GUI_FillPolygon(aPoints, GUI_COUNTOF(aPoints), 80,
					420 - i * 25 - 40);
			GUI_FillPolygon(aPoints, GUI_COUNTOF(aPoints), 120,
					420 - i * 25 - 40);
			aPoints[2].x += 2;
			aPoints[3].x += 2;
		}
		GUI_DispStringAt("L1", 40, 380);
		GUI_DispStringAt("L2", 80, 380);
		GUI_DispStringAt("L3", 120, 380);





//		GUI_SetColor(0xb2b2b2);
//		GUI_FillRect(0, 58, xSize - 1, 59);
//		pBm = &_bmBatteryEmpty_27x14;
//		xPos -= pBm->XSize + 3;
//		GUI_DrawBitmap(pBm, xPos, 3);
//		pBm = _apbmCharge[Index];
//		GUI_DrawBitmap(pBm, xPos, 3);
//		pBm = &bmClock_16x16_black;
//		xPos -= pBm->XSize + 10;
//		GUI_DrawBitmap(pBm, xPos, 2);
//		//
//		// Draw 'Settings'
//		//
//		GUI_SetFont(&GUI_Font32B_ASCII);
//		GUI_SetColor(GUI_BLACK);
//		GUI_SetTextMode(GUI_TM_TRANS);
//		GUI_DispStringHCenterAt("Settings", xSize / 2, 3);
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

/*********************************************************************
 *
 *       _cbSelected
 *
 * Purpose:
 *   Callback function of window created in reaction of pressing a button.
 *   Responsible for drawing only.
 */
static void _cbSelected(WM_MESSAGE * pMsg) {
	WM_HWIN hWin;
	int Index, xSize, yPos, ySizeFont;
	const GUI_BITMAP * pBm;

	hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_PAINT:
		WM_GetUserData(hWin, &Index, sizeof(Index));
		xSize = WM_GetXSize(hWin);
		GUI_SetBkColor(_aMenu[Index].Color);
		GUI_Clear();
		GUI_SetFont(&GUI_Font32B_1);
		ySizeFont = GUI_GetFontSizeY();
		GUI_SetColor(GUI_WHITE);
		GUI_SetTextMode(GUI_TM_TRANS);
		GUI_DispStringHCenterAt("You have selected\nthe following button:",
				xSize / 2, 30);
		pBm = _aMenu[Index].pBm;
		yPos = GUI_GetDispPosY() + ySizeFont * 3;
		GUI_DrawBitmap(pBm, (xSize - pBm->XSize) / 2, yPos);
		yPos += pBm->YSize + ySizeFont;
		GUI_DispStringHCenterAt(_aMenu[Index].pText, xSize / 2, yPos);
		break;
	default:
		WM_DefaultProc(pMsg);
	}
}

/*********************************************************************
 *
 *       _ButtonSkin
 *
 * Purpose:
 *   Skinning function of a single button. Responsible for custom drawing only.
 */
static int _ButtonSkin(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
	int Index, xSize, ySize, IsPressed;
	WM_HWIN hWin;
	const GUI_BITMAP * pBm;
	GUI_COLOR Color;

	hWin = pDrawItemInfo->hWin;
	switch (pDrawItemInfo->Cmd) {
	case WIDGET_ITEM_DRAW_BACKGROUND:
		//
		// Get state of button
		//
		IsPressed = BUTTON_IsPressed(pDrawItemInfo->hWin);
		//
		// Get window dimension
		//
		xSize = WM_GetWindowSizeX(hWin);
		ySize = WM_GetWindowSizeY(hWin);
		//
		// Get button index
		//
		BUTTON_GetUserData(hWin, &Index, sizeof(Index));
		//
		// Draw background color depending on state
		//
		if (IsPressed) {
			Color = 0xCCCCCC;
		} else {
			Color = GUI_GRAY_E7;
		}
		GUI_SetBkColor(Color);
		GUI_Clear();
		//
		// Draw antialiased rounded rectangle as background for image
		//
		GUI_SetColor(_aMenu[Index].Color);
		GUI_AA_FillRoundedRect(10, 6, 47 + 10, 47 + 6, 12);
		//
		// Draw compressed alpha bitmap
		//
		GUI_SetColor(GUI_WHITE);
		GUI_DrawBitmap(_aMenu[Index].pBm, 18, 14);
		//
		// Draw button text
		//
		GUI_SetColor(GUI_BLACK);
		GUI_SetFont(&GUI_FontComic24B_1);
		GUI_SetTextAlign(GUI_TA_LEFT | GUI_TA_VCENTER);
		GUI_DispStringAt(_aMenu[Index].pText, 80, 30);
		//
		// Draw small separator line
		//
		GUI_SetColor(GUI_GRAY_3F);
		GUI_DrawHLine(ySize - 1, 80, xSize - 1);
		//
		// Draw arrow at the right
		//
		pBm = &bmArrowRigth_15x24;
		GUI_DrawBitmap(&bmArrowRigth_15x24, xSize - 40,
				(ySize - pBm->YSize) / 2);
		break;
	}
	return 0;
}

/*********************************************************************
 *
 *       _CreateSelected
 *
 * Purpose:
 *   This function is called when a button is pressed. It creates a new
 *   window and shows a small screen animation.
 */
static void _CreateSelected(int Index, WM_HWIN hWin) {
	WM_HWIN hWinBase;     // Window to be shifted out
	WM_HWIN hWinSelected; // New window to become visible behind hWinBase
	int xSize, ySize;

	hWinBase = WM_GetParent(WM_GetParent(hWin));
	xSize = WM_GetXSize(hWinBase);
	ySize = WM_GetYSize(hWinBase);
	hWinSelected = WM_CreateWindow(0, 0, xSize, ySize, WM_CF_SHOW, _cbSelected,
			sizeof(Index));
	//
	// Pass menu index to window
	//
	WM_SetUserData(hWinSelected, &Index, sizeof(Index));
	//
	// Window animation
	//
	GUI_MEMDEV_ShiftOutWindow(hWinBase, 500, GUI_MEMDEV_EDGE_LEFT);
	GUI_Delay(500);
	GUI_MEMDEV_ShiftInWindow(hWinBase, 500, GUI_MEMDEV_EDGE_LEFT);
	//
	// Remove the new window
	//
	WM_DeleteWindow(hWinSelected);
}

/*********************************************************************
 *
 *       _cbDummy
 *
 * Purpose:
 *   Required for base window and viewport window to make sure WM_DefaultProc() is called.
 */
static void _cbDummy(WM_MESSAGE * pMsg) {
	switch (pMsg->MsgId) {
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
void MainWindow(void) {
	int xSize, ySize;
	WM_HWIN hWinHeading;  // Heading window

	WM_HWIN hWinMenu;     // Menu window moveable within viewport window
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

	hWinMenu = WM_CreateWindowAsChild(0, 60, 250, 60 * GUI_COUNTOF(_aMenu),
	WM_HBKWIN, WM_CF_SHOW | WM_CF_MOTION_Y, _cbMenu, 0);
	hWinViewport = WM_CreateWindowAsChild(250, 60, xSize - 250, ySize - 60,
	WM_HBKWIN,
	WM_CF_SHOW, _cbView, 0);
	hWinHeading = WM_CreateWindowAsChild(0, 0, xSize, 60, WM_HBKWIN,
	WM_CF_SHOW, _cbHeading, 0);
	MainScreenShow();
}

/*************************** End of file ****************************/
