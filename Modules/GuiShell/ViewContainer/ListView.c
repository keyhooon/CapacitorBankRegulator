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





extern GUI_CONST_STORAGE GUI_BITMAP bmItemIndexImage;



static GUI_HWIN ListViewShow(void *);
static uint8_t ListViewHide(GUI_HWIN hWin, void *);
void ListBackCallback(void *);
void ListOkCallback(void *);




const View_Typedef ListView = {
LIST_VIEW_ID, "List", "List", (void *) NULL, ListViewShow, ListViewHide,
		(const char*) "Back", (const char*) "Select", ListBackCallback,
		ListOkCallback };

static int _OwnerListDraw(const WIDGET_ITEM_DRAW_INFO * pDrawItemInfo) {
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
				+ FontDistY - bmItemIndexImage.YSize / 2, pDrawItemInfo->x0 + 7
				+ bmItemIndexImage.XSize, pDrawItemInfo->y0 + FontDistY
				+ bmItemIndexImage.YSize / 2 };
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
		GUI_DrawBitmap(&bmItemIndexImage, IconRect.x0 + 1, IconRect.y0 + 1);
		//
		// Draw index
		//
		GUI_SetTextMode(GUI_TEXTMODE_TRANS);
		char indexString[4];
		itoa(Index, indexString, 10);
		int indexStringDistX = GUI_GetStringDistX(indexString);
		GUI_DispStringInRect(indexString, &IconRect,
		GUI_TA_HCENTER | GUI_TA_VCENTER);
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

void SetListSkin(LISTBOX_Handle list) {
	LISTBOX_SetScrollbarWidth(list, 16);
	LISTBOX_SetAutoScrollV(list, 1);
	LISTBOX_SetItemSpacing(list, 10);
	LISTBOX_SetOwnerDraw(list, _OwnerListDraw);
}

static GUI_HWIN ListViewShow(void * parameters) {
	ListView_Parameters_Typedef * listView_parameters =
			(ListView_Parameters_Typedef *) parameters;
	listView_parameters->DisplayArray =
			listView_parameters->apiHandlers->GetDisplayArray();
	WM_HWIN hwin = WINDOW_CreateEx(0, 0, 128, 115, NULL, WM_CF_SHOW, 0x0,
			GUI_ID_USER, NULL);
	LISTBOX_Handle listbox_hwin = LISTBOX_CreateEx(0, 0, 128, 115, hwin,
	WM_CF_SHOW, 0, GUI_ID_LISTBOX0, listView_parameters->DisplayArray);
	SetListSkin(listbox_hwin);
	for (int i = 0; (*(listView_parameters->customFunction + i)) != NULL; i++)
		LISTBOX_AddString(listbox_hwin,
				(*(listView_parameters->customFunction + i))->display);
	LISTBOX_SetSel(listbox_hwin,
			listView_parameters->apiHandlers->GetSelectedIndex());
	listView_parameters->hWin = listbox_hwin;
	return hwin;
}
static uint8_t ListViewHide(GUI_HWIN hWin, void * parameters) {
	ListView_Parameters_Typedef * listView_parameters =
			(ListView_Parameters_Typedef *) parameters;
	listView_parameters->apiHandlers->FreeDisplayArray(
			listView_parameters->DisplayArray);
	return 0;
}
void ListOkCallback(void * parameters) {
	ListView_Parameters_Typedef * listView_parameters =
			(ListView_Parameters_Typedef *) parameters;
	uint32_t selItem = LISTBOX_GetSel(listView_parameters->hWin);
	uint32_t count = listView_parameters->apiHandlers->GetCount();
	if (selItem < count) {
		listView_parameters->apiHandlers->SetSelectedIndex(selItem);
		listView_parameters->SelectCallback();
	} else
		(*(listView_parameters->customFunction + (selItem - count)))->function();
}

void ListBackCallback(void * parameters) {
	ViewNavigator_GoBackView(&DefaultViewNavigator);
}


