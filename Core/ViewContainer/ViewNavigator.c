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
static uint8_t ExistViewVerify(ViewNavigatorTypedef *viewNavigator,
		PageItem_Typedef *page);
static uint8_t ExistPageIdVerify(ViewNavigatorTypedef *viewNavigator,
		uint8_t pageId);
static uint8_t FindPageIdx(ViewNavigatorTypedef *viewNavigator,
		PageItem_Typedef *page);
static uint8_t FindPageIdxByID(ViewNavigatorTypedef *viewNavigator,
		uint8_t pageId);
static uint8_t FindFirstPageIdxEmpty(ViewNavigatorTypedef *viewNavigator);

static void PageStartup(ViewNavigatorTypedef *viewNavigator,
		PagePropertyTypedef *page_prop);
static uint8_t PageRelease(ViewNavigatorTypedef *viewNavigator,
		PagePropertyTypedef *page_prop);
static void PageShow(ViewNavigatorTypedef *viewNavigator,
		PagePropertyTypedef *page_prop, void *param, int isForward);
static uint8_t PageHide(ViewNavigatorTypedef *viewNavigator,
		PagePropertyTypedef *page_prop);
static uint8_t ExistPageInRouteVerify(ViewNavigatorTypedef *viewNavigator,
		PageItem_Typedef *page);

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
		if (ExistViewVerify(viewNavigator, view) == 0) {
			idx = FindFirstPageIdxEmpty(viewNavigator);
			viewNavigator->registered_view_list[idx] = view;
			viewNavigator->register_view_num++;
			return idx;
		} else
			return FindPageIdx(viewNavigator, view);
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
	uint8_t idx = FindPageIdx(viewNavigator, view);
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
					&viewNavigator->registered_view_list[viewNavigator->view_route.items[viewNavigator->view_route.currentItemPos]])
					!= 0) {
		if (viewNavigator->view_route.currentItemPos > 0)
			viewNavigator->view_route.currentItemPos--;
		PageShow(viewNavigator,
				&viewNavigator->registered_view_list[viewNavigator->view_route.items[viewNavigator->view_route.currentItemPos]],
				NULL, 0);
		viewNavigator->currentViewChanged();
		return 1;
	}
	return 0;
}
/**
 * @brief  Go to Home Page.
 * @param  Page: pointer to data structure of type ViewNavigatorTypedef
 * @retval Done status
 */

uint8_t ViewNavigator_GoHomeView(ViewNavigatorTypedef *viewNavigator) {
	if (viewNavigator->view_route.currentItemPos >= 0
			&& PageHide(viewNavigator,
					&viewNavigator->registered_view_list[viewNavigator->view_route.items[viewNavigator->view_route.currentItemPos]])
					!= 0) {
		viewNavigator->view_route.currentItemPos = 0;
		PageShow(viewNavigator,
				&viewNavigator->registered_view_list[viewNavigator->view_route.items[0]],
				NULL, 0);
		viewNavigator->currentViewChanged();
		return 1;
	}
	return 0;
}
/**
 * @brief  Go to Page.
 * @param  ViewNavigatorTypedef: pointer to data structure of type ViewNavigatorTypedef
 * @param  Page: pointer to data structure of type pageItem_Typedef, if page has not registered before, it is registering in this subroutine
 * @retval done status
 */

