/*
 * InfoView.c
 *
 *  Created on: Oct 7, 2018
 *      Author: HP
 */

#include "DIALOG.h"
#include "WM.h"
#include "ViewNavigator.h"
#include "InfoView.h"

static GUI_HWIN InfoViewShow(void * parameters);
static uint8_t InfoViewHide(GUI_HWIN hWin, void * parameters);
static void InfoViewbackCallback(void * parameters);

const View_Typedef InfoView = {
INFO_VIEW_ID, "View", "View", (void *) NULL, InfoViewShow, InfoViewHide,
NULL, (const char*) "Back", NULL, InfoViewbackCallback, NULL, 0 };

static GUI_HWIN InfoViewShow(void * parameters) {
	WM_HWIN hwin = WINDOW_CreateEx(0, 0, 128, 115, NULL, WM_CF_SHOW, 0x0,
	GUI_ID_USER, NULL);
	char temp[33];
	((InfoView_Parameters_Typedef *) parameters)->apiHandlers->GetDisplay(temp);
	TEXT_Handle text_hwin = TEXT_CreateEx(5, 5, 118, 115, hwin, WM_CF_SHOW, 0,
	GUI_ID_TEXT0, temp);
	TEXT_SetFont(text_hwin, &GUI_Font8x10_ASCII);
	TEXT_SetWrapMode(text_hwin, GUI_WRAPMODE_WORD);
	return hwin;
}

static uint8_t InfoViewHide(GUI_HWIN hWin, void * parameters) {
	return 0;
}

static void InfoViewbackCallback(void * parameters) {
	ViewNavigator_GoBackView(&DefaultViewNavigator);
}
