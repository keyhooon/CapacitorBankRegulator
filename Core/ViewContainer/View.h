/*
 * View.h
 *
 *  Created on: Oct 8, 2018
 *      Author: HP
 */

#ifndef VIEWCONTAINER_VIEW_H_
#define VIEWCONTAINER_VIEW_H_

#include "main.h"
#include "wm.h"
#include "dialog.h"

#define DESKTOP_VIEW_ID			0x0
#define MENU_VIEW_ID			0x1
#define CONTACT_LIST_VIEW_ID	0x2
#define CONTACT_OPTION_VIEW_ID	0x21
#define CONTACT_CALL_VIEW_ID	0x211
#define CONTACT_SHOW_VIEW_ID	0x212
#define CONTACT_EDIT_VIEW_ID	0x213






typedef enum {
	Ok, Cancel, Error,
} ViewStatus_Typedef;





typedef struct {
	uint8_t id;
	const char *name;
	const char *shortName;
	GUI_CONST_STORAGE GUI_BITMAP *icon;
	GUI_HWIN (*show)(void);
	uint8_t (*hide)(GUI_HWIN hWin);
	const char* firstButtonText;
	const char* SecondButtonText;
	void (*firstButtonCallback)(void);
	void (*SecondButtonCallback)(void);
	const void * param;
	void * state;
} View_Typedef;


#endif /* VIEWCONTAINER_VIEW_H_ */
