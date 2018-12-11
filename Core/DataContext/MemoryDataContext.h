/*
 * DataContext.h
 *
 *  Created on: Dec 11, 2018
 *      Author: HP
 */

#ifndef DATACONTEXT_MEMORYDATACONTEXT_H_
#define DATACONTEXT_MEMORYDATACONTEXT_H_

extern int hMemoryDataContextAllocator;

void InitMemoryDataContext();

typedef struct {
	int (*Add)(void *);
	int (*Remove)(void);
	int (*GetListLen)(void);
	void (*GetDisplay)(char *);
	char ** (*GetDisplayArray)(void);
	void (*FreeDisplayArray)(char **);
	int (*SetCurrentItem)(int);
	int (*GetCurrentItemIndex)(void);
	void * (*GetCurrentItem)(void);
} ListApiHandlers_typedef;

#define DATA_CONTEXT_PROTOTYPES(type) \
	typedef struct type##_List_Struct { \
		struct type##_List_Struct *next_ptr; \
		struct type##_List_Struct *prev_ptr; \
		type##_Typedef current_item; \
	} type##_List_Typedef; \
	int Add##type(type##_Typedef *value); \
	int Remove##type(void); \
	int Get##type##ListLen(void); \
	char ** Get##type##DisplayArray(void); \
	void Get##type##Display(char *); \
	void Free##type##DisplayArray(char ** stringArray); \
	int SetCurrent##type##Item(int index); \
	int GetCurrent##type##ItemIndex(void); \
	void * GetCurrent##type##Item(void); \


#define DATA_CONTEXT_FUNCTIONS(type, comparator, display, displayDetail) \
	SGLIB_DEFINE_DL_LIST_PROTOTYPES(type##_List_Typedef, comparator, prev_ptr, next_ptr) \
	SGLIB_DEFINE_DL_LIST_FUNCTIONS(type##_List_Typedef, comparator, prev_ptr, next_ptr) \
	ListApiHandlers_typedef type##ListApiHandlers = { \
			Add##type, \
			Remove##type, \
			Get##type##ListLen, \
			Get##type##Display, \
			Get##type##DisplayArray, \
			Free##type##DisplayArray, \
			SetCurrent##type##Item, \
			GetCurrent##type##ItemIndex, \
			GetCurrent##type##Item,\
	}; \
	int Add##type(type##_Typedef *value) { \
		type##_List_Typedef * node = pvPortMalloc(sizeof(type##_List_Typedef)); \
		type##_List_Typedef * member;\
		memcpy(&(node->current_item), value, sizeof(type##_Typedef)); \
		return (sglib_##type##_List_Typedef_add_if_not_member(&type##List, node, &member)); \
	} \
	int Remove##type() { \
		type##_List_Typedef * item; \
		if (sglib_##type##_List_Typedef_delete_if_member(&type##List, type##List, &item)) \
		{ \
			vPortFree(item); \
			return 1; \
		} \
		return 0;\
	} \
	int Get##type##ListLen() { \
		return sglib_##type##_List_Typedef_len(type##List);\
	} \
	void Get##type##Display(char * text) {\
		displayDetail(text, type##List->current_item);\
	}\
	char ** Get##type##DisplayArray(){ \
		char temp[100]; \
		int itemCount = sglib_##type##_List_Typedef_len(type##List) ; \
		char** stringArray = pvPortMalloc((itemCount + 1) *  sizeof(char *) ); \
		char * stringItem;\
		type##_List_Typedef *val = sglib_##type##_List_Typedef_get_first (type##List) ; \
		 for (int i = 0; i < itemCount; i++) { \
			display(temp, val->current_item) \
		 	stringItem = pvPortMalloc(strlen(temp) + 1); \
		 	strcpy(stringItem,temp); \
			*(stringArray + i) = stringItem; \
		 	val = val->next_ptr; \
		 	if (val == NULL) \
				break; \
		 } \
		 *(stringArray + itemCount) = NULL; \
		 return stringArray; \
	} \
	void Free##type##DisplayArray(char ** stringArray){\
		vPortFree(stringArray); \
		while(* stringArray) { \
			vPortFree(* stringArray); \
			stringArray ++; \
		} \
	} \
	int SetCurrent##type##Item(int index) {\
		type##_List_Typedef *val = sglib_##type##_List_Typedef_get_first (type##List); \
		for (int i = 0; i < index && val != NULL; i++) { \
			if (val == NULL) \
				return 1; \
			val = val -> next_ptr;\
		 } \
		 type##List = val; \
		 return 0; \
	} \
	int GetCurrent##type##ItemIndex() {\
		int i = -1; \
		for (type##_List_Typedef *val = type##List; val != NULL; val = val->prev_ptr) { \
			i++;\
		 } \
		 return i; \
	} \
	void * GetCurrent##type##Item(void){\
		return &(type##List->current_item);\
	}\

#endif /* DATACONTEXT_MEMORYDATACONTEXT_H_ */
