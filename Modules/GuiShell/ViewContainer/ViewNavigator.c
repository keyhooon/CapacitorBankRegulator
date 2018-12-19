/*
 * ViewNavigator.c
 *
 *  Created on: Oct 8, 2018
 *      Author: HP
 */



/* Includes ------------------------------------------------------------------*/
#include "ViewNavigator.h"
#include "dialog.h"



View_Navigator_Typedef DefaultViewNavigator;

static void * GetCurrentViewParameter(View_Navigator_Typedef *viewNavigator);
static uint8_t FindLoadedViewIndexByID(View_Navigator_Typedef *viewNavigator,
		uint8_t id);
static uint8_t FindLoadedViewIndex(View_Navigator_Typedef *viewNavigator,
		View_Typedef * view);
static uint8_t FindRegisterViewIndexByID(View_Navigator_Typedef *viewNavigator,
		uint8_t pageId);
static uint8_t FindRegisterViewIndex(View_Navigator_Typedef *viewNavigator,
		View_Typedef * view);
static uint8_t FindRegisteredListFreeIndex(
		View_Navigator_Typedef *viewNavigator);


static GUI_HWIN PageShow(View_Navigator_Typedef *viewNavigator,
		View_Typedef *view);
static uint8_t PageHide(View_Navigator_Typedef *viewNavigator,
		View_Typedef *view);


/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Page Initialization.
 * @param  None.
 * @retval None
 */
void ViewNavigator_Init(View_Navigator_Typedef *viewNavigator,
		WM_HWIN containerhWin) {
	viewNavigator->view_container_hWin = containerhWin;
	viewNavigator->current_Loaded_View_Index = -1;
	memset(viewNavigator->registered_View_List, 0,
			sizeof(View_Typedef *) * MAX_VIEW_COUNT);
	memset(viewNavigator->loaded_View_List, 0,
			sizeof(Loaded_View_TypeDef) * DEEPEST_CHAIN_VIEW_COUNT);
}

/**
 * @brief  Add Page.
 * @param  Page: pointer to data structure of type pageItem_Typedef
 * @retval Page add status
 */
uint8_t ViewNavigator_RegisterView(View_Navigator_Typedef *viewNavigator,
		View_Typedef *view) {

	if (FindRegisterViewIndex(viewNavigator, view) != 255)
		return -1;
	uint8_t idx = FindRegisteredListFreeIndex(viewNavigator);
	if (idx == 255)
		return -1;
	viewNavigator->registered_View_List[idx].view = view;
	return 0;
}

/**
 * @brief  Remove Page
 * @param  Page: pointer to data structure of type PageItem_Typedef
 * @retval None
 */

uint8_t ViewNavigator_UnregisterView(View_Navigator_Typedef *viewNavigator,
		View_Typedef *view) {
	uint8_t registeredViewIndex = FindRegisterViewIndex(viewNavigator, view);
	if (registeredViewIndex == 255)
		return -1;
	if (FindLoadedViewIndex(viewNavigator, view) != 255)
		return -1;

	viewNavigator->registered_View_List[registeredViewIndex].view = NULL;
	return 0;
}

/**
 * @brief  Go to Last Page.
 * @param  Page: pointer to data structure of type View_Navigator_Typedef
 * @retval Done status
 */

GUI_HWIN ViewNavigator_GoBackView(View_Navigator_Typedef *viewNavigator) {
	if (viewNavigator->current_Loaded_View_Index
			<= 0|| viewNavigator->current_Loaded_View_Index >= DEEPEST_CHAIN_VIEW_COUNT)
		return GUI_HMEM_NULL;
	if (PageHide(viewNavigator, ViewNavigator_GetCurrentView(viewNavigator))
			== 0) {
		if (viewNavigator->current_Loaded_View_Index > 0)
			viewNavigator->current_Loaded_View_Index--;
		GUI_HWIN hWin = PageShow(viewNavigator,
				ViewNavigator_GetCurrentView(viewNavigator));
		if (viewNavigator->currentViewChanged != NULL)
			viewNavigator->currentViewChanged();
		return hWin;
	}
	return GUI_HMEM_NULL;
}
/**
 * @brief  Go to Home Page.
 * @param  Page: pointer to data structure of type View_Navigator_Typedef
 * @retval Done status
 */

