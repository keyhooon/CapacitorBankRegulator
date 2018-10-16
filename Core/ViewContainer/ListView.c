/*
 * ListView.c
 *
 *  Created on: Oct 7, 2018
 *      Author: HP
 */

#include "DIALOG.h"
#include "WM.h"
#include "ViewNavigator.h"

GUI_HWIN ListViewShow(void);
uint8_t ListVIewHide(GUI_HWIN hWin);
/*********************************************************************
 *
 *       Defines
 *
 **********************************************************************
 */

/*********************************************************************
 *
 *       Static data
 *
 **********************************************************************
 */

// USER START (Optionally insert additional static data)
// USER END


/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */

// USER START (Optionally insert additional static code)
// USER END

/*********************************************************************
 *
 *       _cbDialog
 */
static void _cbDialog(WM_MESSAGE * pMsg) {
	WM_HWIN hItem;
	int xSize, ySize;
	int NCode;
	int Id;
	// USER START (Optionally insert additional variables)
	// USER END

	switch (pMsg->MsgId) {
	case WM_CREATE:
		//
		// Initialization of 'ContactListWheel'
		//
		xSize = WM_GetWindowSizeX(hWin);
		ySize = WM_GetWindowSizeY(hWin);
		LISTBOX_CreateEx(0, 0, xSize, ySize, pMsg->hWin, 0, 0, GUI_ID_LISTBOX0);
		hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_LISTBOX0);
		void * selectedItem;
		WM_GetUserData(pMsg->hWin, &(pMsg->hWin), sizeof(void*));
		// USER START (Optionally insert additional code for further widget initialization)

		// USER END
		break;
	case WM_NOTIFY_PARENT:
		Id = WM_GetId(pMsg->hWinSrc);
		NCode = pMsg->Data.v;
		switch (Id) {
		case GUI_ID_LISTBOX0: // Notifications sent by 'ContactListWheel'
			switch (NCode) {
			case WM_NOTIFICATION_CLICKED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
			case WM_NOTIFICATION_RELEASED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
			case WM_NOTIFICATION_SEL_CHANGED:
				// USER START (Optionally insert code for reacting on notification message)
				// USER END
				break;
				// USER START (Optionally insert additional code for further notification handling)
				// USER END
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
		WINDOW_CreateIndirect, "Dialog", GUI_ID_USER, 0, 0, 128, 115, 0, 0x0,
		sizeof(void*) }, { LISTBOX_CreateIndirect, "List",
		GUI_ID_LISTBOX0, 0,
		0, 128, 115, 0, 0x0, 0 } };
GUI_HWIN ListViewShow(void) {
	return WINDOW_CreateUser(0, 0, 128, 115, NULL, 0, 0x0, GUI_ID_USER,
			_cbDialog, sizeof(void*));
}