uint8_t ViewNavigator_GoToViewOf(ViewNavigatorTypedef *viewNavigator,
		View_Typedef *view, void* param) {
	if (ExistViewVerify(viewNavigator, view) == 0)
		uint8_t PageIdx = ViewNavigator_RegisterView(viewNavigator, view);
	if (viewNavigator->page_route_list.currentItemPos < MAX_pages_chain_NUM - 1
			&& PageHide(viewNavigator,
					&viewNavigator->register_page_list_prop[viewNavigator->page_route_list.value[viewNavigator->page_route_list.currentItemPos]])
					!= 0) {
		uint8_t idx = FindPageIdx(viewNavigator, page);
		viewNavigator->page_route_list.currentItemPos++;
		viewNavigator->page_route_list.value[viewNavigator->page_route_list.currentItemPos] =
				idx;
		PageShow(viewNavigator,
				&viewNavigator->register_page_list_prop[viewNavigator->page_route_list.value[viewNavigator->page_route_list.currentItemPos]],
				param, 1);
		viewNavigator->currentViewChanged();
		return 1;
	}
	return 0;
}
/**
 * @brief  Go to Page.
 * @param  viewNavigator: pointer to data structure of type ViewNavigatorTypedef
 * @param  pageId: page Id , page should be register befor call this subroutine
 * @param  param: param is variable value that has been send to destination page
 * @retval done status
 */

uint8_t ViewNavigator_GoToPageOfByID(ViewNavigatorTypedef *viewNavigator,
		uint8_t pageId, void* param) {

	if (ExistPageIdVerify(viewNavigator, pageId) == 1
			&& viewNavigator->page_route_list.currentItemPos
					< MAX_pages_chain_NUM - 1
			&& PageHide(viewNavigator,
					&viewNavigator->register_page_list_prop[viewNavigator->page_route_list.value[viewNavigator->page_route_list.currentItemPos]])
					!= 0) {
		uint8_t idx = FindPageIdxByID(viewNavigator, pageId);
		viewNavigator->page_route_list.currentItemPos++;
		viewNavigator->page_route_list.value[viewNavigator->page_route_list.currentItemPos] =
				idx;
		PageShow(viewNavigator,
				&viewNavigator->register_page_list_prop[viewNavigator->page_route_list.value[viewNavigator->page_route_list.currentItemPos]],
				param, 1);
		viewNavigator->currentItemChanged();
		return 1;
	}
	return 0;
}
/**
 * @brief  Get Current Page.
 * @param  Page: pointer to data structure of type ViewNavigatorTypedef
 * @param  Page: pointer to data structure of type pageItem_Typedef
 * @retval Page Item
 */

PagePropertyTypedef ViewNavigator_GetCurrentPage(
		ViewNavigatorTypedef *viewNavigator) {
	uint8_t Idx =
			viewNavigator->page_route_list.value[viewNavigator->page_route_list.currentItemPos];
	return viewNavigator->register_page_list_prop[Idx];
}

/**
 * @brief  Verify Page.
 * @param  Page: pointer to data structure of type pageItem_Typedef
 * @retval Page ID status
 */

static uint8_t ExistViewVerify(ViewNavigatorTypedef *viewNavigator,
		PageItem_Typedef *page) {
	if (FindPageIdx(viewNavigator, page) == 255)
		return 0;
	return 1;
}
static uint8_t ExistPageInRouteVerify(ViewNavigatorTypedef *viewNavigator,
		PageItem_Typedef *page) {
	return ExistPageIDInRouteVerify(viewNavigator, page->id);
}
uint8_t ExistPageIDInRouteVerify(ViewNavigatorTypedef *viewNavigator,
		uint8_t pageId) {
	uint8_t idx = 0;

	for (idx = 0; idx < viewNavigator->page_route_list.currentItemPos; idx++) {
		if (viewNavigator->register_page_list_prop[viewNavigator->page_route_list.value[idx]].page->id
				== pageId) {
			return 1;
		}
	}
	return 0;
}

/**
 * @brief  Verify Page.
 * @param  Page: pointer to data structure of type pageItem_Typedef
 * @retval Page ID status
 */

