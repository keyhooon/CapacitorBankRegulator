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


static void _cbCallView(WM_MESSAGE * pMsg) {
	static int time;
	int xSize, xPos;

	WM_HWIN hWin;
	hWin = pMsg->hWin;
	switch (pMsg->MsgId) {
	case WM_CREATE:
		//
		// Create timer to be used to modify the battery symbol
		//
		WM_CreateTimer(hWin, 0, 1000, 0);
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
		GUI_SetTextMode(GUI_TEXTMODE_XOR);
		GUI_Clear();

		GUI_DrawBitmap(&bmcalling0, xPos, 10);
		for (int i = 0; i < (time & 3); i++)
			GUI_DrawBitmap(_abmcalling[i], xPos, 0);
		CallInfo_Typedef callInfo;
		WINDOW_GetUserData(hWin, &callInfo, sizeof(CallInfo_Typedef));
		if (callInfo.Name == NULL)
			GUI_DispStringHCenterAt(callInfo.number, xSize / 2, 80);
		else {
			GUI_DispStringHCenterAt(callInfo.Name, xSize / 2, 80);
		}
}
}


static void CallCancelCallback(void) {
	GSM_DISCONNECT_EXISTING_CONNECTION();
}
static GUI_HWIN CallViewShow() {
	WM_HWIN hwin = WINDOW_CreateUser(0, 0, 128, 115, NULL, WM_CF_SHOW, 0x0,
			GUI_ID_USER, _cbCallView,sizeof(CallInfo_Typedef));
	return hwin;
}
static uint32_t CallViewHide(GUI_HWIN hwin) {
	return 1;
}



void OnRing(void){

}

void OnCallStateChanged(CallInfo_Typedef callInfo){

	static GUI_HWIN hWin;
	if (callInfo.state == Incoming || callInfo.state == Alerting)
		hWin=ViewNavigator_GoToViewOf(&DefaultViewNavigator, &CallView);
	WINDOW_SetUserData(hWin,&callInfo, sizeof(CallInfo_Typedef));
}
