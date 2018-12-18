/*
 * Board_keypad.c
 *
 *  Created on: Oct 10, 2018
 *      Author: HP
 */


#include <keypad.h>
#include <keypad_config.h>
#include "GUI.h"
#include "cmsis_os.h"

void Keypad_Io_Init(void);

void KeypadButtonKeyCode_Init(uint32_t i, uint32_t j, const char value);
void KeypadButtonChar_Init(uint32_t i, uint32_t j, const char * ch);

uint16_t KP_C_PINs[4] = { KP_C0_PIN, KP_C1_PIN, KP_C2_PIN, KP_C3_PIN };
uint16_t KP_R_PINs[4] = { KP_R0_PIN, KP_R1_PIN, KP_R2_PIN, KP_R3_PIN };
GPIO_TypeDef * KP_C_Ports[4] = { KP_C0_PORT, KP_C1_PORT, KP_C2_PORT,
KP_C3_PORT };
GPIO_TypeDef * KP_R_Ports[4] = { KP_R0_PORT, KP_R1_PORT, KP_R2_PORT,
KP_R3_PORT };





osSemaphoreId keypadSemaphoreID;
osThreadId keyboardTaskHandle;

KeypadBtn_typedef KP_Btn[4][4];
int KeyPressed = 0;
KeypadBtn_typedef *lastKeypadBtnReleased;
KeypadBtn_typedef *CurrentKeypadBtnPressed;
int CountKeyPressed = 0;
int lastTimeKeyReleased = 0;
int lastTimeKeyPressed;
int holdKey;

void Keypad_Io_Init(void) {

	GPIO_InitTypeDef GPIO_InitStruct;

	/* GPIO Ports Clock Enable */
	KP_R_GPIO_CLK_ENABLE();
	KP_C_GPIO_CLK_ENABLE();

	/*Configure GPIO pin : PtPin */
	GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
	GPIO_InitStruct.Pull = GPIO_PULLUP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
	GPIO_InitStruct.Pin = KP_C0_PIN;
	HAL_GPIO_Init(KP_C0_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = KP_C1_PIN;
	HAL_GPIO_Init(KP_C1_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = KP_C2_PIN;
	HAL_GPIO_Init(KP_C2_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = KP_C3_PIN;
	HAL_GPIO_Init(KP_C3_PORT, &GPIO_InitStruct);

	HAL_GPIO_WritePin(KP_C_Ports[0], KP_C_PINs[0], GPIO_PIN_SET);
	HAL_GPIO_WritePin(KP_C_Ports[1], KP_C_PINs[1], GPIO_PIN_SET);
	HAL_GPIO_WritePin(KP_C_Ports[2], KP_C_PINs[2], GPIO_PIN_SET);
	HAL_GPIO_WritePin(KP_C_Ports[3], KP_C_PINs[3], GPIO_PIN_SET);

	GPIO_InitStruct.Mode = GPIO_MODE_IT_RISING_FALLING;
	GPIO_InitStruct.Pull = GPIO_PULLDOWN;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	GPIO_InitStruct.Pin = KP_R0_PIN;
	HAL_GPIO_Init(KP_R0_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = KP_R1_PIN;
	HAL_GPIO_Init(KP_R1_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = KP_R2_PIN;
	HAL_GPIO_Init(KP_R2_PORT, &GPIO_InitStruct);
	GPIO_InitStruct.Pin = KP_R3_PIN;
	HAL_GPIO_Init(KP_R3_PORT, &GPIO_InitStruct);

	HAL_NVIC_SetPriority(KP_R_IRQn, 0x0A, 0x00);
	HAL_NVIC_EnableIRQ(KP_R_IRQn);

}


void Keypad_EXTI_Callback(uint16_t GPIO_Pin) {
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

void Keypad_Main(void const * argument) {

	Keypad_Io_Init();
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
				} else
					CountKeyPressed = 0;
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
			if (holdKey == 1) {
				holdKey = 0;
				GUI_SendKeyMsg((int) CurrentKeypadBtnPressed->Val.chars[0], 0);
				lastKeypadBtnReleased = CurrentKeypadBtnPressed;
				lastTimeKeyReleased = HAL_GetTick();
			}
			osSemaphoreWait(keypadSemaphoreID, KeyPadProccessTime);

		}
	}
}
void Keypad_Init(void) {

	osThreadDef(keyboardTask, Keypad_Main, osPriorityNormal, 0, 256);
	keyboardTaskHandle = osThreadCreate(osThread(keyboardTask), NULL);

	osSemaphoreDef(Keypad);
	keypadSemaphoreID = osSemaphoreCreate(osSemaphore(Keypad), 1);

	KeypadButtonKeyCode_Init(0, 0, GUI_KEY_UP);		// UP
	KeypadButtonKeyCode_Init(0, 1, GUI_KEY_DOWN);		// Down
	KeypadButtonKeyCode_Init(0, 2, GUI_KEY_RIGHT);	// Left
	KeypadButtonKeyCode_Init(0, 3, GUI_KEY_LEFT);		// Right
	KeypadButtonChar_Init(3, 0, "1");
	KeypadButtonChar_Init(2, 0, "2ABC");
	KeypadButtonChar_Init(1, 0, "3DEF");
	KeypadButtonChar_Init(3, 1, "4GHI");
	KeypadButtonChar_Init(2, 1, "5JKL");
	KeypadButtonChar_Init(1, 1, "6MNO");
	KeypadButtonChar_Init(3, 2, "7PQRS");
	KeypadButtonChar_Init(2, 2, "8TUV");
	KeypadButtonChar_Init(1, 2, "9WXYZ");
	KeypadButtonKeyCode_Init(3, 3, GUI_KEY_DELETE);	// DEL
	KeypadButtonChar_Init(2, 3, "0 ");
	KeypadButtonKeyCode_Init(1, 3, GUI_KEY_ENTER);	// ENTER

}
void KeypadButtonKeyCode_Init(uint32_t i, uint32_t j, const char value) {
	KP_Btn[i][j].KeypadBtnType = KeyCode;
	KP_Btn[i][j].Val.chars[0] = value;
	KP_Btn[i][j].Val.chars[1] = (char) 0;

}
void KeypadButtonChar_Init(uint32_t i, uint32_t j, const char * ch) {
	KP_Btn[i][j].KeypadBtnType = Char;
	strcpy(KP_Btn[i][j].Val.chars, ch);
}


