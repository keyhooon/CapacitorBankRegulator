/*
 * ViewNavigator.c
 *
 *  Created on: Oct 8, 2018
 *      Author: HP
 */



/* Includes ------------------------------------------------------------------*/
#include "ViewNavigator.h"
#include "dialog.h"

/** @addtogroup CORE
 * @{
 */

/** @defgroup KERNEL_page
 * @brief Kernel page routines
 * @{
 */

/* External variables --------------------------------------------------------*/
/* Private typedef -----------------------------------------------------------*/
/* Private defines -----------------------------------------------------------*/
/* Private macros ------------------------------------------------------------*/

/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/

static uint8_t FindViewLvlByID(ViewNavigatorTypedef *viewNavigator,
		uint8_t viewId);
static uint8_t FindViewLvlByView(ViewNavigatorTypedef *viewNavigator,
		View_Typedef * view);
static uint8_t FindViewIdxByID(ViewNavigatorTypedef *viewNavigator,
		uint8_t pageId);
static uint8_t FindViewIdxByView(ViewNavigatorTypedef *viewNavigator,
		View_Typedef * view);
static uint8_t FindFirstPageIdxEmpty(ViewNavigatorTypedef *viewNavigator);


static void PageShow(ViewNavigatorTypedef *viewNavigator,
		View_Typedef *view);
static uint8_t PageHide(ViewNavigatorTypedef *viewNavigator,
		View_Typedef *view);


/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Page Initialization.
 * @param  None.
 * @retval None
 */
void ViewNavigator_Init(ViewNavigatorTypedef *viewNavigator,
		WM_HWIN containerhWin) {
	viewNavigator->view_container_hWin = containerhWin;
	memset(viewNavigator->registered_view_list, 0,
			sizeof(View_Typedef *) * MAX_VIEW_COUNT);
	viewNavigator->register_view_num = 0;
	memset(viewNavigator->view_route.items, 0,
			sizeof(uint8_t) * DEEPEST_CHAIN_VIEW_COUNT);
	viewNavigator->view_route.currentItemPos = -1;

}
/**
 * @brief  Get the Page number.
 * @param  None.
 * @retval None
 */
uint8_t ViewNavigator_GetViewCount(ViewNavigatorTypedef *viewNavigator) {
	return viewNavigator->register_view_num;
}
/**
 * @brief  Add Page.
 * @param  Page: pointer to data structure of type pageItem_Typedef
 * @retval Page add status
 */
uint8_t ViewNavigator_RegisterView(ViewNavigatorTypedef *viewNavigator,
		View_Typedef *view) {
	uint8_t idx;
	if (viewNavigator->register_view_num < (MAX_VIEW_COUNT - 1)) {
		uint8_t idx = FindViewIdxByView(viewNavigator, view);
		if (idx == 255) {
			idx = FindFirstPageIdxEmpty(viewNavigator);
			viewNavigator->registered_view_list[idx] = view;
			viewNavigator->register_view_num++;
		}
		return idx;
	}
	return 255;
}

/**
 * @brief  Remove Page
 * @param  Page: pointer to data structure of type PageItem_Typedef
 * @retval None
 */

uint8_t ViewNavigator_UnregisterView(ViewNavigatorTypedef *viewNavigator,
		View_Typedef *view) {
	if (ViewNavigator_GetCurrentView(viewNavigator) == view) {
		ViewNavigator_GoBackPage(viewNavigator);
	}
	uint8_t idx = FindViewIdxByView(viewNavigator, view);
	viewNavigator->registered_view_list[idx] = NULL;
	viewNavigator->register_view_num--;
	return idx;
}

/**
 * @brief  Go to Last Page.
 * @param  Page: pointer to data structure of type ViewNavigatorTypedef
 * @retval Done status
 */

uint8_t ViewNavigator_GoBackView(ViewNavigatorTypedef *viewNavigator) {
	if (viewNavigator->view_route.currentItemPos >= 0
			&& PageHide(viewNavigator,
					(viewNavigator->registered_view_list[viewNavigator->view_route.items[viewNavigator->view_route.currentItemPos]]))
					!= 0) {
		if (viewNavigator->view_route.currentItemPos > 0)
			viewNavigator->view_route.currentItemPos--;
		PageShow(viewNavigator,
				viewNavigator->registered_view_list[viewNavigator->view_route.items[viewNavigator->view_route.currentItemPos]]);
		if (viewNavigator->currentViewChanged != NULL)
			viewNavigator->currentViewChanged();
		return viewNavigator->view_route.items[viewNavigator->view_route.currentItemPos];
	}
	return 255;
}
/**
 * @brief  Go to Home Page.
 * @param  Page: pointer to data structure of type ViewNavigatorTypedef
 * @retval Done status
 */

uint8_t ViewNavigator_GoHomeView(ViewNavigatorTypedef *viewNavigator) {
	if (viewNavigator->view_route.currentItemPos >= 0
			&& PageHide(viewNavigator,
					viewNavigator->registered_view_list[viewNavigator->view_route.items[viewNavigator->view_route.currentItemPos]])
					!= 0) {
		viewNavigator->view_route.currentItemPos = 0;
		PageShow(viewNavigator,
				viewNavigator->registered_view_list[viewNavigator->view_route.items[0]]);
		if (viewNavigator->currentViewChanged != NULL)
			viewNavigator->currentViewChanged();
		return 0;
	}
	return 255;
}
/**
 * @brief  Go to Page.
 * @param  ViewNavigatorTypedef: pointer to data structure of type ViewNavigatorTypedef
 * @param  Page: pointer to data structure of type pageItem_Typedef, if page has not registered before, it is registering in this subroutine
 * @retval done status
 */

