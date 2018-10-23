/*
 * Board_keypad.c
 *
 *  Created on: Oct 10, 2018
 *      Author: HP
 */


#include "Board_keypad.h"
#include "GUI.h"
#include "cmsis_os.h"

extern uint16_t KP_C_PINs[4];
extern uint16_t KP_R_PINs[4];
extern GPIO_TypeDef * KP_C_Ports[4];
extern GPIO_TypeDef * KP_R_Ports[4];

void KEYPAD_BUTTON_KeyCode_INIT(uint32_t i, uint32_t j, const char value);
void KEYPAD_BUTTON_CHAR_INIT(uint32_t i, uint32_t j, const char * ch);



osSemaphoreId keypadSemaphoreID;

KeypadBtn_typedef KP_Btn[4][6];
int KeyPressed = 0;
KeypadBtn_typedef *lastKeypadBtnReleased;
KeypadBtn_typedef *CurrentKeypadBtnPressed;
int CountKeyPressed = 0;
int lastTimeKeyReleased = 0;
int lastTimeKeyPressed;
int holdKey;

void KEYPAD_EXTI_Callback(uint16_t GPIO_Pin) {
	if (lastTimeKeyReleased + KeyPadProccessTime * 2 > HAL_GetTick())
		return;
	uint32_t find = 0;
	KeypadBtn_typedef * BtnPressed = NULL;
	for (uint32_t row = 0; row < 4 && find == 0; row++)
		if (GPIO_Pin == KP_R_PINs[row]) {
			if (HAL_GPIO_ReadPin(KP_R_Ports[row], KP_R_PINs[row])
					== GPIO_PIN_RESET) {
				BtnPressed = CurrentKeypadBtnPressed;
				KeyPressed = 0;
				find = 1;
			} else {
				if (KeyPressed == 1)
					return;
				KeyPressed = 1;
				CLEAR_BIT(EXTI->IMR,
						KP_R_PINs[0] | KP_R_PINs[1] | KP_R_PINs[2]
								| KP_R_PINs[3]);
				for (uint32_t col = 0; col < 4 && find == 0; col++) {
					HAL_GPIO_WritePin(KP_C_Ports[col], KP_C_PINs[col],
							GPIO_PIN_RESET);
					for (volatile int i = 0; i < 10; i++)
						;
					if (HAL_GPIO_ReadPin(KP_R_Ports[row], KP_R_PINs[row])
							== GPIO_PIN_RESET) {
						find = 1;
						BtnPressed = &KP_Btn[row][col];
					}
					HAL_GPIO_WritePin(KP_C_Ports[col], KP_C_PINs[col],
							GPIO_PIN_SET);
				}
				SET_BIT(EXTI->IMR,
						KP_R_PINs[0] | KP_R_PINs[1] | KP_R_PINs[2]
								| KP_R_PINs[3]);
			}
		}

	__HAL_GPIO_EXTI_CLEAR_IT(GPIO_Pin);
	if (BtnPressed == NULL)
		return;
	CurrentKeypadBtnPressed = BtnPressed;
	if (KeyPressed == 1)
	osSemaphoreRelease(keypadSemaphoreID);
}

void KeyboardProc(void const * argument) {
	KEYPAD_Init();
	for (;;) {
		if (KeyPressed) {
			if ((holdKey == 0)) {
				if (CurrentKeypadBtnPressed->KeypadBtnType == Char) {
					if (lastTimeKeyReleased + DoubleClickTime > HAL_GetTick()
							&& lastKeypadBtnReleased
									== CurrentKeypadBtnPressed) {
						GUI_SendKeyMsg(GUI_KEY_BACKSPACE, 1);
						if (CurrentKeypadBtnPressed->Val.chars[++CountKeyPressed]
								== '\0')
							CountKeyPressed = 0;
					} else
						CountKeyPressed = 0;
				}
				GUI_SendKeyMsg(
						(int) CurrentKeypadBtnPressed->Val.chars[CountKeyPressed],
						1);
				lastTimeKeyPressed = HAL_GetTick();
				holdKey = 1;
			} else if (lastTimeKeyPressed + HoldKeyTime < HAL_GetTick()) {
				if (CurrentKeypadBtnPressed->KeypadBtnType == Char) {
					GUI_SendKeyMsg(GUI_KEY_BACKSPACE, 1);
					if (CurrentKeypadBtnPressed->Val.chars[++CountKeyPressed]
							== '\0')
						CountKeyPressed = 0;
				}
				GUI_SendKeyMsg(
						(int) CurrentKeypadBtnPressed->Val.chars[CountKeyPressed],
						1);
				lastTimeKeyPressed = HAL_GetTick()
						- (HoldKeyTime - HoldKeyLatencyTime);
			}
			osDelay(KeyPadProccessTime);
		} else {
			holdKey = 0;
			GUI_SendKeyMsg((int) CurrentKeypadBtnPressed->Val.chars[0], 0);
			lastKeypadBtnReleased = CurrentKeypadBtnPressed;
			lastTimeKeyReleased = HAL_GetTick();
			osSemaphoreWait(keypadSemaphoreID, osWaitForever);
		}
	}
}
void KEYPAD_Init(void) {
	KEYPAD_IO_Init();
	KEYPAD_BUTTON_KeyCode_INIT(0, 0, GUI_KEY_UP);		// UP
	KEYPAD_BUTTON_KeyCode_INIT(0, 1, GUI_KEY_DOWN);		// Down
	KEYPAD_BUTTON_KeyCode_INIT(0, 2, GUI_KEY_RIGHT);	// Left
	KEYPAD_BUTTON_KeyCode_INIT(0, 3, GUI_KEY_LEFT);		// Right
	KEYPAD_BUTTON_CHAR_INIT(3, 0, "1");
	KEYPAD_BUTTON_CHAR_INIT(2, 0, "2ABC");
	KEYPAD_BUTTON_CHAR_INIT(1, 0, "3DEF");
	KEYPAD_BUTTON_CHAR_INIT(3, 1, "4GHI");
	KEYPAD_BUTTON_CHAR_INIT(2, 1, "5JKL");
	KEYPAD_BUTTON_CHAR_INIT(1, 1, "6MNO");
	KEYPAD_BUTTON_CHAR_INIT(3, 2, "7PQRS");
	KEYPAD_BUTTON_CHAR_INIT(2, 2, "8TUV");
	KEYPAD_BUTTON_CHAR_INIT(1, 2, "9WXYZ");
	KEYPAD_BUTTON_KeyCode_INIT(3, 3, GUI_KEY_DELETE);	// DEL
	KEYPAD_BUTTON_CHAR_INIT(2, 3, "0 ");
	KEYPAD_BUTTON_KeyCode_INIT(1, 3, GUI_KEY_ENTER);	// ENTER
	osSemaphoreDef(Keypad);
	keypadSemaphoreID = osSemaphoreCreate(osSemaphore(Keypad), 1);
}
void KEYPAD_BUTTON_KeyCode_INIT(uint32_t i, uint32_t j, const char value) {
	KP_Btn[i][j].KeypadBtnType = KeyCode;
	KP_Btn[i][j].Val.chars[0] = value;
	KP_Btn[i][j].Val.chars[1] = (char) 0;

}
void KEYPAD_BUTTON_CHAR_INIT(uint32_t i, uint32_t j, const char * ch) {
	KP_Btn[i][j].KeypadBtnType = Char;
	strcpy(KP_Btn[i][j].Val.chars, ch);
}