GUI_HWIN ViewNavigator_GoHomeView(View_Navigator_Typedef *viewNavigator) {
	if (PageHide(viewNavigator, ViewNavigator_GetCurrentView(viewNavigator))
			== 0) {
		viewNavigator->current_Loaded_View_Index = 0;
		GUI_HWIN hWin = PageShow(viewNavigator,
				ViewNavigator_GetCurrentView(viewNavigator));
		if (viewNavigator->currentViewChanged != NULL)
			viewNavigator->currentViewChanged();
		return hWin;
	}
	return GUI_HMEM_NULL;
}
/**
 * @brief  Go to Page.
 * @param  View_Navigator_Typedef: pointer to data structure of type View_Navigator_Typedef
 * @param  Page: pointer to data structure of type pageItem_Typedef, if page has not registered before, it is registering in this subroutine
 * @retval done status
 */

GUI_HWIN ViewNavigator_GoToViewOf(View_Navigator_Typedef *viewNavigator,
		View_Typedef * view, void * parameter) {
	uint8_t index = FindRegisterViewIndex(viewNavigator, view);
	if (index == 255) {
		ViewNavigator_RegisterView(viewNavigator, view);
		index = FindRegisterViewIndex(viewNavigator, view);
	}
	if (((viewNavigator->current_Loaded_View_Index
			< DEEPEST_CHAIN_VIEW_COUNT - 1)
			&& PageHide(viewNavigator,
					ViewNavigator_GetCurrentView(viewNavigator)) == 0)
			|| viewNavigator->current_Loaded_View_Index == 0xff) {
		viewNavigator->loaded_View_List[++viewNavigator->current_Loaded_View_Index].index =
				index;
		viewNavigator->loaded_View_List[viewNavigator->current_Loaded_View_Index].parameter =
				parameter;
		GUI_HWIN hWin = PageShow(viewNavigator,
				ViewNavigator_GetCurrentView(viewNavigator));
		if (viewNavigator->currentViewChanged != NULL)
			viewNavigator->currentViewChanged();
		return hWin;
	}
	return GUI_HMEM_NULL;
}
/**
 * @brief  Go to Page.
 * @param  viewNavigator: pointer to data structure of type View_Navigator_Typedef
 * @param  pageId: page Id , page should be register befor call this subroutine
 * @param  param: param is variable value that has been send to destination page
 * @retval done status
 */

GUI_HWIN ViewNavigator_GoToViewOfByID(View_Navigator_Typedef *viewNavigator,
		uint8_t viewId, void * parameter) {
	uint8_t index = FindRegisterViewIndexByID(viewNavigator, viewId);
	if (index == 255)
		return GUI_HMEM_NULL;
	if (((viewNavigator->current_Loaded_View_Index
			< DEEPEST_CHAIN_VIEW_COUNT - 1)
			&& PageHide(viewNavigator,
					ViewNavigator_GetCurrentView(viewNavigator))
					== 0)
			|| viewNavigator->current_Loaded_View_Index == 0xff) {
		viewNavigator->loaded_View_List[++viewNavigator->current_Loaded_View_Index].index =
				index;
		viewNavigator->loaded_View_List[viewNavigator->current_Loaded_View_Index].parameter =
				parameter;
		GUI_HWIN hWin = PageShow(viewNavigator,
				ViewNavigator_GetCurrentView(viewNavigator));
		if (viewNavigator->currentViewChanged != NULL)
			viewNavigator->currentViewChanged();
		return hWin;
	}
	return GUI_HMEM_NULL;
}
/**
 * @brief  Get Current Page.
 * @param  Page: pointer to data structure of type View_Navigator_Typedef
 * @param  Page: pointer to data structure of type pageItem_Typedef
 * @retval Page Item
 */

