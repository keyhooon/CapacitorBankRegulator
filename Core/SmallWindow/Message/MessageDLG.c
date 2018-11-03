/*
 * MessageDLG.c
 *
 *  Created on: Oct 27, 2018
 *      Author: HP
 */


#include "ViewNavigator.h"
#include "WM.h"
#include "DIALOG.h"
#include "Message.h"
#include "ListView.h"

/*********************************************************************
 *
 *       Defines
 *
 **********************************************************************
 */
#define ID_WINDOW_02     (GUI_ID_USER + 0x10)
#define ID_LISTBOX_0     (GUI_ID_USER + 0x11)

void InitMessageView(void);

static void Forward(void);
static void Reply(void);

static GUI_HWIN ReplyViewShow();
static uint8_t ReplyViewHide(GUI_HWIN hWin);
static void ReplyOkCallback(void);
static GUI_HWIN ForwardViewShow();
static uint8_t ForwardViewHide(GUI_HWIN hWin);
static void ForwardOkCallback(void);
static void backCallback(void);

CustomFunction_Typedef * MessageFunctionList[5];
static void EditMessageProgress(void * arg, GUI_HWIN currentWidget);

extern ListApiHandlers_typedef MessageListApiHandlers;
extern View_Typedef ListView;

static const CustomFunction_Typedef ForwardFunction = {
NULL, (const char*) "Forward", Forward };
static const CustomFunction_Typedef ReplyFunction = {
NULL, (const char*) "Reply", Reply };

GUI_HWIN currentWidget;

typedef enum {
	EditMessageState_Content,
	EditMessageState_CallNumber,
	EditMessageState_Finished,
} EditMessageState_Typedef;

const View_Typedef ForwardView = {
EDIT_VIEW_ID, "Forward", "Forward", (void *) NULL, ForwardViewShow,
		ForwardViewHide,
		(const char*) "Cancel", (const char*) "Send", backCallback,
		ForwardOkCallback, NULL, 0 };

const View_Typedef ReplyView = {
EDIT_VIEW_ID, "Reply", "Reply", (void *) NULL, ReplyViewShow, ReplyViewHide,
		(const char*) "Cancel", (const char*) "Send", backCallback,
		ReplyOkCallback, NULL, 0 };


void InitMessageView() {
	MessageFunctionList[0] = &ForwardFunction;
	MessageFunctionList[1] = &ReplyFunction;
	MessageFunctionList[2] = &ViewInfoFunction;
	MessageFunctionList[3] = &DeleteFunction;
	MessageFunctionList[4] = NULL;
	ListViewInit(&MessageListApiHandlers,
			MessageFunctionList, sizeof(Message_Typedef), EditMessageProgress);
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &ListView);
}

static void Forward(void) {
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &ForwardView);
}

static void Reply(void) {
	ViewNavigator_GoToViewOf(&DefaultViewNavigator, &ReplyView);
}


static void EditMessageProgress(void * arg, GUI_HWIN currentWidget) {
	uint32_t len;
	Message_Typedef *Message = arg;
	EditMessageState_Typedef *state = arg + sizeof(Message_Typedef);
	if (*state == EditMessageState_Content) {

		GUI_HWIN editHwin = MULTIEDIT_Create(5, 65, 118, 40, currentWidget,
		GUI_ID_MULTIEDIT0, WM_CF_SHOW, 0, (Message)->Content, 255);
//		TEXT_SetText(textHwin, "Content");

//		MULTIEDIT_SetText(editHwin, (Message)->Content);

		*state = EditMessageState_CallNumber;
	} else if (*state == EditMessageState_CallNumber) {
		GUI_HWIN editHwin = WM_GetDialogItem(currentWidget, GUI_ID_MULTIEDIT0);
		GUI_HWIN textHwin = TEXT_CreateAsChild(5, 20, 118, 40, currentWidget,
				GUI_ID_TEXT0, WM_CF_SHOW, "Call Number",
				TEXT_CF_TOP | TEXT_CF_HCENTER);
		len = EDIT_GetNumChars(editHwin);
		if (Message->Content != NULL)
			vPortFree(Message->Content);
		Message->Content = pvPortMalloc(len + 1);
		MULTIEDIT_GetText(editHwin, (Message)->CallNumber, len + 1);
		WM_DeleteWindow(editHwin);

		editHwin = EDIT_CreateAsChild(5, 65, 118, 40, currentWidget,
				GUI_ID_EDIT0, WM_CF_SHOW, 15);
		TEXT_SetText(textHwin, "Call Number");

		EDIT_SetText(editHwin, (Message)->CallNumber);

		*state = EditMessageState_Finished;
	} else if (*state == EditMessageState_Finished) {
		GUI_HWIN editHwin = WM_GetDialogItem(currentWidget, GUI_ID_EDIT0);
		len = EDIT_GetNumChars(editHwin);
		if (Message->CallNumber != NULL)
			vPortFree(Message->CallNumber);
		Message->CallNumber = pvPortMalloc(len + 1);
		EDIT_GetText(editHwin, (Message)->CallNumber, len + 1);

		memcpy(&MessageList->current_item, Message, sizeof(Message_Typedef));
		ViewNavigator_GoBackView(&DefaultViewNavigator);
		ViewNavigator_GoBackView(&DefaultViewNavigator);
		*state = EditMessageState_Content;
	}
}

static GUI_HWIN ForwardViewShow(void) {
	int xSize, ySize;
	WM_HWIN hwin = WINDOW_CreateEx(0, 0, 128, 115, NULL, WM_CF_SHOW, 0x0,
			GUI_ID_USER, NULL);
	GUI_HWIN textHwin = TEXT_CreateAsChild(5, 20, 118, 40, hwin, GUI_ID_TEXT0,
			WM_CF_SHOW, "Call Number", TEXT_CF_TOP | TEXT_CF_HCENTER);
	currentWidget = EDIT_CreateAsChild(5, 65, 118, 40, hwin, GUI_ID_EDIT0,
			WM_CF_SHOW, 15);

	return hwin;
}
static uint8_t ForwardViewHide(GUI_HWIN hWin) {
	return 1;
}

static void ForwardOkCallback(void) {
	ViewNavigator_GoBackView(&DefaultViewNavigator);
}

static GUI_HWIN ReplyViewShow(void) {
	int xSize, ySize;
	WM_HWIN hwin = WINDOW_CreateEx(0, 0, 128, 115, NULL, WM_CF_SHOW, 0x0,
			GUI_ID_USER, NULL);

	currentWidget = MULTIEDIT_Create(5, 15, 118, 80, hwin,
			GUI_ID_MULTIEDIT0, WM_CF_SHOW, 0, 0, 255);

	return hwin;
}
static uint8_t ReplyViewHide(GUI_HWIN hWin) {
	return 1;
}

static void ReplyOkCallback(void) {
	ViewNavigator_GoBackView(&DefaultViewNavigator);
}


static void backCallback(void) {
	ViewNavigator_GoBackView(&DefaultViewNavigator);
}

