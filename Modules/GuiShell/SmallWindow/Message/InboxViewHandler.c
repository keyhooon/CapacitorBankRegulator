/*
 * MessageDLG.c
 *
 *  Created on: Oct 27, 2018
 *      Author: HP
 */


#include "WM.h"
#include "DIALOG.h"

#include "ViewContainer/ViewNavigator.h"
#include "MemoryDataContext.h"

#include "Message.h"

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

extern GUI_CONST_STORAGE GUI_BITMAP bmmessageforward;
extern GUI_CONST_STORAGE GUI_BITMAP bmmessagereply;
extern GUI_CONST_STORAGE GUI_BITMAP bmloupe;
extern GUI_CONST_STORAGE GUI_BITMAP bmdelete;

void InitMessageView(void);
static void MessageForwardFunctionCallback(void);
static void MessageReplyFunctionCallback(void);
static void MessageViewFunctionCallBcak(void);
static void MessageDeleteFunctionCallback(void);
static void MessageAddFunctionCallback(void);
static void MessageEditFinishedCallback(void *);
static void MessageEditCancelCallback(void *);
static void MessageSelectCallback(void);

extern ListApiHandlers_typedef ContactListApiHandlers;
extern ListApiHandlers_typedef MessageListApiHandlers;




extern View_Typedef ListView;
extern View_Typedef EditView;
extern View_Typedef OptionListView;
extern View_Typedef InfoView;

static const CustomFunction_Typedef AddFunction = { NULL, "Add New...",
		MessageAddFunctionCallback };
static const CustomFunction_Typedef * MessageListFunctionList[2] =
		{ &AddFunction, NULL };
static ListView_Parameters_Typedef MessageListView_Parameters = { //
		MessageListFunctionList, // custom function list
				&MessageListApiHandlers,  // list api handler
				MessageSelectCallback, // list select callback
				0, // not document
				0 // not document
		};


static const CustomFunction_Typedef ReplyFunction = { &bmmessagereply,
		(const char*) "Reply", MessageReplyFunctionCallback };
static const CustomFunction_Typedef ForwardFunction = { &bmmessageforward,
		(const char*) "Forward", MessageReplyFunctionCallback };
static const CustomFunction_Typedef ViewFunction = { &bmloupe,
		(const char*) "View",
		MessageViewFunctionCallBcak };
static const CustomFunction_Typedef DeleteFunction = { &bmdelete,
		(const char*) "Delete", MessageDeleteFunctionCallback };
static const CustomFunction_Typedef * MessageOptionFunctionList[5] = {
		&ReplyFunction,
		&ForwardFunction, &ViewFunction, &DeleteFunction, NULL };
static OptionListView_Parameters_Typedef MessageOptionListView_Parameters = { //
		MessageOptionFunctionList, // custom function list
				0, // option select callback
				0, // not document
		};


static EditView_Parameters_Typedef MessageEditView_Parameters = { //
		&MessageFieldsAttribute, //
				MessageEditFinishedCallback, // Finished Edit Callback
				MessageEditCancelCallback, // Canceled Edit Callback
				MESSAGE_FIELD_COUNT, // Number of contact model field
				0, //
				0, //
				0, //
		};

static InfoView_Parameters_Typedef MessageInfoView_Parameters = { //
		&MessageListApiHandlers // list api handler
		};



void InitMessageView() {
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &ListView,
			&MessageListView_Parameters);
}
static void MessageSelectCallback(void) {
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &OptionListView,
			&MessageOptionListView_Parameters);
}

static void MessageForwardFunctionCallback(void) {

}
static void MessageReplyFunctionCallback(void) {

}
static void MessageViewFunctionCallBcak(void) {
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &InfoView,
			&MessageInfoView_Parameters);
}
static void MessageDeleteFunctionCallback(void) {
	MessageListApiHandlers.RemoveCurrent();
	ViewNavigator_GoBackView(&DefaultViewNavigator);
}
static void MessageAddFunctionCallback(void) {
	MessageEditView_Parameters.isNew = 1;
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &EditView,
			&MessageEditView_Parameters);
}
static void MessageEditFinishedCallback(void *parameters) {
	EditView_Parameters_Typedef *param =
			(EditView_Parameters_Typedef *) parameters;
	Message_Typedef* buffer = (Message_Typedef*) (param->buffer);
	AddMessageEx(buffer->Content, buffer->CallNumber, buffer->Time,
			buffer->IsSuccessfully, buffer->IsIncoming);
}
static void MessageEditCancelCallback(void *parameters) {

}

