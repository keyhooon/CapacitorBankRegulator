/*
 * keypad.h
 *
 *  Created on: Oct 10, 2018
 *      Author: HP
 */

#ifndef KEYPAD_H_
#define KEYPAD_H_


#include "main.h"

void KEYPAD_Init(void);
void KEYPAD_Main(void const * argument);
void KEYPAD_EXTI_Callback(uint16_t GPIO_Pin);

typedef enum {
	Command, KeyCode, Char,
} KeypadBtnType_Enum_typedef;

typedef struct {
	KeypadBtnType_Enum_typedef KeypadBtnType;
	union {
		char chars[6];
		void (*Func)(int isPressed);
	} Val;
} KeypadBtn_typedef;
#endif /* KEYPAD_H_ */
