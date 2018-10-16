/*
 * List_Heap.h
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */

#ifndef LIST_HEAP_H_
#define LIST_HEAP_H_
#include "sglib.h"
#include "FreeRTOS.h"
#include "string.h"
#define DATA_ACCESS_LIST_PROTOTYPES(type, displayOperation) \
	typedef struct type##_List_Struct { \
		type##_Typedef current_item; \
		struct type##_List_Struct *next_ptr; \
		struct type##_List_Struct *prev_ptr; \
	} type##_List_Typedef; \
	char* (*type##Display)(type##_Typedef item){	\
		displayOperation(item);\
	}\
	type##_List_Typedef * type##List; \
	void Add##type(type##_Typedef *value) ;	\
	type##_List_Typedef * Get##type##List(uint32_t pageSize, uint32_t pageIndex) ; \
	void Remove##type(type##_List_Typedef * value) ;

#define DATA_ACCESS_LIST_FUNCTIONS(type, comparator) \
	SGLIB_DEFINE_DL_LIST_PROTOTYPES(type##_List_Typedef, comparator, prev_ptr, next_ptr) \
	SGLIB_DEFINE_DL_LIST_FUNCTIONS(type##_List_Typedef, STRING_COMPARATOR, prev_ptr, next_ptr) \
	int Add##type(type##_Typedef *value) { \
		type##_List_Typedef * node = pvPortMalloc(sizeof(type##_List_Typedef)); \
		type##_List_Typedef * member;\
		memcpy(node, value, sizeof(type##_List_Typedef)); \
		sglib_##type##_List_add_if_not_member(&type##List, node, &member); \
		if (member == NULL)\
			return 1;\
		return 0;\
	} \
	char * Get##type##DisplayArray(displayOperation){\
		struct sglib_##type##_iterator it;\
		type##_List_Typedef *val; \
		char** stringArray = pvPortMalloc(sizeof(sglib_##type##_len(type##List)) * sizeof(void*));\
		char * stringItem = *stringArray;\
		 for (val = type##List; val != NULL; val = type##List->next_ptr)\
		 {\
			char * disp = displayOperation(val->current_item) \
		 	stringItem = pvPortMalloc(strlen(disp));\
		 	strcpy(stringItem++,disp);\
		 }\
	}\

	void Remove##type(type##_List_Typedef * value) { \
		type##_List_Typedef * item; \
		sglib_##type##_List_delete_if_member(&type##List, value, &item); \
		if (member != NULL)\
			return 1;\
		vPortFree(item); \
		return 0;\
	}

#endif /* LIST_HEAP_H_ */
