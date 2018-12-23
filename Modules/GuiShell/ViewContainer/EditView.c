/*
 * EditView.c
 *
 *  Created on: Oct 7, 2018
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

/*********************************************************************
 *
 *       Static (const) data
 *
 **********************************************************************
 */
void StoreValue(EditView_Parameters_Typedef * editView_parameters);
void LoadValue(EditView_Parameters_Typedef * editView_parameters);






static GUI_HWIN EditViewShow(void *);
static uint8_t EditViewHide(GUI_HWIN hWin, void *);
void EditViewOkCallback(void *);
void EditViewBackCallback(void *);
const View_Typedef EditView = {
EDIT_VIEW_ID, "Edit", "Edit", (void *) NULL, EditViewShow, EditViewHide,
		(const char*) "Cancel", (const char*) "OK", EditViewBackCallback,
		EditViewOkCallback, NULL, 0 };

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = { //
		{ WINDOW_CreateIndirect, "Main Menu", GUI_ID_USER, 0, 0, 128, 115,
				WM_CF_SHOW, 0x0, 0 }, //
				{ TEXT_CreateIndirect, "Text", GUI_ID_TEXT0, 5, 20, 118, 20,
						TEXT_CF_HCENTER | TEXT_CF_VCENTER, 0, 0 }, //
				{ EDIT_CreateIndirect, "Edit", GUI_ID_EDIT0, 5, 60, 128, 20,
						TEXT_CF_HCENTER | TEXT_CF_VCENTER, 0, 0 }, //
		};
static GUI_HWIN EditViewShow(void * parameters) {
	EditView_Parameters_Typedef * editView_parameters =
			(EditView_Parameters_Typedef *) parameters;
	WM_HWIN hwin = GUI_CreateDialogBox(_aDialogCreate,
			GUI_COUNTOF(_aDialogCreate), NULL, NULL, 0, 0);
	editView_parameters->currentFieldIndex = 0;
	int sz = CalculateDataModelSizeWithoutExtra(
			editView_parameters->fieldAttribute,
			editView_parameters->fieldCount);
	for (int i = 0; i < editView_parameters->fieldCount; i++) {
		FieldAttribute_Typedef * fieldAttribute =
				editView_parameters->fieldAttribute + i;
		if (fieldAttribute->type == stringField)
		{
			*(char**) (editView_parameters->buffer
					+ fieldAttribute->offsetInStruct) =
					editView_parameters->buffer + sz;
			sz += fieldAttribute->maxLength + 1;
		}
	}
	editView_parameters->buffer = pvPortMalloc(sz);
	LoadValue(editView_parameters);
	return hwin;
}
static uint8_t EditViewHide(GUI_HWIN hWin, void * parameters) {
	vPortFree(((EditView_Parameters_Typedef *) parameters)->buffer);
	return 0;
}

void EditViewOkCallback(void * parameters) {
	EditView_Parameters_Typedef * editView_parameters =
			(EditView_Parameters_Typedef *) parameters;
	StoreValue(editView_parameters);
	editView_parameters->currentFieldIndex++;
	if (editView_parameters->currentFieldIndex
			== editView_parameters->fieldCount)
	{
		editView_parameters->FinishCallback(editView_parameters);
		ViewNavigator_GoBackView(&DefaultViewNavigator);
	}
	else
		LoadValue(editView_parameters);
}

void EditViewBackCallback(void * parameters) {
	EditView_Parameters_Typedef * editView_parameters =
			(EditView_Parameters_Typedef *) parameters;
	if (editView_parameters->currentFieldIndex-- == 0)
	{
		editView_parameters->CancelCallback(editView_parameters);
		ViewNavigator_GoBackView(&DefaultViewNavigator);
	}
	else
		LoadValue(editView_parameters);
}

void StoreValue(EditView_Parameters_Typedef * editView_parameters) {
	WM_HWIN countainer_hwin = WM_GetFirstChild(
			DefaultViewNavigator.view_container_hWin);
	FieldAttribute_Typedef *fieldAttribute =
			editView_parameters->fieldAttribute
			+ editView_parameters->currentFieldIndex;
	GUI_HWIN hEditWin = WM_GetDialogItem(countainer_hwin, GUI_ID_EDIT0);

	if (fieldAttribute->type == stringField) {
		EDIT_GetText(hEditWin,
				*(char**) (editView_parameters->buffer
						+ fieldAttribute->offsetInStruct),
				fieldAttribute->maxLength);
	} else if (fieldAttribute->type == integerField) {
		*(int*) (editView_parameters->buffer
				+ fieldAttribute->offsetInStruct) =
				EDIT_GetValue(hEditWin);
	}
}

void LoadValue(EditView_Parameters_Typedef * editView_parameters) {
	WM_HWIN countainer_hwin = WM_GetFirstChild(
			DefaultViewNavigator.view_container_hWin);
	GUI_HWIN hEditWin = WM_GetDialogItem(countainer_hwin, GUI_ID_EDIT0);
	FieldAttribute_Typedef *fieldAttribute = editView_parameters->fieldAttribute
			+ editView_parameters->currentFieldIndex;


	TEXT_SetText(WM_GetDialogItem(countainer_hwin, GUI_ID_TEXT0),
			fieldAttribute->display);
	EDIT_SetMaxLen(hEditWin, fieldAttribute->maxLength);
	if (fieldAttribute->type == stringField) {
		EDIT_SetTextMode(hEditWin);
		if (!editView_parameters->isNew) {
			EDIT_SetText(hEditWin,
					(char *) *(((char *) editView_parameters->editableModel)
							+ fieldAttribute->offsetInStruct));
		}
	} else if (fieldAttribute->type == integerField) {
		EDIT_SetDecMode(hEditWin, 0, 0, fieldAttribute->maxLength, 0,
		GUI_EDIT_NORMAL);
		if (!editView_parameters->isNew) {
			EDIT_SetValue(hEditWin,
					(int) *(((char*) editView_parameters->editableModel)
							+ fieldAttribute->offsetInStruct));
		}
	}
}

int CompressEditViewBuffer(EditView_Parameters_Typedef * editView_parameters) {
	int result = editView_parameters->fieldCount * 4;
	char* pField = editView_parameters->buffer + result;
	for (int i = 0; i < editView_parameters->fieldCount; i++) {
		FieldAttribute_Typedef *fieldAttribute =
				editView_parameters->fieldAttribute + i;
		if (fieldAttribute->type == stringField) {
			char * str = *(char**) (editView_parameters->buffer
					+ fieldAttribute->offsetInStruct);
			int len = strlen(str) + 1;
			result += len;
			if (pField != str)
				for (int j = 0; j < len; j++)
					*pField++ = *str++;
		}
	}
	return result;
}
