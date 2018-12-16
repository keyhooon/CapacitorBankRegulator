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



void ProcessEditView(EditView_Parameters_Typedef * editView_parameters);
static GUI_HWIN EditViewShow(void *);
static uint8_t EditViewHide(GUI_HWIN hWin, void *);
void EditViewOkCallback(void *);
void EditViewBackCallback(void *);
const View_Typedef ListEditView = {
EDIT_VIEW_ID, "Edit", "Edit", (void *) NULL, EditViewShow, EditViewHide,
		(const char*) "Cancel", (const char*) "OK", EditViewBackCallback,
		EditViewOkCallback, NULL, 0 };

static const GUI_WIDGET_CREATE_INFO _aDialogCreate[] = { //
		{ WINDOW_CreateIndirect, "Main Menu", GUI_ID_USER, 0, 0, 128, 115, 0,
				0x0, 0 }, //
				{ TEXT_CreateIndirect, "Text", GUI_ID_TEXT0, 5, 20, 118, 20,
						TEXT_CF_HCENTER | TEXT_CF_VCENTER, 0, 0 }, //
				{ EDIT_CreateIndirect, "Edit", GUI_ID_EDIT0, 5, 60, 128, 20,
						TEXT_CF_HCENTER | TEXT_CF_VCENTER, 0, 0 }, //
		};
static GUI_HWIN EditViewShow(void * parameters) {
	EditView_Parameters_Typedef * editView_parameters =
			(EditView_Parameters_Typedef *) parameters;
	editView_parameters->currentFieldIndex = 0;
	WM_HWIN hwin = GUI_CreateDialogBox(_aDialogCreate,
			GUI_COUNTOF(_aDialogCreate), NULL, NULL, 0, 0);
	ProcessEditView(editView_parameters);
	return hwin;
}
static uint8_t EditViewHide(GUI_HWIN hWin, void * parameters) {
	vPortFree(DefaultListView->EditArg);
	return 1;
}

void EditViewOkCallback(void * parameters) {
	EditView_Parameters_Typedef * listView_parameters =
			(EditView_Parameters_Typedef *) parameters;
	listView_parameters->currentFieldIndex++;
	if (listView_parameters->currentFieldIndex
			== listView_parameters->fieldCount)
		listView_parameters->FinishCallback();
}

void EditViewBackCallback(void * parameters) {
	EditView_Parameters_Typedef * listView_parameters =
			(EditView_Parameters_Typedef *) parameters;
	if (listView_parameters->currentFieldIndex-- == 0)
		ViewNavigator_GoBackView(&DefaultViewNavigator);
}
void ProcessEditView(EditView_Parameters_Typedef * editView_parameters) {
	WM_HWIN countainer_hwin = WM_GetFirstChild(
			DefaultViewNavigator.view_container_hWin);
	FieldAttribute_Typedef
	TEXT_SetText(WM_GetDialogItem(countainer_hwin, GUI_ID_TEXT0),
			editView_parameters->fieldAttribute[editView_parameters->currentFieldIndex].display);

	EDIT_SetText(WM_GetDialogItem(countainer_hwin, GUI_ID_EDIT0),
			(((char*) editView_parameters->editableModel)
					+ editView_parameters->fieldAttribute[editView_parameters->currentFieldIndex].offsetInStruct));

}
