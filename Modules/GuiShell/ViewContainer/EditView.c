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
void StoreValue(EditView_Parameters_Typedef * editView_parameters, WM_HWIN hwin);
void LoadValue(EditView_Parameters_Typedef * editView_parameters, WM_HWIN hwin);






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
				{ TEXT_CreateIndirect, "Text", GUI_ID_TEXT0, 5, 15, 118, 30,
						TEXT_CF_HCENTER | TEXT_CF_VCENTER, 0, 0 }, //
				{ EDIT_CreateIndirect, "Edit", GUI_ID_EDIT0, 5, 50, 118, 30,
						TEXT_CF_HCENTER | TEXT_CF_VCENTER, 0, 0 }, //
		};
static GUI_HWIN EditViewShow(void * parameters) {
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
		if (fieldAttribute->valueType == stringField)
		{
			*(char**) (editView_parameters->buffer
					+ fieldAttribute->offsetInStruct) =
					editView_parameters->buffer + sz;
			sz += fieldAttribute->maxLength + 1;
		}
	}

	LoadValue(editView_parameters, hwin);
	return hwin;
}
static uint8_t EditViewHide(GUI_HWIN hWin, void * parameters) {
	vPortFree(((EditView_Parameters_Typedef *) parameters)->buffer);
	return 0;
}

void EditViewOkCallback(void * parameters) {
	EditView_Parameters_Typedef * editView_parameters =
			(EditView_Parameters_Typedef *) parameters;
	WM_HWIN countainer_hwin = WM_GetFirstChild(
			DefaultViewNavigator.view_container_hWin);
	StoreValue(editView_parameters, countainer_hwin);
	editView_parameters->currentFieldIndex++;
	while (!editView_parameters->fieldAttribute[editView_parameters->currentFieldIndex].editable
			&& editView_parameters->currentFieldIndex
					!= editView_parameters->fieldCount)
		editView_parameters->currentFieldIndex++;
	if (editView_parameters->currentFieldIndex
			== editView_parameters->fieldCount)
	{
		editView_parameters->FinishCallback(editView_parameters);
		ViewNavigator_GoBackView(&DefaultViewNavigator);
	}
	else
		LoadValue(editView_parameters, countainer_hwin);
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
	{
		WM_HWIN countainer_hwin = WM_GetFirstChild(
				DefaultViewNavigator.view_container_hWin);
		LoadValue(editView_parameters, countainer_hwin);
	}
}

void StoreValue(EditView_Parameters_Typedef * editView_parameters,
		WM_HWIN countainer_hwin) {
	FieldAttribute_Typedef *fieldAttribute =
			editView_parameters->fieldAttribute
			+ editView_parameters->currentFieldIndex;
	GUI_HWIN hEditWin = WM_GetDialogItem(countainer_hwin, GUI_ID_EDIT0);

	if (fieldAttribute->valueType == stringField) {
		EDIT_GetText(hEditWin,
				*(char**) (editView_parameters->buffer
						+ fieldAttribute->offsetInStruct),
				fieldAttribute->maxLength);
	} else if (fieldAttribute->valueType == integerField) {
		*(int*) (editView_parameters->buffer
				+ fieldAttribute->offsetInStruct) =
				EDIT_GetValue(hEditWin);
	}
}

void LoadValue(EditView_Parameters_Typedef * editView_parameters,
		WM_HWIN countainer_hwin) {

	GUI_HWIN hEditWin = WM_GetDialogItem(countainer_hwin, GUI_ID_EDIT0);
	GUI_HWIN hTextWin = WM_GetDialogItem(countainer_hwin, GUI_ID_TEXT0);
	FieldAttribute_Typedef *fieldAttribute = editView_parameters->fieldAttribute
			+ editView_parameters->currentFieldIndex;


	TEXT_SetText(hTextWin, fieldAttribute->display);

	EDIT_SetMaxLen(hEditWin, fieldAttribute->maxLength);
	if (fieldAttribute->valueType == stringField) {
		EDIT_SetTextMode(hEditWin);
		if (!editView_parameters->isNew) {
			EDIT_SetText(hEditWin,
					*(char **) ((char *) editView_parameters->editableModel
							+ fieldAttribute->offsetInStruct));
		}
	} else if (fieldAttribute->valueType == integerField) {
		EDIT_SetDecMode(hEditWin, 0, 0, fieldAttribute->maxLength, 0,
		GUI_EDIT_NORMAL);
		if (!editView_parameters->isNew) {
			EDIT_SetValue(hEditWin,
					*(int *) (((char *) editView_parameters->editableModel)
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
		if (fieldAttribute->valueType == stringField) {
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
