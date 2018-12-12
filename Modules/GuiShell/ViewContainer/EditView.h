/*
 * EditView.h
 *
 *  Created on: Oct 7, 2018
 *      Author: HP
 */

#include "View.h"
#ifndef VIEWCONTAINER_EDITVIEW_H_
#define VIEWCONTAINER_EDITVIEW_H_

typedef struct {
	const char canBeNull;
	const char * infoText;
} EditViewParam_Typedef;

typedef struct {
	char * value;
} EditViewState_TypeDef;

#endif /* VIEWCONTAINER_EDITVIEW_H_ */
