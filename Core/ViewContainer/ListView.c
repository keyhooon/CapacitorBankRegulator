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
	ListViewOption_typedef Option;
	CustomFunctionList_Typedef CustomFunctionList;
	GUI_HWIN CurrentWidget;
	int SizeOfType;
	void (*EditProgress)(void * arg, GUI_HWIN currentWidget);
	void * EditArg;
} ListView_Typedef;

ListView_Typedef * DefaultListView;
extern GUI_CONST_STORAGE GUI_BITMAP bmItemIndexImage;


static GUI_HWIN ListViewShow(void);
static uint8_t ListViewHide(GUI_HWIN hWin);

static GUI_HWIN OptionListViewShow(void);
static uint8_t OptionListViewHide(GUI_HWIN hWin);

static GUI_HWIN EditViewShow();
static uint8_t EditViewHide(GUI_HWIN hWin);

static GUI_HWIN InfoViewShow();
static uint8_t InfoViewHide(GUI_HWIN hWin);


const char* CommandDisplay[3] = { (const char*) "View", (const char*) "Edit",
		(const char*) "Delete" };

const View_Typedef ListView = {
LIST_VIEW_ID, "List", "List", (void *) NULL, ListViewShow, ListViewHide,
		(const char*) "Back", (const char*) "Select", backCallback,
		ListOkCallback, NULL, 0 };

const View_Typedef ListOptionView = {
OPTION_VIEW_ID, "Option", "Opt", (void *) NULL, OptionListViewShow,
		OptionListViewHide, (const char*) "Back", (const char*) "OK",
		backCallback, OptionOkCallback, NULL, 0 };

const View_Typedef ListEditView = {
EDIT_VIEW_ID, "Edit", "Edit", (void *) NULL, EditViewShow, EditViewHide,
		(const char*) "Cancel", (const char*) "OK", backCallback,
		EditViewOkCallback, NULL, 0 };

const View_Typedef ListInfoView = {
INFO_VIEW_ID, "View", "View", (void *) NULL, InfoViewShow, InfoViewHide,
NULL, (const char*) "Cancel", NULL, backCallback, NULL, 0 };


