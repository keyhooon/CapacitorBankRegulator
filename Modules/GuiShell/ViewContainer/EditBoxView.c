/*
 * EditBoxView.c
 *
 *  Created on: Jan 22, 2019
 *      Author: HP
 */

/*********************************************************************
 *
 *       Includes
 *
 **********************************************************************
 */
#include "DIALOG.h"
#include "WM.h"
#include "ViewNavigator.h"
#include "EditView.h"


static GUI_HWIN EditBoxViewShow(void *);
static uint8_t EditBoxViewHide(GUI_HWIN hWin, void *);
void EditBoxViewOkCallback(void *);
void EditBoxViewBackCallback(void *);
const View_Typedef EditBoxView = { EDITBOX_VIEW_ID, "EditBox", "EditBox",
		(void *) NULL, EditBoxViewShow, EditBoxViewHide, (const char*) "Cancel",
		(const char*) "OK", EditBoxViewBackCallback, EditBoxViewOkCallback,
		NULL, 0 };

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = { //
		{ WINDOW_CreateIndirect, "Main Menu", GUI_ID_USER, 0, 0, 128, 115,
		WM_CF_SHOW, 0x0, 0 }, //
				{ TEXT_CreateIndirect, "Text", GUI_ID_TEXT0, 5, 15, 118, 30,
				TEXT_CF_HCENTER | TEXT_CF_VCENTER, 0, 0 }, //
				{ EDIT_CreateIndirect, "Edit", GUI_ID_EDIT0, 5, 50, 118, 30,
				TEXT_CF_HCENTER | TEXT_CF_VCENTER, 0, 0 }, //
		};

static GUI_HWIN EditBoxViewShow(void * parameters) {
	EditView_Parameters_Typedef * editView_parameters =
			(EditView_Parameters_Typedef *) parameters;
	WM_HWIN hwin = GUI_CreateDialogBox(_aDialogCreate,
			GUI_COUNTOF(_aDialogCreate), NULL, NULL, 0, 0);
	GUI_HWIN hEditWin = WM_GetDialogItem(hwin, GUI_ID_EDIT0);
	GUI_HWIN hTextWin = WM_GetDialogItem(hwin, GUI_ID_TEXT0);
	TEXT_SetFont(hTextWin, &GUI_Font16B_ASCII);
	EDIT_SetFont(hEditWin, &GUI_Font13HB_ASCII);

	editView_parameters->currentFieldIndex = 0;
	editView_parameters->buffer = pvPortMalloc(
			CalculateDataModelMaxSizeWithExtra(
					editView_parameters->fieldAttribute,
					editView_parameters->fieldCount));
	int sz = CalculateDataModelSizeWithoutExtra(
			editView_parameters->fieldAttribute,
			editView_parameters->fieldCount);
	for (int i = 0; i < editView_parameters->fieldCount; i++) {
		FieldAttribute_Typedef * fieldAttribute =
				editView_parameters->fieldAttribute + i;
		if (fieldAttribute->valueType == stringField) {
			*(char**) (editView_parameters->buffer
					+ fieldAttribute->offsetInStruct) =
					editView_parameters->buffer + sz;
			sz += fieldAttribute->maxLength + 1;
		}
	}

	LoadValue(editView_parameters, hwin);
	return hwin;
}
static uint8_t EditBoxViewHide(GUI_HWIN hWin, void * parameters) {
	vPortFree(((EditView_Parameters_Typedef *) parameters)->buffer);
	return 0;
}
