/*
 * OptionListView.h
 *
 *  Created on: Dec 16, 2018
 *      Author: HP
 */

#ifndef GUISHELL_VIEWCONTAINER_OPTIONLISTVIEW_H_
#define GUISHELL_VIEWCONTAINER_OPTIONLISTVIEW_H_

#include "MemoryDataContext.h"
#include "View.h"


typedef struct {
	CustomFunction_Typedef **customFunction;
	void (*SelectCallback)(void *);
	LISTBOX_Handle hWin;
} OptionListView_Parameters_Typedef;



#endif /* GUISHELL_VIEWCONTAINER_OPTIONLISTVIEW_H_ */
