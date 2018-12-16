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
	int (*Remove)(void *);
	int (*Edit)(void *, void *);
	int (*GetCount)(void);
	void (*GetDisplay)(char *);
	char ** (*GetDisplayArray)(void);
	void (*FreeDisplayArray)(char **);
	int (*SetSelectedItem)(void *);
	void * (*GetSelectedItem)(void);
	void (*FreeItem)(void *);
	int (*SetSelectedIndex)(int);
	int (*GetSelectedIndex)(void);
} ListApiHandlers_typedef;

#define DATA_CONTEXT_PROTOTYPES(type) \
	typedef struct type##_List_Struct { \
		struct type##_List_Struct *next; \
		struct type##_List_Struct *previous; \
		type##_Typedef value; \
	} type##_List_Typedef; \
	int Add##type(type##_Typedef *value); \
	int Remove##type(type##_Typedef *value); \
	int Edit##type(type##_Typedef *oldValue, type##_Typedef *newValue); \
	int Get##type##Count(); \
	void Get##type##Display(char *); \
	char ** Get##type##DisplayArray(void); \
	void Free##type##DisplayArray(char ** stringArray); \
	int SetSelected##type##Item(type##_Typedef *value) ; \
	type##_Typedef * GetSelected##type##Item(void) ; \
	void Free##type##Item(type##_Typedef * value) ; \
	int SetSelected##type##Index(int value); \
	int GetSelected##type##Index();\


#define DATA_CONTEXT_FUNCTIONS(type, TYPE, hDataAllocator) \
	const ListApiHandlers_typedef type##ListApiHandlers = { \
			Add##type, \
			Remove##type, \
			Edit##type, \
			Get##type##Count, \
			Get##type##Display, \
			Get##type##DisplayArray, \
			Free##type##DisplayArray, \
			SetSelected##type##Item, \
			GetSelected##type##Item, \
			Free##type##Item,\
			SetSelected##type##Index, \
			GetSelected##type##Index, \
	}; \
	type##_List_Typedef * type##_List; \
	type##_List_Typedef * Find##type##Item(type##_Typedef *value) { \
		type##_List_Typedef * _dlp_ ;\
		  for(_dlp_ = type##_List; ((_dlp_)!=NULL) && (TYPE##_COMPARATOR(_dlp_->value, (*value)) != 0); _dlp_= _dlp_->previous) ;\
		  if (_dlp_ == NULL) \
			  for(_dlp_ = type##_List; ((_dlp_)!=NULL) && (TYPE##_COMPARATOR(_dlp_->value, (*value)) != 0); _dlp_= _dlp_->next) ;\
		  return _dlp_;\
	}\
	int Add##type(type##_Typedef *value) { \
		type##_List_Typedef * _dlp_ = Find##type##Item(value); \
		if (_dlp_ == NULL) \
		{ \
			size_t sz = DataAllocator_GetSize(TYPE##_MODEL_DATA_ALLOCATOR,value); \
			size_t header_sz = sizeof(type##_List_Typedef) << 1; \
			type##_List_Typedef * elem = DataAllocator_Alloc(hDataAllocator, sz + header_sz); \
			memcpy(((char *)elem) + header_sz, value, sz ); \
			if (type##_List == NULL) \
			{ \
				  (type##_List) = (elem);\
				  (type##_List)->next = (type##_List)->previous = NULL;\
			} else{\
			    (elem)->next = (type##_List);\
			    (elem)->previous = (type##_List)->previous;\
			    (type##_List)->previous = (elem);\
			    if ((elem)->previous != NULL) (elem)->previous->next = (elem);\
			} \
			return 0; \
		} else\
			return -1; \
	} \
	int Remove##type(type##_Typedef *value) { \
		type##_List_Typedef * _dlp_ = Find##type##Item(value); \
		if (_dlp_ != NULL) \
		{ \
			DataAllocator_Free(hDataAllocator,_dlp_); \
			return 0; \
		} \
		return -1;\
	} \
	int Edit##type(type##_Typedef *oldValue, type##_Typedef *newValue) { \
		if (Remove##type(oldValue)){ \
			if (Add##type(newValue))\
				return 0;\
			else\
				Add##type(oldValue);\
		}\
		return -1;\
	}\
	int Get##type##Count() { \
		int _r_ = 0;\
		if ((type##_List)==NULL) \
			return 0;\
		else {\
			for(type##_List_Typedef * _dlp_ = type##_List; _dlp_!=NULL ; _dlp_= _dlp_->previous) \
				_r_ ++ ;\
			for(type##_List_Typedef * _dlp_ = type##_List; _dlp_!=NULL ; _dlp_= _dlp_->next) \
				_r_ ++ ;\
			return _r_ - 1;\
		}\
	} \
	void Get##type##Display(char * text) {\
		TYPE##_VIEW(text, type##_List->value);\
	}\
	char ** Get##type##DisplayArray(){ \
		char temp[100]; \
		int itemCount = Get##type##Count() ; \
		char** stringArray = pvPortMalloc((itemCount + 1) *  sizeof(char *) ); \
		char ** result = stringArray; \
		char * stringItem;\
		type##_List_Typedef *_dlp_; \
		for(_dlp_ = type##_List; _dlp_->previous !=NULL ; _dlp_= _dlp_->previous) ;\
		for(; _dlp_!=NULL ; _dlp_= _dlp_->next) { \
			display(temp, _dlp_->value) ;\
		 	stringItem = pvPortMalloc(strlen(temp) + 1); \
		 	strcpy(stringItem,temp); \
			*(stringArray ++) = stringItem; \
		}\
		 *stringArray = NULL; \
		 return result; \
	} \
	void Free##type##DisplayArray(char ** stringArray){\
		while(* stringArray) { \
			vPortFree(* stringArray); \
			stringArray ++; \
		} \
		vPortFree(stringArray); \
	} \
	int SetSelected##type##Item(type##_Typedef *value) {\
		type##_List_Typedef * _dlp_ = Find##type##Item(value);\
		if (_dlp_ !=NULL) \
		{	type##_List = _dlp_;\
			return 0;\
		} \
		return 1;\
	} \
	type##_Typedef * GetSelected##type##Item(void) {\
		type##_Typedef *_dlp_ ; \
		if (type##_List != NULL) \
		{ \
			size_t sz = DataAllocatorGetSize(hDataAllocator,type##_List); \
			size_t header_sz = sizeof(type##_List_Typedef) << 1; \
			_dlp_ = DataAllocator_Alloc(TYPE##_MODEL_DATA_ALLOCATOR, sz - header_sz); \
			memcpy(_dlp_,((char *)type##_List) + header_sz, sz - header_sz ); \
			return _dlp_; \
		} \
		return NULL; \
	} \
	void Free##type##Item(type##_Typedef * value) {\
		DataAllocator_Alloc(TYPE##_MODEL_DATA_ALLOCATOR, value); \
	} \
	int SetSelected##type##Index(int value){\
		type##_List_Typedef *_dlp_; \
		for(_dlp_ = type##_List; _dlp_->previous != NULL; _dlp_= _dlp_->previous) ;\
		for (int i = 0; i < value && _dlp_ != NULL ; i++, _dlp_ = _dlp_->next);\
		return (_dlp_ == NULL); \
	}\
	int GetSelected##type##Index() {\
		int i = -1; \
		for (type##_List_Typedef *_dlp_ = type##_List; _dlp_ != NULL; _dlp_ = _dlp_->previous, i++) ; \
		 return i; \
	} \


#endif /* DATACONTEXT_MEMORYDATACONTEXT_H_ */
