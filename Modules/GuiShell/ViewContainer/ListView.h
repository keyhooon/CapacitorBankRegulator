/*
 * ListView.h
 *
 *  Created on: Oct 16, 2018
 *      Author: HP
 */

#ifndef VIEWCONTAINER_LISTVIEW_H_
#define VIEWCONTAINER_LISTVIEW_H_

#include "MemoryDataContext.h"
#include "View.h"


typedef struct {
	const CustomFunction_Typedef **customFunction;
	const ListApiHandlers_typedef * apiHandlers;
	void (*SelectCallback)(void *);
	LISTBOX_Handle hWin;
	char** DisplayArray;
} ListView_Parameters_Typedef;



#endif /* VIEWCONTAINER_LISTVIEW_H_ */
