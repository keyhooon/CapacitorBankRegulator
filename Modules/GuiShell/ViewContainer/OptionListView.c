/*
 * OptionListView.c
 *
 *  Created on: Dec 16, 2018
 *      Author: HP
 */


#include "DIALOG.h"
#include "WM.h"
#include "ViewNavigator.h"
#include "OptionListView.h"



static GUI_HWIN OptionListViewShow(void *);
static uint8_t OptionListViewHide(GUI_HWIN hWin, void *);
static void OptionListOkCallback(void *);
static void backCallback(void *);
const View_Typedef OptionListView = {
OPTION_VIEW_ID, "Option", "Opt", (void *) NULL, OptionListViewShow,
		OptionListViewHide, (const char*) "Back", (const char*) "OK",
		backCallback, OptionListOkCallback, NULL, 0 };

static int _OwnerOptionListDraw(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
	WM_HWIN hWin = pDrawItemInfo->hWin;
	int Index = pDrawItemInfo->ItemIndex;

	switch (pDrawItemInfo->Cmd) {
	case WIDGET_ITEM_GET_YSIZE: {
		//GUI_GetFontDistYLISTBOX_GetFont(hWin);
		return GUI_GetFontDistY() * 2;
	}
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
		IsDisabled = LISTBOX_GetItemDisabled(hWin, Index);
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
		FontDistY = GUI_GetFontDistY();

		GUI_RECT IconRect = { pDrawItemInfo->x0 + 3, pDrawItemInfo->y0
				+ FontDistY - 8, pDrawItemInfo->x0 + 7 + 16, pDrawItemInfo->y0
				+ FontDistY + 8 };
		GUI_RECT TextRect = { IconRect.x1 + 3, pDrawItemInfo->y0,
				pDrawItemInfo->x1, pDrawItemInfo->y0 + FontDistY * 2 };
		//
		// Draw item
		//
		GUI_SetBkColor(aBkColor[ColorIndex]);
		GUI_SetColor(aColor[ColorIndex]);
		LISTBOX_GetItemText(pDrawItemInfo->hWin, pDrawItemInfo->ItemIndex,
				acBuffer, sizeof(acBuffer));
		GUI_Clear();
		if ((ColorIndex == 1) || (ColorIndex == 2)) {
			pOldFont = GUI_SetFont(&GUI_Font8x10_ASCII);
		}
		GUI_DispStringInRect(acBuffer, &TextRect, GUI_TA_LEFT | GUI_TA_VCENTER);
		if (pOldFont) {
			GUI_SetFont(pOldFont);
		}
		GUI_DispCEOL();
		//
		// Draw bitmap
		//
		CustomFunction_Typedef ** t;
		WM_GetUserData(hWin, t, sizeof(CustomFunction_Typedef **));
		if ((*(t + Index))->Icon != NULL)
			GUI_DrawBitmap((*(t + Index))->Icon, IconRect.x0 + 1,
					IconRect.y0 + 1);

		//
		// Draw index
		//
//		GUI_SetTextMode(GUI_TEXTMODE_TRANS);
//		char indexString[4];
//		itoa(Index, indexString, 10);
//		int indexStringDistX = GUI_GetStringDistX(indexString);
//		GUI_DispStringInRect(indexString, &IconRect,
//				GUI_TA_HCENTER | GUI_TA_VCENTER);
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
void SetOptionListSkin(LISTBOX_Handle list) {
	LISTBOX_SetScrollbarWidth(list, 16);
	LISTBOX_SetAutoScrollV(list, 1);
	LISTBOX_SetItemSpacing(list, 10);
	LISTBOX_SetOwnerDraw(list, _OwnerOptionListDraw);
}

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = { //
		{ WINDOW_CreateIndirect, "Option", GUI_ID_USER, 0, 0, 128, 115,
				WM_CF_SHOW, 0x0, 0 }, //
				{ LISTBOX_CreateIndirect, "OptionList", GUI_ID_LISTBOX0, 5, 5,
						118, 105, 0, 0, sizeof(CustomFunction_Typedef **) }, //
		};
static GUI_HWIN OptionListViewShow(void * parameters) {
	OptionListView_Parameters_Typedef * param =
			(OptionListView_Parameters_Typedef *) parameters;
	WM_HWIN hwin = GUI_CreateDialogBox(_aDialogCreate,
			GUI_COUNTOF(_aDialogCreate), NULL, NULL, 0, 0);
	GUI_HWIN hListWin = WM_GetDialogItem(hwin, GUI_ID_LISTBOX0);
	WM_SetUserData(hListWin, param->customFunction,
			sizeof(CustomFunction_Typedef **));

	for (int i = 0; *(param->customFunction + i) == NULL; i++)
		LISTBOX_AddString(hListWin,
				(*(CustomFunction_Typedef **) (param->customFunction + i))->display);
	SetOptionListSkin(hListWin);
	return hwin;
}

static uint8_t OptionListViewHide(GUI_HWIN hWin, void * parameters) {
	return 0;
}

static void OptionListOkCallback(void * parameters) {
	OptionListView_Parameters_Typedef * param =
			(OptionListView_Parameters_Typedef *) parameters;
	WM_HWIN countainer_hwin = WM_GetFirstChild(
			DefaultViewNavigator.view_container_hWin);
	GUI_HWIN hListWin = WM_GetDialogItem(countainer_hwin, GUI_ID_LISTBOX0);
	(*(param->customFunction + LISTBOX_GetSel(hListWin)))->function();
}
static void backCallback(void * parameters) {
	ViewNavigator_GoBackView(&DefaultViewNavigator);
}


