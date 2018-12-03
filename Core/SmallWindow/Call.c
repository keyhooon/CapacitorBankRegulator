/*
 * Call.c
 *
 *  Created on: Dec 2, 2018
 *      Author: keyhooon
 */

#include "ViewNavigator.h"
#include "Api/V25TER.h"
#include "App/Call.h"
#include "Contact.h"
#include "WM.h"
#include <GUI.h>

typedef struct {
	char Number[12];
	Contact_Typedef * contact;
	int time;
} Call_TypeDef;


static void CallCancelCallback(void);
static GUI_HWIN CallViewShow();
static uint32_t CallViewHide(GUI_HWIN hwin);


extern GUI_CONST_STORAGE GUI_BITMAP bmcalling0;
extern GUI_CONST_STORAGE GUI_BITMAP * _abmcalling[];

const View_Typedef CallView = {
		CONTACT_CALL_VIEW_ID, "Contact Call", "Call",
		(void *) NULL, CallViewShow, CallViewHide,
		NULL, (const char*) "Cancel", NULL, CallCancelCallback, NULL, 0 };

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = {
		{
		WINDOW_CreateIndirect, "Window", GUI_ID_USER, 0, 0, 128, 115, 0, 0x0,
				0 }, { TEXT_CreateIndirect, "Text", GUI_ID_TEXT0, 5, 0, 118, 20,
				0, 0x0, 0 }, { TEXT_CreateIndirect, "Text", GUI_ID_TEXT1, 5, 85,
				118, 30, 0, 0x0, 0 }, };

static void _cbCallView(WM_MESSAGE * pMsg) {
	static int time;
	int xSize, xPos;

	WM_HWIN hWin;
	hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:
		//
		// Create timer to be used to modify the battery symbol
		//
		WM_CreateTimer(hWin, 0, 1000, 0);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin, GUI_ID_TEXT1),
				TEXT_CF_HCENTER);
		TEXT_SetTextAlign(WM_GetDialogItem(hWin, GUI_ID_TEXT0),
				TEXT_CF_HCENTER);
		time = 0;
		break;
	case WM_TIMER:
		//
		// Modify battery symbol on timer message
		//
		time++;
		WM_InvalidateWindow(hWin);
		WM_RestartTimer(pMsg->Data.v, 1000);
		break;
	case WM_PAINT:
		//
		// Get window dimension
		//

		xSize = WM_GetWindowSizeX(hWin);
		xPos = (xSize - bmcalling0.XSize) / 2;
		GUI_SetBkColor(WM_GetBkColor(hWin));
		GUI_ClearRect(xPos, 20, bmcalling0.XSize, bmcalling0.YSize);
		GUI_DrawBitmap(&bmcalling0, xPos, 20);
		for (int i = 0; i < (time & 3); i++)
			GUI_DrawBitmap(_abmcalling[i], xPos, 20);
		break;
	default:
		WM_DefaultProc(pMsg);
		break;

}
}


static void CallCancelCallback(void) {
	GSM_DISCONNECT_EXISTING_CONNECTION();
}
static GUI_HWIN CallViewShow() {
	return GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate),
			_cbCallView, NULL, 0, 2);
}
static uint32_t CallViewHide(GUI_HWIN hwin) {
	return 1;
}



void OnRing(void){

}

void OnCallStateChanged(CallInfo_Typedef callInfo){
	static GUI_HWIN hWin;
	if (callInfo.state == Incoming || callInfo.state == Dialing)
	{
		hWin=ViewNavigator_GoToViewOf(&DefaultViewNavigator, &CallView);
	} else if (callInfo.state == Disconnect) {
		ViewNavigator_GoBackView(&DefaultViewNavigator);
		hWin = GUI_HMEM_NULL;
	}
	if (hWin) {
		TEXT_SetText(WM_GetDialogItem(hWin, GUI_ID_TEXT0),
				callStateTextList[callInfo.state]);
		if (callInfo.Name == NULL)
			TEXT_SetText(WM_GetDialogItem(hWin, GUI_ID_TEXT1), callInfo.number);
		else
			TEXT_SetText(WM_GetDialogItem(hWin, GUI_ID_TEXT1), callInfo.Name);
	}

}
