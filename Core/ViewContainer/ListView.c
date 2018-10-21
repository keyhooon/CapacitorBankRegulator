/*
 * ListView.c
 *
 *  Created on: Oct 7, 2018
 *      Author: HP
 */

#include "DIALOG.h"
#include "WM.h"
#include "ViewNavigator.h"
#include "ListView.h"
#include "Contact.h"

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

const char* CommandDisplay[3] = { (const char*) "View", (const char*) "Edit",
		(const char*) "Delete" };
// USER START (Optionally insert additional static data)
// USER END


/*********************************************************************
 *
 *       Static code
 *
 **********************************************************************
 */
static int _OwnerDraw(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo);

void SetListBoxSkin(LISTBOX_Handle list) {
	LISTBOX_SetScrollbarWidth(list, 16);
	LISTBOX_SetAutoScrollV(list, 1);
	LISTBOX_SetItemSpacing(list, 10);
	LISTBOX_SetOwnerDraw(list, _OwnerDraw);
}

/*********************************************************************
 *
 *       _OwnerDraw
 *
 * Function description
 *   This is the owner draw function.
 *   It allows complete customization of how the items in the listbox are
 *   drawn. A command specifies what the function should do;
 *   The minimum is to react to the draw command (WIDGET_ITEM_DRAW);
 *   If the item x-size differs from the default, then this information
 *   needs to be returned in reaction to WIDGET_ITEM_GET_XSIZE.
 *   To insure compatibility with future version, all unhandled commands
 *   must call the default routine LISTBOX_OwnerDraw.
 */
