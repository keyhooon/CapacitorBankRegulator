/*
 * EditView.h
 *
 *  Created on: Oct 7, 2018
 *      Author: HP
 */

#include "MemoryDataContext.h"
#include "MemoryDataContext.h"
#include "DataModel.h"
#include "View.h"


#ifndef VIEWCONTAINER_EDITVIEW_H_
#define VIEWCONTAINER_EDITVIEW_H_

typedef struct {
	const FieldAttribute_Typedef * fieldAttribute;
	void (*FinishCallback)(void *);
	void (*CancelCallback)(void *);
	int fieldCount;
	void * editableModel;
	int isNew;
	int currentFieldIndex;
	void * buffer;
} EditView_Parameters_Typedef;

int CompressEditViewBuffer(EditView_Parameters_Typedef *);
#endif /* VIEWCONTAINER_EDITVIEW_H_ */