char** DisplayArray;

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
				pDrawItemInfo->x0 + bmItemIndexImage.XSize + 16,
				pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
		if (pOldFont) {
			GUI_SetFont(pOldFont);
		}
		GUI_DispCEOL();
		//
		// Draw bitmap
		//
		GUI_DrawBitmap(&bmItemIndexImage, pDrawItemInfo->x0 + 7,
				pDrawItemInfo->y0 + (YSize - bmItemIndexImage.YSize) / 2);
		//
		// Draw index
		//
		GUI_SetTextMode(GUI_TEXTMODE_TRANS);
		int CharDistX = GUI_GetCharDistX('0');
		if (Index <= 9)
			GUI_GotoXY(
					pDrawItemInfo->x0 + 7
							+ (bmItemIndexImage.XSize - CharDistX) / 2,
					pDrawItemInfo->y0 + (YSize - FontDistY) / 2);
		else
			GUI_GotoXY(
					pDrawItemInfo->x0 + 7
							+ (bmItemIndexImage.XSize / 2 - CharDistX),
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

void SetListBoxSkin(LISTBOX_Handle list) {
//	LISTBOX_SetScrollbarWidth(list, 16);
	LISTBOX_SetAutoScrollV(list, 1);
	LISTBOX_SetItemSpacing(list, 10);
	LISTBOX_SetOwnerDraw(list, _OwnerDraw);
}

void ListViewInit(ListApiHandlers_typedef * apiHandlers,
		ListViewOption_typedef option,
		CustomFunctionList_Typedef customFunction, uint32_t sizeOfType,
		void (*editProgress)(void)) {
	DefaultListView = pvPortMalloc(sizeof(ListView_Typedef));
	DefaultListView->ApiHandlers = apiHandlers;
	memcpy(&(DefaultListView->Option), &option, sizeof(ListViewOption_typedef));
	memcpy(&(DefaultListView->CustomFunctionList), &customFunction,
			sizeof(CustomFunctionList_Typedef));
	DefaultListView->SizeOfType = sizeOfType;
	DefaultListView->EditProgress = editProgress;
}

void ListViewDeInit(void) {
	vPortFree(DefaultListView);
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
	TEXT_CreateAsChild(5, 20, 118, 40, hwin, GUI_ID_TEXT0, WM_CF_SHOW, "",
			TEXT_CF_TOP | TEXT_CF_HCENTER);
	GUI_HWIN editHwin = EDIT_CreateAsChild(5, 65, 118, 40, hwin, GUI_ID_EDIT0,
			WM_CF_SHOW, 15);
	WM_SetFocus(editHwin);
	EDIT_SetTextMode(editHwin);
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
	GUI_ID_USER,
	NULL);
	DisplayArray = DefaultListView->ApiHandlers->GetDisplayArray();
	LISTBOX_Handle listbox_hwin = LISTBOX_CreateEx(0, 0, 128, 115, hwin,
	WM_CF_SHOW, 0,
	GUI_ID_LISTBOX0, DisplayArray);
	SetListBoxSkin(listbox_hwin);
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


static GUI_HWIN OptionListViewShow(void) {
	WM_HWIN hwin = WINDOW_CreateEx(0, 0, 128, 115, NULL, WM_CF_SHOW, 0x0,
	GUI_ID_USER,
	NULL);
	uint32_t itemCount = DefaultListView->CustomFunctionList.count;
	itemCount += (DefaultListView->Option.canRemove == 1)
			+ (DefaultListView->Option.canEdit == 1) + 1;
	DisplayArray = pvPortMalloc((itemCount + 1) * sizeof(char*));
	int i = DefaultListView->CustomFunctionList.count;
	memcpy(DisplayArray, DefaultListView->CustomFunctionList.display,
			DefaultListView->CustomFunctionList.count * sizeof(void*));
	*(DisplayArray + i++) = CommandDisplay[0];
	if (DefaultListView->Option.canEdit)
		*(DisplayArray + i++) = CommandDisplay[1];
	if (DefaultListView->Option.canRemove)
		*(DisplayArray + i++) = CommandDisplay[2];
	*(DisplayArray + i) = NULL;
	LISTBOX_Handle listbox_hwin = LISTBOX_CreateEx(0, 0, 128, 115, hwin,
	WM_CF_SHOW, 0,
	GUI_ID_LISTBOX1, DisplayArray);
	DefaultListView->CurrentWidget = listbox_hwin;

	SetListBoxSkin(listbox_hwin);
	return hwin;
}

static uint8_t OptionListViewHide(GUI_HWIN hWin) {
	vPortFree(DisplayArray);
	return 1;
}

static GUI_HWIN InfoViewShow() {
	WM_HWIN hwin = WINDOW_CreateEx(0, 0, 128, 115, NULL, WM_CF_SHOW, 0x0,
	GUI_ID_USER,
	NULL);
	char temp[33];
	DefaultListView->ApiHandlers->GetDisplay(temp);
	TEXT_Handle text_hwin = TEXT_CreateEx(0, 0, 128, 115, hwin,
	WM_CF_SHOW, 0,
	GUI_ID_LISTBOX0, temp);
	DefaultListView->CurrentWidget = text_hwin;
	return hwin;
}

static uint8_t InfoViewHide(GUI_HWIN hWin) {

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

void EditViewOkCallback(void) {
	DefaultListView->EditProgress(DefaultListView->EditArg,
			DefaultListView->CurrentWidget);
}

void OptionOkCallback(void) {
	uint32_t sel = LISTBOX_GetSel(DefaultListView->CurrentWidget);
	if (sel < DefaultListView->CustomFunctionList.count)
		(*(DefaultListView->CustomFunctionList.function + sel))();
	else {
		char selectedItemText[7];
		LISTBOX_GetItemText(DefaultListView->CurrentWidget,
				LISTBOX_GetSel(DefaultListView->CurrentWidget),
				selectedItemText, 7);
		if (strcmp(selectedItemText, CommandDisplay[0]) == 0) {
			ViewNavigator_GoToViewOf(&DefaultViewNavigator, &ListInfoView);
		} else if (strcmp(selectedItemText, CommandDisplay[1]) == 0) {
			ViewNavigator_GoToViewOf(&DefaultViewNavigator, &ListEditView);
		}
		else if (strcmp(selectedItemText, CommandDisplay[2]) == 0) {
			DefaultListView->ApiHandlers->Remove();
			ViewNavigator_GoBackView(&DefaultViewNavigator);
		}
	}
}










void backCallback(void) {
	ViewNavigator_GoBackView(&DefaultViewNavigator);
}
