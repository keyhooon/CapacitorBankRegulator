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







typedef struct Loaded_View_Struct {
	uint8_t index;
	void * parameter;
} Loaded_View_TypeDef;

typedef struct Registered_View_Struct {
	View_Typedef * view;
	void * setting;
} Registered_View_TypeDef;


typedef struct View_Navigator_Struct {
	WM_HWIN view_container_hWin;
	Registered_View_TypeDef registered_View_List[MAX_VIEW_COUNT];
	Loaded_View_TypeDef loaded_View_List[DEEPEST_CHAIN_VIEW_COUNT];
	uint8_t current_Loaded_View_Index;
	void (*currentViewChanged)(void);
} View_Navigator_Typedef;

extern View_Navigator_Typedef DefaultViewNavigator;

/* Exported constants --------------------------------------------------------*/
/* Exported macros -----------------------------------------------------------*/
/* Exported functions ------------------------------------------------------- */
void InitMenu(void);
void StartUp(void);
void SetGuiProfile(void);
void ViewNavigator_Init(View_Navigator_Typedef *viewNavigator,
		WM_HWIN containerhWin);
uint8_t ViewNavigator_RegisterView(View_Navigator_Typedef *viewNavigator,
		View_Typedef *view);
uint8_t ViewNavigator_UnregisterView(View_Navigator_Typedef *viewNavigator,
		View_Typedef *view);
uint8_t ViewNavigator_GetViewCount(View_Navigator_Typedef *viewNavigator);

GUI_HWIN ViewNavigator_GoBackView(View_Navigator_Typedef *viewNavigator);
GUI_HWIN ViewNavigator_GoHomeView(View_Navigator_Typedef *viewNavigator);
GUI_HWIN ViewNavigator_GoToViewOf(View_Navigator_Typedef *viewNavigator,
		View_Typedef * view, void * parameter);
GUI_HWIN ViewNavigator_GoToViewOfByID(View_Navigator_Typedef *viewNavigator,
		uint8_t viewId, void * parameter);
View_Typedef * ViewNavigator_GetCurrentView(
		View_Navigator_Typedef *viewNavigator);

uint8_t ExistViewIDInRouteVerify(View_Navigator_Typedef *viewNavigator,
		uint8_t viewId);
#ifdef __cplusplus
}
#endif

#endif /* VIEWCONTAINER_VIEWNAVIGATOR_H_ */
