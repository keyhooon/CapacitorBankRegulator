/*
 * ListView.h
 *
 *  Created on: Oct 16, 2018
 *      Author: HP
 */

#ifndef VIEWCONTAINER_LISTVIEW_H_
#define VIEWCONTAINER_LISTVIEW_H_

#include"List_Heap.h"

void backCallback(void);
void ListOkCallback(void);
void EditViewOkCallback(void);
void OptionOkCallback(void);

typedef struct {
	uint32_t count;
	char ** display;
	void (**function)(void);
} CustomFunctionList_Typedef;

typedef struct {
	uint32_t canAdd;
	uint32_t canEdit;
	uint32_t canRemove;
} ListViewOption_typedef;





void ListViewInit(ListApiHandlers_typedef * apiHandlers,
		ListViewOption_typedef option,
		CustomFunctionList_Typedef customFunction, uint32_t sizeOfType,
		void (*editProgress)(void));

void ListViewDeInit(void);






#endif /* VIEWCONTAINER_LISTVIEW_H_ */
