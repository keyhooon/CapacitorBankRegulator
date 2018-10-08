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

typedef enum {
	Ok, Cancel, Error,
} ViewStatus_Typedef;



typedef struct {
	void * States;
	void (*OnStateChanged)(int StateNumber);

} ViewState_Typedef;

typedef void * ViewParam_Typedef;

typedef struct {
	uint8_t id;
	const char *name;
	const char *shortName;
	GUI_CONST_STORAGE GUI_BITMAP *icon;
	void (*show)(void);
	uint8_t (*hide)(void);
	void (*okCallback)(void);
	void (*backCallback)(void);
	const ViewParam_Typedef * param;
	ViewState_Typedef * state;
} View_Typedef;


#endif /* VIEWCONTAINER_VIEW_H_ */
