/*
 * ListView.h
 *
 *  Created on: Oct 16, 2018
 *      Author: HP
 */

#ifndef VIEWCONTAINER_LISTVIEW_H_
#define VIEWCONTAINER_LISTVIEW_H_

#include "MemoryDataContext.h"

typedef struct {
	GUI_BITMAP * Icon;
	char * display;
	void (*function)(void);
} CustomFunction_Typedef;

typedef struct {
	uint32_t canAdd;
	uint32_t canEdit;
	uint32_t canRemove;
} ListViewOption_typedef;

extern CustomFunction_Typedef EditFunction;
extern CustomFunction_Typedef DeleteFunction;
extern CustomFunction_Typedef ViewInfoFunction;


void ListViewInit(ListApiHandlers_typedef * apiHandlers,
		CustomFunction_Typedef **customFunction, uint32_t sizeOfType,
		void (*editProgress)(void));

void ListViewDeInit(void);






#endif /* VIEWCONTAINER_LISTVIEW_H_ */