View_Typedef * ViewNavigator_GetCurrentView(
		View_Navigator_Typedef *viewNavigator) {
	uint8_t index =
			viewNavigator->loaded_View_List[viewNavigator->current_Loaded_View_Index].index;
	return viewNavigator->registered_View_List[index].view;
}
/**
 * @brief  Get Current Page.
 * @param  Page: pointer to data structure of type View_Navigator_Typedef
 * @param  Page: pointer to data structure of type pageItem_Typedef
 * @retval Page Item
 */

void ViewNavigator_FirstButton_Clicked(View_Navigator_Typedef *viewNavigator) {
	View_Typedef * view = ViewNavigator_GetCurrentView(viewNavigator);
	if (view->firstButtonCallback != NULL)
		view->firstButtonCallback(GetCurrentViewParameter(viewNavigator));
}

/**
 * @brief  Get Current Page.
 * @param  Page: pointer to data structure of type View_Navigator_Typedef
 * @param  Page: pointer to data structure of type pageItem_Typedef
 * @retval Page Item
 */

void ViewNavigator_SecondButton_Clicked(View_Navigator_Typedef *viewNavigator) {
	View_Typedef * view = ViewNavigator_GetCurrentView(viewNavigator);
	if (view->secondButtonCallback != NULL)
		view->secondButtonCallback(GetCurrentViewParameter(viewNavigator));
}





static void * GetCurrentViewParameter(View_Navigator_Typedef *viewNavigator) {
	return viewNavigator->loaded_View_List[viewNavigator->current_Loaded_View_Index].parameter;
}


static uint8_t FindLoadedViewIndexByID(View_Navigator_Typedef *viewNavigator,
		uint8_t id) {
	uint8_t idx;
	for (idx = 0; idx < viewNavigator->current_Loaded_View_Index; idx++) {
		if (viewNavigator->registered_View_List[viewNavigator->loaded_View_List[idx].index].view
				!= NULL
				&& viewNavigator->registered_View_List[viewNavigator->loaded_View_List[idx].index].view->id
						== id) {
			return idx;
		}
	}
	return 255;
}

static uint8_t FindLoadedViewIndex(View_Navigator_Typedef *viewNavigator,
		View_Typedef * view) {
	uint8_t idx = 0;

	for (idx = 0; idx <= viewNavigator->current_Loaded_View_Index; idx++) {
		if (viewNavigator->registered_View_List[viewNavigator->loaded_View_List[idx].index].view
				== view) {
			return idx;
		}
	}
	return 255;
}

static uint8_t FindRegisterViewIndexByID(View_Navigator_Typedef *viewNavigator,
		uint8_t id) {
	uint8_t idx = 0;

	for (idx = 0; idx < MAX_VIEW_COUNT; idx++) {
		if (viewNavigator->registered_View_List[idx].view != NULL
				&& viewNavigator->registered_View_List[idx].view->id == id) {
			return idx;
		}
	}
	return 255;
}

static uint8_t FindRegisterViewIndex(View_Navigator_Typedef *viewNavigator,
		View_Typedef * view) {
	uint8_t idx = 0;

	for (idx = 0; idx < MAX_VIEW_COUNT; idx++) {
		if (viewNavigator->registered_View_List[idx].view == view) {
			return idx;
		}
	}
	return 255;
}


static uint8_t FindRegisteredListFreeIndex(
		View_Navigator_Typedef *viewNavigator) {
	return FindRegisterViewIndex(viewNavigator, NULL);
}

static GUI_HWIN PageShow(View_Navigator_Typedef *viewNavigator,
		View_Typedef * view) {
	if (view->show == NULL)
		return GUI_HMEM_NULL;
	GUI_HWIN hWin = view->show(GetCurrentViewParameter(viewNavigator));
	if (hWin != 0) {
		WM_AttachWindow(hWin, viewNavigator->view_container_hWin);
		WM_SetFocus(hWin);
	}
	return hWin;
}
static uint8_t PageHide(View_Navigator_Typedef *viewNavigator,
			View_Typedef * view) {
GUI_HWIN hWin = WM_GetFirstChild(viewNavigator->view_container_hWin);
	if (view->hide == NULL
			|| view->hide(hWin, GetCurrentViewParameter(viewNavigator)) == 0) {
	WM_DetachWindow(hWin);
	WM_DeleteWindow(hWin);
	return 0;
}
return -1;
}

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
