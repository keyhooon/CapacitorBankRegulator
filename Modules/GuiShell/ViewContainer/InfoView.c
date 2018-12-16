/*
 * InfoView.c
 *
 *  Created on: Oct 7, 2018
 *      Author: HP
 */

#include "DIALOG.h"
#include "WM.h"
#include "ViewNavigator.h"
#include "ListView.h"

static GUI_HWIN InfoViewShow();
static uint8_t InfoViewHide(GUI_HWIN hWin);
const View_Typedef ListInfoView = {
INFO_VIEW_ID, "View", "View", (void *) NULL, InfoViewShow, InfoViewHide,
NULL, (const char*) "Back", NULL, backCallback, NULL, 0 };

static GUI_HWIN InfoViewShow(void * parameters) {
	ListView_Parameters_Typedef * listView_parameters =
			(ListView_Parameters_Typedef *) parameters;
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

static uint8_t InfoViewHide(GUI_HWIN hWin, void * parameters) {
	return 1;
}

void InfoViewbackCallback(void * parameters) {
	ViewNavigator_GoBackView(&DefaultViewNavigator);
}
