/*
 * ListView.h
 *
 *  Created on: Oct 16, 2018
 *      Author: HP
 */

#ifndef VIEWCONTAINER_LISTVIEW_H_
#define VIEWCONTAINER_LISTVIEW_H_

#include"List_Heap.h"


GUI_HWIN ListViewShow(ListApiHandlers_typedef ListApiHandlers);

typedef struct {
	uint32_t count;
	char ** display;
	void * (*function)(void);
} CustomFunctionList_Typedef;

typedef struct {
	uint32_t canAdd;
	uint32_t canEdit;
	uint32_t canRemove;
} ListViewOption_typedef;

GUI_HWIN currentWidget;

#define SHOW_LIST_PROTOTYPES(type) \
	extern ListApiHandlers_typedef type##ListApiHandlers; \
	extern const ListViewOption_typedef type##ListViewOption; \
	extern const CustomFunctionList_Typedef type##FunctionList; \
	static void SelectOptionCallback(void); \
	GUI_HWIN type##ListViewShow(void); \
	uint8_t type##ListViewHide(GUI_HWIN hWin);\
	GUI_HWIN type##OptionListViewShow(void); \
	uint8_t type##OptionListViewHide(GUI_HWIN hWin);\


#define SHOW_LIST_FUNCTIONS(type) \
		GUI_HWIN type##ListViewShow(void) { \
			return ListViewShow(type##ListApiHandlers); \
		} \
		uint8_t type##ListViewHide(GUI_HWIN hWin) {\
			return ListViewHide(type##ListApiHandlers, hWin);\
		} \
		GUI_HWIN type##OptionListViewShow(void){ \
			return OptionListViewShow(type##ListViewOption, type##FunctionList); \
		}\
		uint8_t type##OptionListViewHide(GUI_HWIN hWin) {\
			return OptionListViewHide(type##ListViewOption, type##FunctionList, hWin);\
		} \
		static void SelectOptionCallback(void) { \
			uint32_t sel = LISTBOX_GetSel(currentWidget);\
			if (sel < type##FunctionList.count)\
				type##FunctionList[sel]();\
			else
		} \


#endif /* VIEWCONTAINER_LISTVIEW_H_ */
