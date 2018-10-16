/*
 * ViewNavigator.h
 *
 *  Created on: Oct 8, 2018
 *      Author: HP
 */

#ifndef VIEWCONTAINER_VIEWNAVIGATOR_H_
#define VIEWCONTAINER_VIEWNAVIGATOR_H_

/* Includes ------------------------------------------------------------------*/
#include "main.h"
#include "wm.h"
#include "dialog.h"
#include "View.h"
/* Exported types ------------------------------------------------------------*/
#define MAX_VIEW_COUNT	                	                                    40
#define DEEPEST_CHAIN_VIEW_COUNT												10







typedef struct {
	uint8_t items[DEEPEST_CHAIN_VIEW_COUNT];
	int8_t currentItemPos;
} PositionListTypeDef;

typedef struct {
	WM_HWIN view_container_hWin;
	View_Typedef * registered_view_list[MAX_VIEW_COUNT];
	uint16_t register_view_num;
	PositionListTypeDef view_route;
	void (*currentViewChanged)(void);
} ViewNavigatorTypedef;

ViewNavigatorTypedef DefaultViewNavigator;

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void InitMenu(void);
void StartUp(void);
void SetGuiProfile(void);
void ViewNavigator_Init(ViewNavigatorTypedef *viewNavigator,
		WM_HWIN containerhWin);
uint8_t ViewNavigator_RegisterView(ViewNavigatorTypedef *viewNavigator,
		View_Typedef *view);
uint8_t ViewNavigator_UnregisterView(ViewNavigatorTypedef *viewNavigator,
		View_Typedef *view);
uint8_t ViewNavigator_GetViewCount(ViewNavigatorTypedef *viewNavigator);

uint8_t ViewNavigator_GoBackView(ViewNavigatorTypedef *viewNavigator);
uint8_t ViewNavigator_GoHomeView(ViewNavigatorTypedef *viewNavigator);
uint8_t ViewNavigator_GoToViewOf(ViewNavigatorTypedef *viewNavigator,
		View_Typedef *view);
uint8_t ViewNavigator_GoToViewOfByID(ViewNavigatorTypedef *viewNavigator,
		uint8_t viewId);
View_Typedef * ViewNavigator_GetCurrentView(ViewNavigatorTypedef *viewNavigator);

uint8_t ExistViewIDInRouteVerify(ViewNavigatorTypedef *viewNavigator,
		uint8_t viewId);
#ifdef __cplusplus
}
#endif

#endif /* VIEWCONTAINER_VIEWNAVIGATOR_H_ */
