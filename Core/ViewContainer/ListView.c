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

typedef struct {
	ListApiHandlers_typedef * ApiHandlers;
	CustomFunction_Typedef ** CustomFunctionList;
	GUI_HWIN CurrentWidget;
	int SizeOfType;
	void (*EditProgress)(void * arg, GUI_HWIN currentWidget);
	void * EditArg;
} ListView_Typedef;

ListView_Typedef * DefaultListView;
char** DisplayArray;

extern GUI_CONST_STORAGE GUI_BITMAP bmItemIndexImage;
extern GUI_CONST_STORAGE GUI_BITMAP bmpencil;
extern GUI_CONST_STORAGE GUI_BITMAP bmloupe;
extern GUI_CONST_STORAGE GUI_BITMAP bmdelete;



void EditFunctionCallback();
void ViewInfoFunctionCallBcak();
void DeleteFunctionCallback();

CustomFunction_Typedef EditFunction =
		{ &bmpencil, "Edit", EditFunctionCallback };
CustomFunction_Typedef ViewInfoFunction = { &bmloupe, "View",
		ViewInfoFunctionCallBcak };
CustomFunction_Typedef DeleteFunction = { &bmdelete, "Delete",
		DeleteFunctionCallback };

void backCallback(void);

static GUI_HWIN ListViewShow(void);
static uint8_t ListViewHide(GUI_HWIN hWin);
void ListBackCallback(void);
void ListOkCallback(void);
const View_Typedef ListView = {
LIST_VIEW_ID, "List", "List", (void *) NULL, ListViewShow, ListViewHide,
		(const char*) "Back", (const char*) "Select", ListBackCallback,
		ListOkCallback, NULL, 0 };

static GUI_HWIN OptionListViewShow(void);
static uint8_t OptionListViewHide(GUI_HWIN hWin);
void OptionOkCallback(void);
const View_Typedef ListOptionView = {
OPTION_VIEW_ID, "Option", "Opt", (void *) NULL, OptionListViewShow,
		OptionListViewHide, (const char*) "Back", (const char*) "OK",
		backCallback, OptionOkCallback, NULL, 0 };

static GUI_HWIN EditViewShow();
static uint8_t EditViewHide(GUI_HWIN hWin);
void EditViewOkCallback(void);
const View_Typedef ListEditView = {
EDIT_VIEW_ID, "Edit", "Edit", (void *) NULL, EditViewShow, EditViewHide,
		(const char*) "Cancel", (const char*) "OK", backCallback,
		EditViewOkCallback, NULL, 0 };

static GUI_HWIN InfoViewShow();
static uint8_t InfoViewHide(GUI_HWIN hWin);
const View_Typedef ListInfoView = {
INFO_VIEW_ID, "View", "View", (void *) NULL, InfoViewShow, InfoViewHide,
NULL, (const char*) "Back", NULL, backCallback, NULL, 0 };




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
		CustomFunction_Typedef ** t = DefaultListView->CustomFunctionList;
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

void SetListSkin(LISTBOX_Handle list) {
	LISTBOX_SetScrollbarWidth(list, 16);
	LISTBOX_SetAutoScrollV(list, 1);
	LISTBOX_SetItemSpacing(list, 10);
	LISTBOX_SetOwnerDraw(list, _OwnerListDraw);
}
void SetOptionListSkin(LISTBOX_Handle list) {
	LISTBOX_SetScrollbarWidth(list, 16);
	LISTBOX_SetAutoScrollV(list, 1);
	LISTBOX_SetItemSpacing(list, 10);
	LISTBOX_SetOwnerDraw(list, _OwnerOptionListDraw);
}




void ListViewInit(ListApiHandlers_typedef * apiHandlers,
		CustomFunction_Typedef ** customFunction,
		uint32_t sizeOfType,
		void (*editProgress)(void)) {
	if (DefaultListView != NULL)
		ListViewDeInit();
	DefaultListView = pvPortMalloc(sizeof(ListView_Typedef));
	DefaultListView->ApiHandlers = apiHandlers;
	DefaultListView->CustomFunctionList = customFunction;
	DefaultListView->SizeOfType = sizeOfType;
	DefaultListView->EditProgress = editProgress;
}

void ListViewDeInit(void) {
	if (DefaultListView != NULL)
		vPortFree(DefaultListView);
	DefaultListView = 0;
}



