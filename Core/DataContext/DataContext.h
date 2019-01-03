/*
 * DataContext.h
 *
 *  Created on: Jan 3, 2019
 *      Author: HP
 */

#ifndef DATACONTEXT_DATACONTEXT_H_
#define DATACONTEXT_DATACONTEXT_H_

typedef struct {
	int (*Add)(void *);
	int (*Remove)(void *);
	int (*RemoveCurrent)(void);
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

#endif /* DATACONTEXT_DATACONTEXT_H_ */
