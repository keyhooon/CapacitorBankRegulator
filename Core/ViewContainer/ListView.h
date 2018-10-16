/*
 * ListView.h
 *
 *  Created on: Oct 16, 2018
 *      Author: HP
 */

#ifndef VIEWCONTAINER_LISTVIEW_H_
#define VIEWCONTAINER_LISTVIEW_H_


#define SHOW_LIST_PROTOTYPES(type) \
	extern type##_List_Typedef * type##List; \
	GUI_HWIN type##ListViewShow(void) { \
		return GUI_CreateDialogBox(_aDialogCreate, GUI_COUNTOF(_aDialogCreate), \
			_cbDialog, WM_HBKWIN, 0, 0); \
	}


#endif /* VIEWCONTAINER_LISTVIEW_H_ */