static GUI_HWIN EditViewShow(void) {
	int xSize, ySize;
	DefaultListView->EditArg = pvPortMalloc(
			DefaultListView->SizeOfType + sizeof(int));
	memset(DefaultListView->EditArg, 0,
			DefaultListView->SizeOfType + sizeof(int));
	memcpy(DefaultListView->EditArg,
			DefaultListView->ApiHandlers->GetCurrentItem(),
			DefaultListView->SizeOfType);
	WM_HWIN hwin = WINDOW_CreateEx(0, 0, 128, 115, NULL, WM_CF_SHOW, 0x0,
	GUI_ID_USER, NULL);
	DefaultListView->CurrentWidget = hwin;
	DefaultListView->EditProgress(DefaultListView->EditArg,
			DefaultListView->CurrentWidget);
	return hwin;
}
static uint8_t EditViewHide(GUI_HWIN hWin) {
	vPortFree(DefaultListView->EditArg);
	return 1;
}
static GUI_HWIN ListViewShow(void) {
	WM_HWIN hwin = WINDOW_CreateEx(0, 0, 128, 115, NULL, WM_CF_SHOW, 0x0,
			GUI_ID_USER, NULL);
	DisplayArray = DefaultListView->ApiHandlers->GetDisplayArray();
	LISTBOX_Handle listbox_hwin = LISTBOX_CreateEx(0, 0, 128, 115, hwin,
			WM_CF_SHOW, 0, GUI_ID_LISTBOX0, DisplayArray);
	SetListSkin(listbox_hwin);
	DefaultListView->CurrentWidget = listbox_hwin;
	LISTBOX_AddString(listbox_hwin, "Add New ...");
	LISTBOX_SetSel(listbox_hwin,
			DefaultListView->ApiHandlers->GetCurrentItemIndex());
	return hwin;
}
static uint8_t ListViewHide(GUI_HWIN hWin) {
	DefaultListView->ApiHandlers->FreeDisplayArray(DisplayArray);
	return 1;
}
void ListOkCallback(void) {
	uint32_t selItem = LISTBOX_GetSel(DefaultListView->CurrentWidget);
	if (selItem < DefaultListView->ApiHandlers->GetListLen()) {
		DefaultListView->ApiHandlers->SetCurrentItem(selItem);
		ViewNavigator_GoToViewOf(&DefaultViewNavigator, &ListOptionView);
	} else {
		Contact_Typedef contact = { 0, NULL, NULL, NULL, };
		DefaultListView->ApiHandlers->Add(&contact);
		ViewNavigator_GoToViewOf(&DefaultViewNavigator, &ListEditView);
	}
}

void ListBackCallback(void) {
	ViewNavigator_GoBackView(&DefaultViewNavigator);
	ListViewDeInit();
}


static GUI_HWIN OptionListViewShow(void) {
	WM_HWIN hwin = WINDOW_CreateEx(0, 0, 128, 115, NULL, WM_CF_SHOW, 0x0,
			GUI_ID_USER, NULL);
	CustomFunction_Typedef ** t = DefaultListView->CustomFunctionList;
	uint32_t i = 0;
	char *MenuDisplayText[10];

	while (*t != NULL)
		MenuDisplayText[i++] = (*t++)->display;
	MenuDisplayText[i] = 0;
	LISTBOX_Handle listbox_hwin = LISTBOX_CreateEx(0, 0, 128, 115, hwin,
			WM_CF_SHOW, 0, GUI_ID_LISTBOX1, MenuDisplayText);
	DefaultListView->CurrentWidget = listbox_hwin;
	SetOptionListSkin(listbox_hwin);
	return hwin;
}

static uint8_t OptionListViewHide(GUI_HWIN hWin) {
	return 1;
}

static GUI_HWIN InfoViewShow() {
	WM_HWIN hwin = WINDOW_CreateEx(0, 0, 128, 115, NULL, WM_CF_SHOW, 0x0,
			GUI_ID_USER, NULL);
	char temp[33];
	DefaultListView->ApiHandlers->GetDisplay(temp);
	TEXT_Handle text_hwin = TEXT_CreateEx(5, 5, 118, 115, hwin, WM_CF_SHOW, 0,
			GUI_ID_TEXT0, temp);
	TEXT_SetFont(text_hwin, &GUI_Font8x10_ASCII);
	TEXT_SetWrapMode(text_hwin, GUI_WRAPMODE_WORD);
	DefaultListView->CurrentWidget = text_hwin;
	return hwin;
}

static uint8_t InfoViewHide(GUI_HWIN hWin) {
	return 1;
}




void EditViewOkCallback(void) {
	DefaultListView->EditProgress(DefaultListView->EditArg,
			DefaultListView->CurrentWidget);
}

void OptionOkCallback(void) {
	uint32_t sel = LISTBOX_GetSel(DefaultListView->CurrentWidget);
	(*(DefaultListView->CustomFunctionList + sel))->function();
}
void EditFunctionCallback() {
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &ListEditView);
}

void ViewInfoFunctionCallBcak() {
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &ListInfoView);
}

void DeleteFunctionCallback() {
	DefaultListView->ApiHandlers->Remove();
	ViewNavigator_GoBackView(&DefaultViewNavigator);
}

void backCallback(void) {
	ViewNavigator_GoBackView(&DefaultViewNavigator);
}
