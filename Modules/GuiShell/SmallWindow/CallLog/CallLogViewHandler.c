/*
 * CallLogDLG.c
 *
 *  Created on: Oct 27, 2018
 *      Author: HP
 */


#include "WM.h"
#include "DIALOG.h"

#include "ViewContainer/ViewNavigator.h"
#include "MemoryDataContext.h"

#include "CallLog.h"

#include "ViewContainer/ListView.h"
#include "ViewContainer/OptionListView.h"
#include "ViewContainer/EditView.h"
#include "ViewContainer/InfoView.h"

#include "Api/3GPP_TS2705.h"
#include "Api/3GPP_TS2707.h"








/*********************************************************************
 *
 *       Defines
 *
 **********************************************************************
 */
#define ID_WINDOW_02     (GUI_ID_USER + 0x10)
#define ID_LISTBOX_0     (GUI_ID_USER + 0x11)

extern GUI_CONST_STORAGE GUI_BITMAP bmloupe;
extern GUI_CONST_STORAGE GUI_BITMAP bmdelete;

void InitCallLogView(void);

static void CallLogViewFunctionCallBcak(void);
static void CallLogDeleteFunctionCallback(void);
static void CallLogSelectCallback(void);

extern ListApiHandlers_typedef ContactListApiHandlers;
extern ListApiHandlers_typedef CallLogListApiHandlers;




extern View_Typedef ListView;
extern View_Typedef OptionListView;
extern View_Typedef InfoView;

static const CustomFunction_Typedef * CallLogListFunctionList[1] = { NULL };
static ListView_Parameters_Typedef CallLogListView_Parameters = { //
		CallLogListFunctionList, // custom function list
				&CallLogListApiHandlers,  // list api handler
				CallLogSelectCallback, // list select callback
				0, // not document
				0 // not document
		};


static const CustomFunction_Typedef ViewFunction = { &bmloupe,
		(const char*) "View",
		CallLogViewFunctionCallBcak };
static const CustomFunction_Typedef DeleteFunction = { &bmdelete,
		(const char*) "Delete", CallLogDeleteFunctionCallback };
static const CustomFunction_Typedef * CallLogOptionFunctionList[3] = {
		&ViewFunction, &DeleteFunction, NULL };
static OptionListView_Parameters_Typedef CallLogOptionListView_Parameters = { //
		CallLogOptionFunctionList, // custom function list
				0, // option select callback
				0, // not document
		};


static InfoView_Parameters_Typedef CallLogInfoView_Parameters = { //
		&CallLogListApiHandlers // list api handler
		};



void InitCallLogView() {
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &ListView,
			&CallLogListView_Parameters);
}
static void CallLogSelectCallback(void) {
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &OptionListView,
			&CallLogOptionListView_Parameters);
}

static void CallLogViewFunctionCallBcak(void) {
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &InfoView,
			&CallLogInfoView_Parameters);
}
static void CallLogDeleteFunctionCallback(void) {
	CallLogListApiHandlers.RemoveCurrent();
	ViewNavigator_GoBackView(&DefaultViewNavigator);
}



