/*
 * keypad_config.h
 *
 *  Created on: Nov 28, 2018
 *      Author: HP
 */

#ifndef KEYPAD_KEYPAD_CONFIG_H_
#define KEYPAD_KEYPAD_CONFIG_H_


#define HoldKeyTime			800
#define HoldKeyLatencyTime	200
#define DoubleClickTime		1000
#define KeyPadProccessTime	50

#define KP_R0_PIN							GPIO_PIN_11
#define KP_R1_PIN							GPIO_PIN_13
#define KP_R2_PIN							GPIO_PIN_14
#define KP_R3_PIN							GPIO_PIN_15
#define KP_R0_PORT							GPIOG
#define KP_R1_PORT							GPIOG
#define KP_R2_PORT							GPIOG
#define KP_R3_PORT							GPIOG

#define KP_C0_PIN							GPIO_PIN_2
#define KP_C1_PIN							GPIO_PIN_3
#define KP_C2_PIN							GPIO_PIN_4
#define KP_C3_PIN							GPIO_PIN_5
#define KP_C0_PORT							GPIOE
#define KP_C1_PORT							GPIOE
#define KP_C2_PORT							GPIOE
#define KP_C3_PORT							GPIOE

#define KP_R_IRQn  		              		EXTI15_10_IRQn
#define KP_R_IRQHANDLER 	            	EXTI15_10_IRQHandler

#define KP_R_GPIO_CLK_ENABLE()           	__HAL_RCC_GPIOE_CLK_ENABLE()
#define KP_R_GPIO_CLK_DISABLE()         	__HAL_RCC_GPIOE_CLK_DISABLE()
#define KP_C_GPIO_CLK_ENABLE()           	__HAL_RCC_GPIOG_CLK_ENABLE()
#define KP_C_GPIO_CLK_DISABLE()          	__HAL_RCC_GPIOG_CLK_DISABLE()

#endif /* KEYPAD_KEYPAD_CONFIG_H_ */