uint8_t ViewNavigator_GoToViewOf(ViewNavigatorTypedef *viewNavigator,
		View_Typedef * view) {
	uint8_t viewIdx = FindViewIdxByView(viewNavigator, view);
	if (viewIdx == 255)
		viewIdx = ViewNavigator_RegisterView(viewNavigator, view);
	if ((viewNavigator->view_route.currentItemPos == -1)
				|| (viewNavigator->view_route.currentItemPos
						< DEEPEST_CHAIN_VIEW_COUNT - 1
						&& PageHide(viewNavigator,
							viewNavigator->registered_view_list[viewNavigator->view_route.items[viewNavigator->view_route.currentItemPos]]))
					!= 0) {
		viewNavigator->view_route.currentItemPos++;
		viewNavigator->view_route.items[viewNavigator->view_route.currentItemPos] =
				viewIdx;
		PageShow(viewNavigator,
				viewNavigator->registered_view_list[viewIdx]);
		if (viewNavigator->currentViewChanged != NULL)
			viewNavigator->currentViewChanged();
		return viewIdx;
	}
	return 255;
}
/**
 * @brief  Go to Page.
 * @param  viewNavigator: pointer to data structure of type ViewNavigatorTypedef
 * @param  pageId: page Id , page should be register befor call this subroutine
 * @param  param: param is variable value that has been send to destination page
 * @retval done status
 */

uint8_t ViewNavigator_GoToViewOfByID(ViewNavigatorTypedef *viewNavigator,
		uint8_t viewId) {
	uint8_t viewIdx = FindViewIdxByID(viewNavigator, viewId);
	if (viewIdx == 255)
		return viewIdx;
	if (viewNavigator->view_route.currentItemPos < DEEPEST_CHAIN_VIEW_COUNT - 1
			&& PageHide(viewNavigator,
					viewNavigator->registered_view_list[viewNavigator->view_route.items[viewNavigator->view_route.currentItemPos]])
					!= 0) {
		viewNavigator->view_route.currentItemPos++;
		viewNavigator->view_route.items[viewNavigator->view_route.currentItemPos] =
				viewIdx;
		PageShow(viewNavigator,
				viewNavigator->registered_view_list[viewIdx]);
		if (viewNavigator->currentViewChanged != NULL)
			viewNavigator->currentViewChanged();
		return viewIdx;
	}
	return 255;
}
/**
 * @brief  Get Current Page.
 * @param  Page: pointer to data structure of type ViewNavigatorTypedef
 * @param  Page: pointer to data structure of type pageItem_Typedef
 * @retval Page Item
 */

View_Typedef * ViewNavigator_GetCurrentView(
		ViewNavigatorTypedef *viewNavigator) {
	uint8_t Idx =
			viewNavigator->view_route.items[viewNavigator->view_route.currentItemPos];
	return viewNavigator->registered_view_list[Idx];
}

static uint8_t FindViewLvlByID(ViewNavigatorTypedef *viewNavigator,
		uint8_t viewId) {
	for (uint8_t idx = 0; idx < viewNavigator->view_route.currentItemPos;
			idx++) {
		if (viewNavigator->registered_view_list[viewNavigator->view_route.items[idx]]
				!= NULL
				&& viewNavigator->registered_view_list[viewNavigator->view_route.items[idx]]->id
						== viewId) {
			return idx;
		}
	}
	return 255;
}

static uint8_t FindViewLvlByView(ViewNavigatorTypedef *viewNavigator,
		View_Typedef * view) {
	uint8_t idx = 0;

	for (idx = 0; idx < viewNavigator->view_route.currentItemPos; idx++) {
		if (viewNavigator->registered_view_list[viewNavigator->view_route.items[idx]]
				== view) {
			return idx;
		}
	}
	return 255;
}

static uint8_t FindViewIdxByID(ViewNavigatorTypedef *viewNavigator,
		uint8_t pageId) {
	uint8_t idx = 0;

	for (idx = 0; idx < MAX_VIEW_COUNT; idx++) {
		if (viewNavigator->registered_view_list[idx] != NULL
				&& viewNavigator->registered_view_list[idx]->id == pageId) {
			return idx;
		}
	}
	return 255;
}

static uint8_t FindViewIdxByView(ViewNavigatorTypedef *viewNavigator,
		View_Typedef * view) {
	uint8_t idx = 0;

	for (idx = 0; idx < MAX_VIEW_COUNT; idx++) {
		if (viewNavigator->registered_view_list[idx] != NULL
				&& viewNavigator->registered_view_list[idx] == view) {
			return idx;
		}
	}
	return 255;
}


static uint8_t FindFirstPageIdxEmpty(ViewNavigatorTypedef *viewNavigator) {
	uint8_t idx = 0;

	for (idx = 0; idx < MAX_VIEW_COUNT; idx++) {
		if (viewNavigator->registered_view_list[idx] == NULL) {
			return idx;
		}
	}
	return 255;
}

static void PageShow(ViewNavigatorTypedef *viewNavigator,
		View_Typedef * view) {
	if (view->show == NULL)
		return;
	GUI_HWIN hWin = view->show();
	if (hWin != NULL) {
		WM_AttachWindow(hWin, viewNavigator->view_container_hWin);
		WM_SetFocus(hWin);

}
}
	static uint8_t PageHide(ViewNavigatorTypedef *viewNavigator,
			View_Typedef * view) {
		GUI_HWIN hWin = WM_GetFirstChild(viewNavigator->view_container_hWin);
	int ret = 1;
	if (view->hide != NULL)
			ret = view->hide(hWin);
	if (ret) {
			WM_DetachWindow(hWin);
			WM_DeleteWindow(hWin);
	}
	return ret;
}

/**
 * @}
 */

/**
 * @}
 */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