static int _OwnerDraw(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
	WM_HWIN hWin;
	int Index;

	hWin = pDrawItemInfo->hWin;
	Index = pDrawItemInfo->ItemIndex;
	switch (pDrawItemInfo->Cmd) {
	case WIDGET_ITEM_DRAW: {
		int MultiSel;
		int Sel;
		int YSize;
		int FontDistY;
		int IsDisabled;
		int IsSelected;
		int ColorIndex;
		char acBuffer[100];
		const GUI_FONT * pOldFont = 0;

		GUI_COLOR aColor[4] = { GUI_BLACK, GUI_WHITE, GUI_WHITE, GUI_GRAY };
		GUI_COLOR aBkColor[4] = { GUI_WHITE, GUI_GRAY, GUI_BLUE, 0xC0C0C0 };
		IsDisabled = LISTBOX_GetItemDisabled(pDrawItemInfo->hWin,
				pDrawItemInfo->ItemIndex);
		IsSelected = LISTBOX_GetItemSel(hWin, Index);
		MultiSel = LISTBOX_GetMulti(hWin);
		Sel = LISTBOX_GetSel(hWin);
		YSize = GUI_GetFontDistY() + 11;
		//
		// Calculate color index
		//
		if (MultiSel) {
			if (IsDisabled) {
				ColorIndex = 3;
			} else {
				ColorIndex = (IsSelected) ? 2 : 0;
			}
		} else {
			if (IsDisabled) {
				ColorIndex = 3;
			} else {
				if (pDrawItemInfo->ItemIndex == Sel) {
					ColorIndex = WM_HasFocus(pDrawItemInfo->hWin) ? 2 : 1;
				} else {
					ColorIndex = 0;
				}
			}
		}
		//
		// Draw item
		//
		GUI_SetBkColor(aBkColor[ColorIndex]);
		GUI_SetColor(aColor[ColorIndex]);
		LISTBOX_GetItemText(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex,
				acBuffer, sizeof(acBuffer));
		GUI_Clear();
		if ((ColorIndex == 1) || (ColorIndex == 2)) {
			pOldFont = GUI_SetFont(&GUI_Font13HB_1);
		}
		FontDistY = GUI_GetFontDistY();
		GUI_DispStringAt(acBuffer,
				pDrawItemInfo->x0 + 16,
				pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
		if (pOldFont) {
			GUI_SetFont(pOldFont);
		}
		GUI_DispCEOL();
		//
		// Draw bitmap
		//
//		GUI_DrawBitmap(&bmItemIndexImage, pDrawItemInfo->x0 + 7,
//				pDrawItemInfo->y0 + (YSize - bmItemIndexImage.YSize) / 2);
		//
		// Draw index
		//
		GUI_SetTextMode(GUI_TEXTMODE_TRANS);
		int CharDistX = GUI_GetCharDistX('0');
		if (Index <= 9)
			GUI_GotoXY(
					pDrawItemInfo->x0 + 7
			/*+ (bmItemIndexImage.XSize - CharDistX) / 2*/,
					pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
		else
			GUI_GotoXY(
					pDrawItemInfo->x0 + 7
							+ (/*bmItemIndexImage.XSize / 2*/-CharDistX),
					pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
		GUI_DispDecMin(Index);
		//
		// Draw focus rectangle
		//
		if (MultiSel && (pDrawItemInfo->ItemIndex == Sel)) {
			GUI_RECT rFocus;
			GUI_RECT rInside;

			WM_GetInsideRectEx(pDrawItemInfo->hWin, &rInside);
			rFocus.x0 = pDrawItemInfo->x0;
			rFocus.y0 = pDrawItemInfo->y0;
			rFocus.x1 = rInside.x1;
			rFocus.y1 = pDrawItemInfo->y0 + YSize - 1;
			GUI_SetColor(GUI_WHITE - aBkColor[ColorIndex]);
			GUI_DrawFocusRect(&rFocus, 0);
		}
	}
		break;
	default:
		return LISTBOX_OwnerDraw(pDrawItemInfo);
	}
	return 0;
}
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
		// USER START (Optionally insert additional code for further widget initialization)
		hItem = WM_GetDialogItem(pMsg->hWin, GUI_ID_LISTBOX0);

		// USER START (Optionally insert additional code for further widget initialization)
		SetListBoxSkin(hItem);
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
char** DisplayArray;
GUI_HWIN ListViewShow(ListApiHandlers_typedef ListApiHandlers) {
	WM_HWIN hwin = WINDOW_CreateEx(0, 0, 128, 115, NULL, WM_CF_SHOW, 0x0,
			GUI_ID_USER,
			_cbDialog);
	DisplayArray = ListApiHandlers.GetDisplayArray();
	LISTBOX_Handle listbox_hwin = LISTBOX_CreateEx(0, 0, 128, 115, hwin,
			WM_CF_SHOW, 0,
			GUI_ID_LISTBOX0,
			DisplayArray);

	LISTBOX_AddString(listbox_hwin, "Add New ...");
	LISTBOX_SetSel(listbox_hwin, ListApiHandlers.GetCurrentItemIndex());
	return hwin;
}
uint32_t ListViewHide(ListApiHandlers_typedef ListApiHandlers, GUI_HWIN hwin) {
	ListApiHandlers.FreeDisplayArray(DisplayArray);
	ListApiHandlers.SetCurrentItem(LISTBOX_GetSel(WM_GetFirstChild(hwin)));
	return 1;
}

GUI_HWIN OptionListViewShow(ListViewOption_typedef ListViewOption,
		CustomFunctionList_Typedef FunctionList) {
	WM_HWIN hwin = WINDOW_CreateEx(0, 0, 128, 115, NULL, WM_CF_SHOW, 0x0,
	GUI_ID_USER,
	NULL);
	uint32_t itemCount = FunctionList.count;
	itemCount += (ListViewOption.canRemove == 1) + (ListViewOption.canEdit == 1)
			+ 1;
	DisplayArray = pvPortMalloc((itemCount + 1) * sizeof(char*));
	int i = FunctionList.count;
	memcpy(DisplayArray, FunctionList.display,
			FunctionList.count * sizeof(void*));
	*(DisplayArray + i++) = CommandDisplay[0];
	if (ListViewOption.canEdit)
		*(DisplayArray + i++) = CommandDisplay[1];
	if (ListViewOption.canRemove)
		*(DisplayArray + i++) = CommandDisplay[2];
	*(DisplayArray + i) = NULL;
	currentWidget = LISTBOX_CreateEx(0, 0, 128, 115, hwin,
	WM_CF_SHOW, 0,
	GUI_ID_LISTBOX0, DisplayArray);
	return hwin;
}
uint32_t OptionListViewHide(ListViewOption_typedef ListViewOption,
		CustomFunctionList_Typedef FunctionList,
		GUI_HWIN hwin) {
	vPortFree(DisplayArray);
	return 1;
}