static uint8_t ExistPageIdVerify(ViewNavigatorTypedef *viewNavigator,
		uint8_t pageId) {
	if (FindPageIdxByID(viewNavigator, pageId) == 255)
		return 0;
	return 1;
}
static uint8_t FindPageIdx(ViewNavigatorTypedef *viewNavigator,
		PageItem_Typedef *page) {
	uint8_t idx = 0;

	for (idx = 0; idx < MAX_pageS_NUM; idx++) {
		if (viewNavigator->register_page_list_prop[idx].page != NULL
				&& viewNavigator->register_page_list_prop[idx].page->id
						== page->id) {
			return idx;
		}
	}
	return 255;
}
static uint8_t FindPageIdxByID(ViewNavigatorTypedef *viewNavigator,
		uint8_t pageId) {
	uint8_t idx = 0;

	for (idx = 0; idx < MAX_pageS_NUM; idx++) {
		if (viewNavigator->register_page_list_prop[idx].page != NULL
				&& viewNavigator->register_page_list_prop[idx].page->id
						== pageId) {
			return idx;
		}
	}
	return 255;
}

static uint8_t FindFirstPageIdxEmpty(ViewNavigatorTypedef *viewNavigator) {
	uint8_t idx = 0;

	for (idx = 0; idx < MAX_pageS_NUM; idx++) {
		if (viewNavigator->register_page_list_prop[idx].page == NULL) {
			return idx;
		}
	}
	return 255;
}

//static void PageStartup(ViewNavigatorTypedef *viewNavigator, PageItem_Typedef *page)
//{
//	page->hWindow = page->CreatehWindow();
//	WM_AttachWindowAt(page->hWindow,viewNavigator->page_container_hWin,0,20);
//	WM_HideWindow(page->hWindow);
//	if (page->startup!=NULL)
//		page->startup();
//}
//static uint8_t	PageRelease (ViewNavigatorTypedef *viewNavigator, PageItem_Typedef *page)
//{
//	int ret = 1;
//	if (page->release!=NULL)
//		ret = page->release();
//	if (ret)
//	{
//		WM_DetachWindow(page->hWindow);
//		WM_DeleteWindow(page->hWindow);
//		page->hWindow = WM_HWIN_NULL;
//	}
//	return ret;
//}
//static void	PageShow	(ViewNavigatorTypedef *viewNavigator, PageItem_Typedef *page, void *param, int isForward)
//{
//	WM_ShowWindow(page->hWindow);
//	WM_SetFocus(page->hWindow);
//	if (page->show!=NULL)
//		page->show(param, isForward);
//}
//static uint8_t	PageHide	(ViewNavigatorTypedef *viewNavigator,  PageItem_Typedef *page)
//{
//	int ret=1;
//	if (page->hide!=NULL)
//		ret = page->hide();
//	if (ret)
//		WM_HideWindow(page->hWindow);
//	return ret;
//}
static void PageStartup(ViewNavigatorTypedef *viewNavigator,
		PagePropertyTypedef * page_prop) {

	if (page_prop->page->startup != NULL)
		page_prop->page->startup();
}
static uint8_t PageRelease(ViewNavigatorTypedef *viewNavigator,
		PagePropertyTypedef * page_prop) {
	int ret = 1;
	if (page_prop->page->release != NULL)
		ret = page_prop->page->release();
	return ret;
}
static void PageShow(ViewNavigatorTypedef *viewNavigator,
		PagePropertyTypedef * page_prop, void *param, int isForward) {
	page_prop->hWindow = page_prop->page->CreatehWindow();
	WM_AttachWindowAt(page_prop->hWindow, viewNavigator->page_container_hWin, 0,
			20);
	WM_SetFocus(page_prop->hWindow);
	if (page_prop->page->show != NULL)
		page_prop->page->show(param, isForward);
}
static uint8_t PageHide(ViewNavigatorTypedef *viewNavigator,
		View_Typedef * view) {
	int ret = 1;
	if (view->hide != NULL)
		ret = view->hide();
	if (ret) {
		WM_DetachWindow(page_prop->hWindow);
		WM_DeleteWindow(page_prop->hWindow);
		page_prop->hWindow = WM_HWIN_NULL;
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
