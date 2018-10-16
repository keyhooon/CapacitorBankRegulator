/*
 * sorted_list_heap.h
 *
 *  Created on: Oct 15, 2018
 *      Author: HP
 */

#ifndef SORTED_LIST_HEAP_H_
#define SORTED_LIST_HEAP_H_
#include "sglib.h"
#include "FreeRTOS.h"
#define DATA_ACCESS_SORTED_LIST_PROTOTYPES(type, displayOperation) \
	typedef struct type##_List_Struct { \
		type##_Typedef current_item; \
		struct type##_List_Struct *next_ptr; \
	} type##_List_Typedef; \
	char* (*Display)(type##_Typedef item){	\
		displayOperation(item);\
	}\
	type##_List_Typedef * type##List; \
	void Add##type(type##_Typedef *value) ; \
	type##_List_Typedef * Get##type##List(uint32_t pageSize, uint32_t pageIndex) ; \
	void Remove##type(type##_List_Typedef * value);

#define DATA_ACCESS_SORTED_LIST_FUNCTIONS(type, comparator) \
	SGLIB_DEFINE_SORTED_LIST_PROTOTYPES(type##_List_Typedef, comparator, \
			next_ptr) \
	SGLIB_DEFINE_SORTED_LIST_FUNCTIONS(type##_List_Typedef, STRING_COMPARATOR, \
			next_ptr) \
	void Add##type(type##_Typedef *value) { \
		type##_List_Typedef * node = pvPortMalloc(sizeof(type##_List_Typedef)); \
		memcpy(node, value, sizeof(type##_List_Typedef)); \
		sglib_##type##_List_add(&type##List, node); \
	} \
	void Remove##type(type##_List_Typedef * value) { \
		type##_List_Typedef * item; \
		sglib_##type##_List_delete_if_member(&type##List, value, &item); \
		vPortFree(item); \
	}

#endif /* SORTED_LIST_HEAP_H_ */
