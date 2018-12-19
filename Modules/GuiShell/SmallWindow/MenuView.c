/*
 * MenuView.c
 *
 *  Created on: Oct 10, 2018
 *      Author: HP
 */
#include "ViewContainer/ViewNavigator.h"


/*********************************************************************
 *
 *       Defines
 *
 **********************************************************************
 */
#define ID_WINDOW_03     (GUI_ID_USER + 0x20)


/*********************************************************************
 *
 *       Static data
 *
 **********************************************************************
 */

// USER START (Optionally insert additional static data)

extern GUI_CONST_STORAGE GUI_BITMAP bmCalllogs;
extern GUI_CONST_STORAGE GUI_BITMAP bmContact;
extern GUI_CONST_STORAGE GUI_BITMAP bmMessage;
extern GUI_CONST_STORAGE GUI_BITMAP bmScan;
extern GUI_CONST_STORAGE GUI_BITMAP bmSetting;
extern GUI_CONST_STORAGE GUI_BITMAP bmZone;

uint8_t SelectedItem = 0;

static GUI_HWIN show(void);
static uint8_t hide(GUI_HWIN hWin);
static void okCallback(void);
static void backCallback(void);

extern void InitContactView(void);
extern void InitMessageView(void);

const View_Typedef MenuView = { MENU_VIEW_ID, (const char*) "Main Menu",
		(const char*) "Menu", (void*) 0,
	show,
		hide, (const char*) "Back",
		(const char*) "OK", backCallback, okCallback, NULL, &SelectedItem };

/*********************************************************************
 *
 *       _cbDialog
 */
static void _cbDialog(WM_MESSAGE * pMsg) {
	ICONVIEW_Handle hItem;
	int NCode;
	int Id;
	// USER START (Optionally insert additional variables)
	// USER END

	switch (pMsg->MsgId) {
	case WM_INIT_DIALOG:
		//
		// Initialization of 'SettingList'
		//

		hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_ICONVIEW0);
		ICONVIEW_SetIconAlign(hItem, ICONVIEW_IA_HCENTER | ICONVIEW_IA_TOP);

		ICONVIEW_SetTextColor(hItem, ICONVIEW_CI_UNSEL, GUI_BLACK);

		ICONVIEW_SetSpace(hItem, GUI_COORD_Y, -1);
		ICONVIEW_SetSpace(hItem, GUI_COORD_X, 18);

		ICONVIEW_SetTextAlign(hItem, GUI_TA_BOTTOM | GUI_TA_HCENTER);

		ICONVIEW_AddBitmapItem(hItem, &bmContact, "Contact");
		ICONVIEW_AddBitmapItem(hItem, &bmMessage, "Message");
		ICONVIEW_AddBitmapItem(hItem, &bmCalllogs, "Call Log");
		ICONVIEW_AddBitmapItem(hItem, &bmScan, "Dial");
		ICONVIEW_AddBitmapItem(hItem, &bmZone, "Zone");
		ICONVIEW_AddBitmapItem(hItem, &bmSetting, "Setting");
		ICONVIEW_SetSel(hItem, SelectedItem);
		// USER END
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case GUI_ID_ICONVIEW0: // Notifications sent by 'SettingList'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
			case WM_NOTIFICATION_MOVED_OUT:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
			case WM_NOTIFICATION_SCROLL_CHANGED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
			case WM_NOTIFICATION_SEL_CHANGED:
				// USER START (Optionally insert code for reacting on notification message)
				if (ICONVIEW_GetSel(pMsg->hWinSrc) != SelectedItem)
					SelectedItem = ICONVIEW_GetSel(pMsg->hWinSrc);
				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
			default:
				WM_DefaultProc(pMsg);
				break;
			}
			break;
			// USER START (Optionally insert additional code for further Ids)
			// USER END
		}
		break;
		// USER START (Optionally insert additional message handling)
		// USER END
	default:
		WM_DefaultProc(pMsg);
		break;
	}
}
/*********************************************************************
 *
 *       _aDialogCreate
 */
static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = { {
		WINDOW_CreateIndirect, "Main Menu", ID_WINDOW_03, 0, 0, 128, 115, 0,
		0x0, 0 }, { ICONVIEW_CreateIndirect, "SettingList", GUI_ID_ICONVIEW0,
		0, 0,
		128, 115, WM_CF_SHOW | WM_CF_HASTRANS,
		ICONVIEW_CF_AUTOSCROLLBAR_V | 0x00240030, 0 },
		};
static GUI_HWIN show(void) {
	return GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate),
			_cbDialog, NULL, 0, 2);
}
static uint8_t hide(GUI_HWIN hWin) {
	return 0;
}
static void okCallback(void) {
	switch (SelectedItem) {
	case 0:
		InitContactView();
		break;
	case 1:
		InitMessageView();
		break;
	break;
	default:
		break;
	}
}
static void backCallback(void) {
	ViewNavigator_GoBackView(&DefaultViewNavigator);
}
