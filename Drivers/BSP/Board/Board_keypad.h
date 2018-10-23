/*
 * Board_keypad.h
 *
 *  Created on: Oct 10, 2018
 *      Author: HP
 */

#ifndef BSP_BOARD_BOARD_KEYPAD_H_
#define BSP_BOARD_BOARD_KEYPAD_H_


#include "main.h"

 void KEYPAD_Init(void);
void KeyboardProc(void const * argument);

void KEYPAD_Process(void);

void KEYPAD_IO_Init(void);


#define HoldKeyTime			800
#define HoldKeyLatencyTime	200
#define DoubleClickTime		1000
#define KeyPadProccessTime	50


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
#endif /* BSP_BOARD_BOARD_KEYPAD_H_ */
