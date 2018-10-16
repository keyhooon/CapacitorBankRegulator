/**
  ******************************************************************************
  * @file    stm3210c_eval.c
  * @author  MCD Application Team
  * @version V6.1.0
  * @date    14-April-2017
  * @brief   This file provides a set of firmware functions to manage Leds,
 *          push-button and COM ports for STM3210C_BOARD
  ******************************************************************************
  * @attention
  *
  * <h2><center>&copy; COPYRIGHT(c) 2016 STMicroelectronics</center></h2>
  *
  * Redistribution and use in source and binary forms, with or without modification,
  * are permitted provided that the following conditions are met:
  *   1. Redistributions of source code must retain the above copyright notice,
  *      this list of conditions and the following disclaimer.
  *   2. Redistributions in binary form must reproduce the above copyright notice,
  *      this list of conditions and the following disclaimer in the documentation
  *      and/or other materials provided with the distribution.
  *   3. Neither the name of STMicroelectronics nor the names of its contributors
  *      may be used to endorse or promote products derived from this software
  *      without specific prior written permission.
  *
  * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
  * AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
  * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
  * DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
  * FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
  * DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR
  * SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER
  * CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY,
  * OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
  * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "Board.h"


typedef struct
{
  __IO uint16_t REG; /* Read Register */
  __IO uint16_t RAM; /* Read RAM */
} TFT_LCD_TypeDef;

/* LINK SD Card */
#define SD_DUMMY_BYTE      0xFF
#define SD_NO_RESPONSE_EXPECTED  0x80

/**
 * @brief STM3210C BOARD BSP Driver version number
   */
#define __STM3210C_BOARD_BSP_VERSION_MAIN       (0x06) /*!< [31:24] main version */
#define __STM3210C_BOARD_BSP_VERSION_SUB1       (0x01) /*!< [23:16] sub1 version */
#define __STM3210C_BOARD_BSP_VERSION_SUB2       (0x00) /*!< [15:8]  sub2 version */
#define __STM3210C_BOARD_BSP_VERSION_RC         (0x00) /*!< [7:0]  release candidate */
#define __STM3210C_BOARD_BSP_VERSION            ((__STM3210C_BOARD_BSP_VERSION_MAIN << 24)\
                                               |(__STM3210C_BOARD_BSP_VERSION_SUB1 << 16)\
                                               |(__STM3210C_BOARD_BSP_VERSION_SUB2 << 8 )\
                                               |(__STM3210C_BOARD_BSP_VERSION_RC))


/* Note: LCD /CS is CE4 - Bank 4 of NOR/SRAM Bank 1~4 */
#define TFT_LCD_BASE           FSMC_BANK1_4
#define TFT_LCD                ((TFT_LCD_TypeDef *) TFT_LCD_BASE)

/**
  * @}
  */


/** @defgroup STM3210C_BOARD_Private_Variables STM3210C BOARD Private Variables
  * @{
  */
/**
 * @brief LED variables
 */
GPIO_TypeDef* LED_PORT[LEDn] = {LED1_GPIO_PORT,
                                LED2_GPIO_PORT,
                                LED3_GPIO_PORT,
                                LED4_GPIO_PORT};

const uint16_t LED_PIN[LEDn] = {LED1_PIN,
                                LED2_PIN,
                                LED3_PIN,
                                LED4_PIN};

/**
 * @brief BUTTON variables
 */
GPIO_TypeDef* BUTTON_PORT[BUTTONn] = {WAKEUP_BUTTON_GPIO_PORT,
                                      TAMPER_BUTTON_GPIO_PORT,
KEY1_BUTTON_GPIO_PORT, KEY2_BUTTON_GPIO_PORT };

const uint16_t BUTTON_PIN[BUTTONn] = {WAKEUP_BUTTON_PIN,
                                      TAMPER_BUTTON_PIN,
KEY1_BUTTON_PIN,
KEY2_BUTTON_PIN };

const uint16_t BUTTON_IRQn[BUTTONn] = {WAKEUP_BUTTON_EXTI_IRQn,
                                       TAMPER_BUTTON_EXTI_IRQn,
KEY1_BUTTON_EXTI_IRQn,
KEY2_BUTTON_EXTI_IRQn };

uint16_t KP_C_PINs[4] = { KP_C0_PIN, KP_C1_PIN, KP_C2_PIN, KP_C3_PIN };
uint16_t KP_R_PINs[4] = { KP_R0_PIN, KP_R1_PIN, KP_R2_PIN, KP_R3_PIN };
GPIO_TypeDef * KP_C_Ports[4] = { KP_C0_PORT, KP_C1_PORT, KP_C2_PORT,
KP_C3_PORT };
GPIO_TypeDef * KP_R_Ports[4] = { KP_R0_PORT, KP_R1_PORT, KP_R2_PORT,
KP_R3_PORT };

/**
 * @brief COM variables
 */
USART_TypeDef* COM_USART[COMn] = { BOARD_COM1 };



GPIO_TypeDef* COM_TX_PORT[COMn] = { BOARD_COM1_TX_GPIO_PORT };

GPIO_TypeDef* COM_RX_PORT[COMn] = { BOARD_COM1_RX_GPIO_PORT };

const uint16_t COM_TX_PIN[COMn] = { BOARD_COM1_TX_PIN };

const uint16_t COM_RX_PIN[COMn] = { BOARD_COM1_RX_PIN };

/**
 * @brief BUS variables
 */
#ifdef HAL_SPI_MODULE_ENABLED
uint32_t SpixTimeout = BOARD_SPI1_TIMEOUT_MAX; /*<! Value of Timeout when SPI communication fails */
static SPI_HandleTypeDef hboard_Spi1;
static SPI_HandleTypeDef hboard_Spi2;

#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
uint32_t I2cxTimeout = BOARD_I2Cx_TIMEOUT_MAX; /*<! Value of Timeout when I2C communication fails */
I2C_HandleTypeDef hboard_I2c;
#endif /* HAL_I2C_MODULE_ENABLED */



static uint32_t FSMC_Initialized = 0;

TIM_HandleTypeDef htim5;
TIM_HandleTypeDef htim1;


/* I2Cx bus function */
#ifdef HAL_I2C_MODULE_ENABLED
/* Link function for I2C EEPROM peripheral */
static void I2Cx_Init(void);
static void I2Cx_ITConfig(void);
static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg,
		uint16_t MemAddress, uint8_t *Buffer, uint16_t Length);
static HAL_StatusTypeDef I2Cx_ReadBuffer(uint16_t Addr, uint8_t Reg,
		uint16_t RegSize, uint8_t *pBuffer, uint16_t Length);
static void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value);
static HAL_StatusTypeDef I2Cx_WriteBuffer(uint16_t Addr, uint8_t Reg,
		uint16_t RegSize, uint8_t *pBuffer, uint16_t Length);
static uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg);
static HAL_StatusTypeDef I2Cx_IsDeviceReady(uint16_t DevAddress,
		uint32_t Trials);
static void I2Cx_Error(uint8_t Addr);
static void I2Cx_MspInit(I2C_HandleTypeDef *hi2c);

/* Link function for EEPROM peripheral over I2C */
void EEPROM_I2C_IO_Init(void);
HAL_StatusTypeDef EEPROM_I2C_IO_WriteData(uint16_t DevAddress,
		uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef EEPROM_I2C_IO_ReadData(uint16_t DevAddress,
		uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize);
HAL_StatusTypeDef EEPROM_I2C_IO_IsDeviceReady(uint16_t DevAddress,
		uint32_t Trials);


#endif /* HAL_I2C_MODULE_ENABLED */

/* SPIx bus function */
#ifdef HAL_SPI_MODULE_ENABLED
HAL_StatusTypeDef SPI1_Init(void);
static uint8_t SPI1_Write(uint8_t WriteValue);
static uint8_t SPI1_Read(void);
static void SPI1_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut,
		uint16_t DataLength);
static void SPI1_WriteData(const uint8_t *Data, uint16_t DataLength);
static void SPI1_ReadData(const uint8_t *Data, uint16_t DataLength);
static void SPI1_Error(void);
static void SPI1_MspInit(SPI_HandleTypeDef *hspi);

static void SPI2_Init(void);
static void SPI2_WriteData(uint8_t *DataIn, uint16_t DataLength);
static void SPI2_Write(uint8_t Value);
static void SPI2_ReadData(const uint8_t *Data, uint16_t DataLength);
static void SPI2_Error(void);



/* Link function for LCD2 peripheral over SPI */
void LCD_IO_Init(void);
void LCD_IO_WriteData(uint8_t RegValue);

void LCD_IO_WriteMultipleData(uint8_t *pData, uint32_t Size);
void LCD_IO_ReadReg(uint8_t Reg, uint8_t *Data, uint16_t DataLength);
void LCD_IO_WriteReg(uint8_t Reg);
void LCD_Delay(uint32_t delay);

#endif /* HAL_SPI_MODULE_ENABLED */



/* TIMx bus function */
void TIM5_Init();
void TIM5_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle);
void TIM1_Init();
void TIM1_PWM_MspInit(TIM_HandleTypeDef* tim_pwmHandle);

#if defined(HAL_SRAM_MODULE_ENABLED)

static void     FSMC_BANK1NORSRAM4_WriteData(uint16_t Data);
static void     FSMC_BANK1NORSRAM4_WriteReg(uint8_t Reg);
static uint16_t FSMC_BANK1NORSRAM4_ReadData();
static void     FSMC_BANK1NORSRAM4_Init(void);
static void     FSMC_BANK1NORSRAM4_MspInit(void);

/* Link function for LCD peripheral over FMSC */
void LCDex_IO_Init(void);
void LCDex_IO_WriteData(uint16_t RegValue);
void LCDex_IO_WriteMultipleData(uint16_t *pData, uint32_t Size);
void LCDex_IO_ReadMultipleData(uint16_t *pData, uint32_t Size);
void LCDex_IO_WriteReg(uint8_t Reg);
uint16_t LCDex_IO_ReadData();
void LCDex_Delay(uint32_t delay);
#endif /*HAL_SRAM_MODULE_ENABLED*/




/** @defgroup STM3210C_BOARD_Exported_Functions STM3210C BOARD Exported Functions
  * @{
  */

/**
 * @brief  This method returns the STM3210C BOARD BSP Driver revision
  * @retval version : 0xXYZR (8bits for each decimal, R for RC)
  */
uint32_t BSP_GetVersion(void)
{
	return __STM3210C_BOARD_BSP_VERSION;
}

/**
  * @brief  Configures LED GPIO.
  * @param  Led: Specifies the Led to be configured.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  */
void BSP_LED_Init(Led_TypeDef Led)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};

  /* Enable the GPIO_LED clock */
  LEDx_GPIO_CLK_ENABLE(Led);

  /* Configure the GPIO_LED pin */
  gpioinitstruct.Pin    = LED_PIN[Led];
  gpioinitstruct.Mode   = GPIO_MODE_OUTPUT_PP;
  gpioinitstruct.Pull   = GPIO_NOPULL;
  gpioinitstruct.Speed  = GPIO_SPEED_FREQ_HIGH;

  HAL_GPIO_Init(LED_PORT[Led], &gpioinitstruct);

  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET);
}

/**
  * @brief  Turns selected LED On.
  * @param  Led: Specifies the Led to be set on.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  */
void BSP_LED_On(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_SET);
}

/**
  * @brief  Turns selected LED Off.
  * @param  Led: Specifies the Led to be set off.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  */
void BSP_LED_Off(Led_TypeDef Led)
{
  HAL_GPIO_WritePin(LED_PORT[Led], LED_PIN[Led], GPIO_PIN_RESET);
}

/**
  * @brief  Toggles the selected LED.
  * @param  Led: Specifies the Led to be toggled.
  *   This parameter can be one of following parameters:
  *     @arg LED1
  *     @arg LED2
  *     @arg LED3
  *     @arg LED4
  * @retval None
  */
void BSP_LED_Toggle(Led_TypeDef Led)
{
  HAL_GPIO_TogglePin(LED_PORT[Led], LED_PIN[Led]);
}

/**
  * @brief  Configures push button GPIO and EXTI Line.
  * @param  Button: Button to be configured.
  *   This parameter can be one of the following values:
  *     @arg BUTTON_WAKEUP: Wakeup Push Button
  *     @arg BUTTON_TAMPER: Tamper Push Button
  *     @arg BUTTON_KEY: Key Push Button
  * @param  Button_Mode: Button mode requested.
  *   This parameter can be one of the following values:
  *     @arg BUTTON_MODE_GPIO: Button will be used as simple IO
  *     @arg BUTTON_MODE_EXTI: Button will be connected to EXTI line
  *                            with interrupt generation capability
  */
void BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode)
{
  GPIO_InitTypeDef gpioinitstruct = {0};

  /* Enable the corresponding Push Button clock */
  BUTTONx_GPIO_CLK_ENABLE(Button);

  /* Configure Push Button pin as input */
  gpioinitstruct.Pin    = BUTTON_PIN[Button];
  gpioinitstruct.Pull   = GPIO_NOPULL;
  gpioinitstruct.Speed  = GPIO_SPEED_FREQ_HIGH;

  if (Button_Mode == BUTTON_MODE_GPIO)
  {
    /* Configure Button pin as input */
    gpioinitstruct.Mode = GPIO_MODE_INPUT;
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpioinitstruct);
  }
  else if (Button_Mode == BUTTON_MODE_EXTI)
  {
    if(Button != BUTTON_WAKEUP)
    {
      /* Configure Joystick Button pin as input with External interrupt, falling edge */
			gpioinitstruct.Mode = GPIO_MODE_IT_RISING_FALLING;
    }
    else
    {
      /* Configure Key Push Button pin as input with External interrupt, rising edge */
			gpioinitstruct.Mode = GPIO_MODE_IT_RISING;
    }
    HAL_GPIO_Init(BUTTON_PORT[Button], &gpioinitstruct);

    /* Enable and set Button EXTI Interrupt to the lowest priority */
		HAL_NVIC_SetPriority((IRQn_Type) (BUTTON_IRQn[Button]), 0x0A, 0);
    HAL_NVIC_EnableIRQ((IRQn_Type)(BUTTON_IRQn[Button]));
  }
}

/**
  * @brief  Returns the selected button state.
  * @param  Button: Button to be checked.
  *   This parameter can be one of the following values:
  *     @arg BUTTON_TAMPER: Key/Tamper Push Button
  * @retval Button state
  */
uint32_t BSP_PB_GetState(Button_TypeDef Button)
{
  return HAL_GPIO_ReadPin(BUTTON_PORT[Button], BUTTON_PIN[Button]);
}

#ifdef HAL_I2C_MODULE_ENABLED

#endif /*HAL_I2C_MODULE_ENABLED*/

void KEYPAD_IO_Init(void) {

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

	HAL_NVIC_SetPriority(KP_R_EXTI_IRQn, 0x0A, 0x00);
	HAL_NVIC_EnableIRQ(KP_R_EXTI_IRQn);

}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == GPIO_PIN_11 || GPIO_Pin == GPIO_PIN_13
			|| GPIO_Pin == GPIO_PIN_14 || GPIO_Pin == GPIO_PIN_15)
		KEYPAD_EXTI_Callback(GPIO_Pin);
	if (GPIO_Pin == BUTTON_PIN[2])
		BSP_PB_EXTI_Callback(BUTTON_KEY1,
				HAL_GPIO_ReadPin(BUTTON_PORT[2], BUTTON_PIN[2]));
	if (GPIO_Pin == BUTTON_PIN[3])
		BSP_PB_EXTI_Callback(BUTTON_KEY2,
				HAL_GPIO_ReadPin(BUTTON_PORT[3], BUTTON_PIN[3]));


}

/**
  * @}
  */

/** @defgroup STM3210C_BOARD_BusOperations_Functions STM3210C BOARD BusOperations Functions
  * @{
  */

/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

void TIM5_Init() {
	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;
	TIM_OC_InitTypeDef sConfigOC;
	htim5.Instance = TIM5;
	htim5.Init.Prescaler = 72 - 1;
	htim5.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim5.Init.Period = 1000;
	htim5.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim5.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	TIM5_PWM_MspInit(&htim5);
	if (HAL_TIM_Base_Init(&htim5) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim5, &sClockSourceConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	if (HAL_TIM_PWM_Init(&htim5) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim5, &sMasterConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 500;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	if (HAL_TIM_PWM_ConfigChannel(&htim5, &sConfigOC, TIM_CHANNEL_2)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}




}

void TIM5_PWM_MspInit(TIM_HandleTypeDef* tim_Handle) {
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_TIM5_CLK_ENABLE()
	;
	LCDex_BL_GPIO_CLK_ENABLE()
	;
		GPIO_InitStruct.Pin = LCDex_BL_Pin;
	    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
		HAL_GPIO_Init(LCDex_BL_GPIO_Port, &GPIO_InitStruct);
		;

}


void TIM1_Init() {

	TIM_ClockConfigTypeDef sClockSourceConfig;
	TIM_MasterConfigTypeDef sMasterConfig;
	TIM_OC_InitTypeDef sConfigOC;

	htim1.Instance = TIM1;
	htim1.Init.Prescaler = 72 - 1;
	htim1.Init.CounterMode = TIM_COUNTERMODE_UP;
	htim1.Init.Period = 1000;
	htim1.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
	htim1.Init.AutoReloadPreload = TIM_AUTORELOAD_PRELOAD_DISABLE;
	TIM1_PWM_MspInit(&htim1);
	if (HAL_TIM_Base_Init(&htim1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sClockSourceConfig.ClockSource = TIM_CLOCKSOURCE_INTERNAL;
	if (HAL_TIM_ConfigClockSource(&htim1, &sClockSourceConfig) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	if (HAL_TIM_PWM_Init(&htim1) != HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sMasterConfig.MasterOutputTrigger = TIM_TRGO_RESET;
	sMasterConfig.MasterSlaveMode = TIM_MASTERSLAVEMODE_DISABLE;
	if (HAL_TIMEx_MasterConfigSynchronization(&htim1, &sMasterConfig)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}

	sConfigOC.OCMode = TIM_OCMODE_PWM1;
	sConfigOC.Pulse = 500;
	sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
	sConfigOC.OCNPolarity = TIM_OCNPOLARITY_HIGH;
	sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
	sConfigOC.OCIdleState = TIM_OCIDLESTATE_RESET;
	sConfigOC.OCNIdleState = TIM_OCNIDLESTATE_RESET;
	if (HAL_TIM_PWM_ConfigChannel(&htim1, &sConfigOC, TIM_CHANNEL_2)
			!= HAL_OK) {
		_Error_Handler(__FILE__, __LINE__);
	}




}

void TIM1_PWM_MspInit(TIM_HandleTypeDef* tim_Handle) {
	GPIO_InitTypeDef GPIO_InitStruct;
	__HAL_RCC_TIM1_CLK_ENABLE()
	;
	LCD_BL_GPIO_CLK_ENABLE()
	;
	GPIO_InitStruct.Pin = LCD_BL_Pin;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
	HAL_GPIO_Init(LCD_BL_GPIO_Port, &GPIO_InitStruct);

}


/*******************************************************************************
                            BUS OPERATIONS
*******************************************************************************/

/*************************** FSMC Routines ************************************/
#if defined(HAL_SRAM_MODULE_ENABLED)
/**
  * @brief  Initializes FSMC_BANK4 MSP.
  */
static void FSMC_MspInit(void){
	/* USER CODE BEGIN FSMC_MspInit 0 */

	/* USER CODE END FSMC_MspInit 0 */
	GPIO_InitTypeDef GPIO_InitStruct;
	if (FSMC_Initialized) {
		return;
	}
	FSMC_Initialized = 1;
	/* Peripheral clock enable */
	__HAL_RCC_FSMC_CLK_ENABLE()
	;

	/** FSMC GPIO Configuration
	 PF0   ------> FSMC_A0
	 PF1   ------> FSMC_A1
	 PF2   ------> FSMC_A2
	 PF3   ------> FSMC_A3
	 PF4   ------> FSMC_A4
	 PF5   ------> FSMC_A5
	 PF12   ------> FSMC_A6
	 PF13   ------> FSMC_A7
	 PF14   ------> FSMC_A8
	 PF15   ------> FSMC_A9
	 PG0   ------> FSMC_A10
	 PG1   ------> FSMC_A11
	 PE7   ------> FSMC_D4
	 PE8   ------> FSMC_D5
	 PE9   ------> FSMC_D6
	 PE10   ------> FSMC_D7
	 PE11   ------> FSMC_D8
	 PE12   ------> FSMC_D9
	 PE13   ------> FSMC_D10
	 PE14   ------> FSMC_D11
	 PE15   ------> FSMC_D12
	 PD8   ------> FSMC_D13
	 PD9   ------> FSMC_D14
	 PD10   ------> FSMC_D15
	 PD11   ------> FSMC_A16
	 PD11   ------> FSMC_CLE
	 PD12   ------> FSMC_A17
	 PD12   ------> FSMC_ALE
	 PD14   ------> FSMC_D0
	 PD15   ------> FSMC_D1
	 PG2   ------> FSMC_A12
	 PG3   ------> FSMC_A13
	 PG4   ------> FSMC_A14
	 PG5   ------> FSMC_A15
	 PG6   ------> FSMC_INT2
	 PD0   ------> FSMC_D2
	 PD1   ------> FSMC_D3
	 PD4   ------> FSMC_NOE
	 PD5   ------> FSMC_NWE
	 PD6   ------> FSMC_NWAIT
	 PD7   ------> FSMC_NCE2
	 PG9   ------> FSMC_NE2
	 PG10   ------> FSMC_NE3
	 PG12   ------> FSMC_NE4
	 PE0   ------> FSMC_NBL0
	 PE1   ------> FSMC_NBL1
	 */
	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
			| GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14
			| GPIO_PIN_15;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(GPIOF, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_0 | GPIO_PIN_1 | GPIO_PIN_2 | GPIO_PIN_3
			| GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_12;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_7 | GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10
			| GPIO_PIN_11 | GPIO_PIN_12 | GPIO_PIN_13 | GPIO_PIN_14
			| GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_8 | GPIO_PIN_9 | GPIO_PIN_10 | GPIO_PIN_11
			| GPIO_PIN_12 | GPIO_PIN_14 | GPIO_PIN_15 | GPIO_PIN_0 | GPIO_PIN_1
			| GPIO_PIN_4 | GPIO_PIN_5 | GPIO_PIN_7;
	GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
	GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;

	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOG, &GPIO_InitStruct);

	/* GPIO_InitStruct */
	GPIO_InitStruct.Pin = GPIO_PIN_6;
	GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
	GPIO_InitStruct.Pull = GPIO_NOPULL;

	HAL_GPIO_Init(GPIOD, &GPIO_InitStruct);

	/* USER CODE BEGIN FSMC_MspInit 1 */

	/* USER CODE END FSMC_MspInit 1 */
}




static void FSMC_BANK1NORSRAM4_MspInit(void)
{
	  FSMC_MspInit();
}

/**
  * @brief  Initializes LCD IO.
  */
static void FSMC_BANK1NORSRAM4_Init(void)
{
  SRAM_HandleTypeDef          hsram;
  FSMC_NORSRAM_TimingTypeDef  sramtiming = {0};

  /*** Configure the SRAM Bank 4 ***/
  /* Configure IPs */
  hsram.Instance  = FSMC_NORSRAM_DEVICE;
  hsram.Extended  = FSMC_NORSRAM_EXTENDED_DEVICE;

	sramtiming.AddressSetupTime = 1;
	sramtiming.AddressHoldTime = 0;
	sramtiming.DataSetupTime = 1;
	sramtiming.BusTurnAroundDuration = 0;
	sramtiming.CLKDivision = 0;
	sramtiming.DataLatency = 0;
  sramtiming.AccessMode             = FSMC_ACCESS_MODE_A;

  /* Color LCD configuration
     LCD configured as follow:
        - Data/Address MUX = Disable
        - Memory Type = SRAM
        - Data Width = 16bit
        - Write Operation = Enable
        - Extended Mode = Enable
        - Asynchronous Wait = Disable */
  hsram.Init.NSBank             = FSMC_NORSRAM_BANK4;
  hsram.Init.DataAddressMux     = FSMC_DATA_ADDRESS_MUX_DISABLE;
  hsram.Init.MemoryType         = FSMC_MEMORY_TYPE_SRAM;
  hsram.Init.MemoryDataWidth    = FSMC_NORSRAM_MEM_BUS_WIDTH_16;
  hsram.Init.BurstAccessMode    = FSMC_BURST_ACCESS_MODE_DISABLE;
  hsram.Init.WaitSignalPolarity = FSMC_WAIT_SIGNAL_POLARITY_LOW;
  hsram.Init.WrapMode           = FSMC_WRAP_MODE_DISABLE;
  hsram.Init.WaitSignalActive   = FSMC_WAIT_TIMING_BEFORE_WS;
  hsram.Init.WriteOperation     = FSMC_WRITE_OPERATION_ENABLE;
  hsram.Init.WaitSignal         = FSMC_WAIT_SIGNAL_DISABLE;
  hsram.Init.ExtendedMode       = FSMC_EXTENDED_MODE_DISABLE;
  hsram.Init.AsynchronousWait   = FSMC_ASYNCHRONOUS_WAIT_DISABLE;
  hsram.Init.WriteBurst         = FSMC_WRITE_BURST_DISABLE;

  /* Initialize the SRAM controller */
  FSMC_BANK1NORSRAM4_MspInit();

  HAL_SRAM_Init(&hsram, &sramtiming, &sramtiming);
}

/**
  * @brief  Writes register value.
  */
static void FSMC_BANK1NORSRAM4_WriteData(uint16_t Data)
{
  /* Write 16-bit Data */
  TFT_LCD->RAM = Data;
}

/**
  * @brief  Writes register address.
  * @param  Reg:
  * @retval None
  */
static void FSMC_BANK1NORSRAM4_WriteReg(uint8_t Reg)
{
  /* Write 16-bit Index, then Write Reg */
  TFT_LCD->REG = Reg;
}

/**
  * @brief  Reads register value.
  * @retval Read value
  */
static uint16_t FSMC_BANK1NORSRAM4_ReadData()
{
  /* Read 16-bit Reg */
  return (TFT_LCD->RAM);
}

#endif /*HAL_SRAM_MODULE_ENABLED*/


#ifdef HAL_I2C_MODULE_ENABLED
/******************************* I2C Routines**********************************/

/**
  * @brief Eval I2Cx MSP Initialization
  * @param hi2c: I2C handle
  */
static void I2Cx_MspInit(I2C_HandleTypeDef *hi2c)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};

	if (hi2c->Instance == BOARD_I2Cx)
  {
    /*## Configure the GPIOs ################################################*/

    /* Enable GPIO clock */
		BOARD_I2Cx_SDA_GPIO_CLK_ENABLE()
		;
		BOARD_I2Cx_SCL_GPIO_CLK_ENABLE()
		;

    /* Configure I2C Tx as alternate function  */
		gpioinitstruct.Pin = BOARD_I2Cx_SCL_PIN;
    gpioinitstruct.Mode      = GPIO_MODE_AF_OD;
    gpioinitstruct.Pull      = GPIO_NOPULL;
    gpioinitstruct.Speed     = GPIO_SPEED_FREQ_HIGH;
		HAL_GPIO_Init(BOARD_I2Cx_SCL_GPIO_PORT, &gpioinitstruct);

    /* Configure I2C Rx as alternate function  */
		gpioinitstruct.Pin = BOARD_I2Cx_SDA_PIN;
		HAL_GPIO_Init(BOARD_I2Cx_SDA_GPIO_PORT, &gpioinitstruct);

    /*## Configure the Eval I2Cx peripheral #######################################*/
    /* Enable Eval_I2Cx clock */
		BOARD_I2Cx_CLK_ENABLE()
		;

    /* Add delay related to RCC workaround */
    while (READ_BIT(RCC->APB1ENR, RCC_APB1ENR_I2C1EN) != RCC_APB1ENR_I2C1EN) {};

    /* Force the I2C Periheral Clock Reset */
		BOARD_I2Cx_FORCE_RESET();

    /* Release the I2C Periheral Clock Reset */
		BOARD_I2Cx_RELEASE_RESET();

    /* Enable and set Eval I2Cx Interrupt to the highest priority */
		HAL_NVIC_SetPriority(BOARD_I2Cx_EV_IRQn, 0xE, 0);
		HAL_NVIC_EnableIRQ(BOARD_I2Cx_EV_IRQn);

    /* Enable and set Eval I2Cx Interrupt to the highest priority */
		HAL_NVIC_SetPriority(BOARD_I2Cx_ER_IRQn, 0xE, 0);
		HAL_NVIC_EnableIRQ(BOARD_I2Cx_ER_IRQn);
  }
}

/**
  * @brief Eval I2Cx Bus initialization
  */
static void I2Cx_Init(void)
{
	if (HAL_I2C_GetState(&hboard_I2c) == HAL_I2C_STATE_RESET)
  {
		hboard_I2c.Instance = BOARD_I2Cx;
		hboard_I2c.Init.ClockSpeed = BSP_I2C_SPEED;
		hboard_I2c.Init.DutyCycle = I2C_DUTYCYCLE_2;
		hboard_I2c.Init.OwnAddress1 = 0;
		hboard_I2c.Init.AddressingMode = I2C_ADDRESSINGMODE_7BIT;
		hboard_I2c.Init.DualAddressMode = I2C_DUALADDRESS_DISABLE;
		hboard_I2c.Init.OwnAddress2 = 0;
		hboard_I2c.Init.GeneralCallMode = I2C_GENERALCALL_DISABLE;
		hboard_I2c.Init.NoStretchMode = I2C_NOSTRETCH_DISABLE;

    /* Init the I2C */
		I2Cx_MspInit(&hboard_I2c);
		HAL_I2C_Init(&hboard_I2c);
  }
}

/**
  * @brief  Configures I2C Interrupt.
  */
static void I2Cx_ITConfig(void)
{
  static uint8_t I2C_IT_Enabled = 0;
  GPIO_InitTypeDef  gpioinitstruct = {0};

  if(I2C_IT_Enabled == 0)
  {
    I2C_IT_Enabled = 1;

    /* Enable the GPIO EXTI clock */
    IOE_IT_GPIO_CLK_ENABLE();

    gpioinitstruct.Pin   = IOE_IT_PIN;
    gpioinitstruct.Pull  = GPIO_NOPULL;
    gpioinitstruct.Speed = GPIO_SPEED_FREQ_HIGH;
    gpioinitstruct.Mode  = GPIO_MODE_IT_FALLING;
    HAL_GPIO_Init(IOE_IT_GPIO_PORT, &gpioinitstruct);

    /* Set priority and Enable GPIO EXTI Interrupt */
    HAL_NVIC_SetPriority((IRQn_Type)(IOE_IT_EXTI_IRQn), 0xE, 0);
    HAL_NVIC_EnableIRQ((IRQn_Type)(IOE_IT_EXTI_IRQn));
  }
}

/**
  * @brief  Reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  MemAddress: Internal memory address
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
static HAL_StatusTypeDef I2Cx_ReadMultiple(uint8_t Addr, uint16_t Reg, uint16_t MemAddress, uint8_t *Buffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Read(&hboard_I2c, Addr, (uint16_t) Reg, MemAddress,
			Buffer, Length, I2cxTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* I2C error occured */
    I2Cx_Error(Addr);
  }
  return status;
}

/**
  * @brief  Write a value in a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.
  * @param  Reg: The target register address to write
  * @param  Value: The target register value to be written
  */
static void I2Cx_WriteData(uint16_t Addr, uint8_t Reg, uint8_t Value)
{
  HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Write(&hboard_I2c, Addr, (uint16_t) Reg,
			I2C_MEMADD_SIZE_8BIT, &Value, 1, I2cxTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);
  }
}

/**
  * @brief  Write a value in a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.
  * @param  Reg: The target register address to write
  * @param  RegSize: The target register size (can be 8BIT or 16BIT)
  * @param  pBuffer: The target register value to be written
  * @param  Length: buffer size to be written
  */
static HAL_StatusTypeDef I2Cx_WriteBuffer(uint16_t Addr, uint8_t Reg, uint16_t RegSize, uint8_t *pBuffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Write(&hboard_I2c, Addr, (uint16_t) Reg, RegSize,
			pBuffer, Length, I2cxTimeout);

/* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initiaize the BUS */
    I2Cx_Error(Addr);
  }
  return status;
}

/**
  * @brief  Read a value in a register of the device through BUS.
  * @param  Addr: Device address on BUS Bus.
  * @param  Reg: The target register address to write
  * @retval Data read at register @
  */
static uint8_t I2Cx_ReadData(uint16_t Addr, uint8_t Reg)
{
  HAL_StatusTypeDef status = HAL_OK;
  uint8_t value = 0;

	status = HAL_I2C_Mem_Read(&hboard_I2c, Addr, Reg, I2C_MEMADD_SIZE_8BIT,
			&value, 1, I2cxTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
    I2Cx_Error(Addr);

  }
  return value;
}

/**
  * @brief  Reads multiple data on the BUS.
  * @param  Addr: I2C Address
  * @param  Reg: Reg Address
  * @param  RegSize : The target register size (can be 8BIT or 16BIT)
  * @param  pBuffer: pointer to read data buffer
  * @param  Length: length of the data
  * @retval 0 if no problems to read multiple data
  */
static HAL_StatusTypeDef I2Cx_ReadBuffer(uint16_t Addr, uint8_t Reg, uint16_t RegSize, uint8_t *pBuffer, uint16_t Length)
{
  HAL_StatusTypeDef status = HAL_OK;

	status = HAL_I2C_Mem_Read(&hboard_I2c, Addr, (uint16_t) Reg, RegSize,
			pBuffer, Length, I2cxTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Re-Initiaize the BUS */
    I2Cx_Error(Addr);
  }
  return status;
}

/**
* @brief  Checks if target device is ready for communication.
* @note   This function is used with Memory devices
* @param  DevAddress: Target device address
* @param  Trials: Number of trials
* @retval HAL status
*/
static HAL_StatusTypeDef I2Cx_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{
	return (HAL_I2C_IsDeviceReady(&hboard_I2c, DevAddress, Trials, I2cxTimeout));
}

/**
  * @brief  Manages error callback by re-initializing I2C.
  * @param  Addr: I2C Address
  */
static void I2Cx_Error(uint8_t Addr)
{
  /* De-initialize the IOE comunication BUS */
	HAL_I2C_DeInit(&hboard_I2c);

  /* Re-Initiaize the IOE comunication BUS */
  I2Cx_Init();
}

#endif /* HAL_I2C_MODULE_ENABLED */
/******************************* SPI Routines**********************************/
#ifdef HAL_SPI_MODULE_ENABLED
/**
  * @brief  Initializes SPI MSP.
  */
static void SPI1_MspInit(SPI_HandleTypeDef *hspi)
{
  GPIO_InitTypeDef  gpioinitstruct = {0};

	/*** Configure the GPIOs ***/
  /* Enable GPIO clock */
	BOARD_SPI1_SCK_GPIO_CLK_ENABLE()
	;
	BOARD_SPI1_MISO_MOSI_GPIO_CLK_ENABLE()
	;

  /* configure SPI SCK */
	gpioinitstruct.Pin = BOARD_SPI1_SCK_PIN;
  gpioinitstruct.Mode       = GPIO_MODE_AF_PP;
	gpioinitstruct.Pull = GPIO_NOPULL;
  gpioinitstruct.Speed      = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BOARD_SPI1_SCK_GPIO_PORT, &gpioinitstruct);

	/* configure SPI MISO and MOSI */
	gpioinitstruct.Pin = (BOARD_SPI1_MISO_PIN | BOARD_SPI1_MOSI_PIN);
  gpioinitstruct.Mode       = GPIO_MODE_AF_PP;
	gpioinitstruct.Pull = GPIO_NOPULL;
  gpioinitstruct.Speed      = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BOARD_SPI1_MISO_MOSI_GPIO_PORT, &gpioinitstruct);

	/*** Configure the SPI peripheral ***/
  /* Enable SPI clock */
	BOARD_SPI1_CLK_ENABLE()
	;
}

/**
  * @brief  Initializes SPI HAL.
  */
HAL_StatusTypeDef SPI1_Init(void)
{
	/* DeInitializes the SPI peripheral */
	hboard_Spi1.Instance = BOARD_SPI1;
	HAL_SPI_DeInit(&hboard_Spi1);

	/* SPI Config */
	/* SPI baudrate is set to 36 MHz (PCLK2/SPI_BaudRatePrescaler = 72/2 = 36 MHz) */
	hboard_Spi1.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_2;
	hboard_Spi1.Init.Direction = SPI_DIRECTION_2LINES;
	hboard_Spi1.Init.CLKPhase = SPI_PHASE_1EDGE;
	hboard_Spi1.Init.CLKPolarity = SPI_POLARITY_LOW;
	hboard_Spi1.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hboard_Spi1.Init.CRCPolynomial = 7;
	hboard_Spi1.Init.DataSize = SPI_DATASIZE_8BIT;
	hboard_Spi1.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hboard_Spi1.Init.NSS = SPI_NSS_SOFT;
	hboard_Spi1.Init.TIMode = SPI_TIMODE_DISABLE;
	hboard_Spi1.Init.Mode = SPI_MODE_MASTER;

	SPI1_MspInit(&hboard_Spi1);

	return (HAL_SPI_Init(&hboard_Spi1));
}


/**
  * @brief  SPI Write a byte to device
 * @param  WriteValue to be written
 * @retval The value of the received byte.
  */
static uint8_t SPI1_Write(uint8_t WriteValue)
{
  HAL_StatusTypeDef status = HAL_OK;
	uint8_t ReadValue = 0;

	status = HAL_SPI_TransmitReceive(&hboard_Spi1, (uint8_t*) &WriteValue,
			(uint8_t*) &ReadValue, 1, SpixTimeout);

  /* Check the communication status */
  if(status != HAL_OK)
  {
    /* Execute user timeout callback */
		SPI1_Error();
  }

	return ReadValue;
}


/**
 * @brief SPI Read 1 byte from device
 * @retval Read data
 */
static uint8_t SPI1_Read(void)
{
	return (SPI1_Write(FLASH_SPI_DUMMY_BYTE));
}


/**
 * @brief SPI error treatment function
  */
static void SPI1_Error(void)
{
  /* De-initialize the SPI communication BUS */
	HAL_SPI_DeInit(&hboard_Spi1);

	/* Re- Initiaize the SPI communication BUS */
	SPI1_Init();
}
#endif /* HAL_SPI_MODULE_ENABLED */

/**
 * @brief  SPI Write a byte to device
 * @param  DataIn: value to be written
 * @param  DataOut: value to be read
 * @param  DataLength: length of data
 */
static void SPI1_WriteReadData(const uint8_t *DataIn, uint8_t *DataOut,
		uint16_t DataLength) {
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_SPI_TransmitReceive(&hboard_Spi1, (uint8_t*) DataIn, DataOut,
			DataLength, SpixTimeout);

	/* Check the communication status */
	if (status != HAL_OK) {
		/* Execute user timeout callback */
		SPI1_Error();
	}
}

/**
 * @brief  SPI Write Data to device
 * @param  Data: value to be written
 * @param  DataLength: length of data
 */
static void SPI1_WriteData(const uint8_t *Data, uint16_t DataLength) {
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_SPI_Transmit(&hboard_Spi1, (uint8_t*) Data, DataLength,
			SpixTimeout);

	/* Check the communication status */
	if (status != HAL_OK) {
		/* Execute user timeout callback */
		SPI1_Error();
	}
}

/**
 * @brief  SPI Read Data from device
 * @param  Data: value to be read
 * @param  DataLength: length of data
 */
static void SPI1_ReadData(const uint8_t *Data, uint16_t DataLength) {
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_SPI_Receive(&hboard_Spi1, (uint8_t*) Data, DataLength,
			SpixTimeout);

	/* Check the communication status */
	if (status != HAL_OK) {
		/* Execute user timeout callback */
		SPI1_Error();
	}
}

static void SPI2_MspInit(void) {
	GPIO_InitTypeDef gpioinitstruct = { 0 };

	/*** Configure the GPIOs ***/
	/* Enable GPIO clock */
	BOARD_SPI2_SCK_GPIO_CLK_ENABLE()
	;
	BOARD_SPI2_MISO_MOSI_GPIO_CLK_ENABLE()
	;


	/* configure SPI SCK */
	gpioinitstruct.Pin = BOARD_SPI2_SCK_PIN;
	gpioinitstruct.Mode = GPIO_MODE_AF_PP;
	gpioinitstruct.Pull = GPIO_NOPULL;
	gpioinitstruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BOARD_SPI2_SCK_GPIO_PORT, &gpioinitstruct);

	/* configure SPI MISO and MOSI */
	gpioinitstruct.Pin = (BOARD_SPI2_MOSI_PIN);
	gpioinitstruct.Mode = GPIO_MODE_AF_PP;
	gpioinitstruct.Pull = GPIO_NOPULL;
	gpioinitstruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(BOARD_SPI2_MISO_MOSI_GPIO_PORT, &gpioinitstruct);

	/*** Configure the SPI peripheral ***/
	/* Enable SPI clock */
	BOARD_SPI2_CLK_ENABLE()
	;

}

/**
 * @brief  Initializes SPI HAL.
 */
static void SPI2_Init(void) {
	/* DeInitializes the SPI peripheral */
	hboard_Spi2.Instance = BOARD_SPI2;
	HAL_SPI_DeInit(&hboard_Spi2);

	/* SPI Config */
	/* SPI baudrate is set to 9 MHz (PCLK2/SPI_BaudRatePrescaler = 72/8 = 9 MHz) */
	hboard_Spi2.Init.BaudRatePrescaler = SPI_BAUDRATEPRESCALER_8;
	hboard_Spi2.Init.Direction = SPI_DIRECTION_1LINE;
	hboard_Spi2.Init.CLKPhase = SPI_PHASE_1EDGE;
	hboard_Spi2.Init.CLKPolarity = SPI_POLARITY_LOW;
	hboard_Spi2.Init.CRCCalculation = SPI_CRCCALCULATION_DISABLE;
	hboard_Spi2.Init.CRCPolynomial = 7;
	hboard_Spi2.Init.DataSize = SPI_DATASIZE_8BIT;
	hboard_Spi2.Init.FirstBit = SPI_FIRSTBIT_MSB;
	hboard_Spi2.Init.NSS = SPI_NSS_SOFT;
	hboard_Spi2.Init.TIMode = SPI_TIMODE_DISABLE;
	hboard_Spi2.Init.Mode = SPI_MODE_MASTER;

	SPI2_MspInit();
	if (HAL_SPI_Init(&hboard_Spi2) != HAL_OK) {
		/* Should not occur */
		while (1) {
		};
	}
}

/**
 * @brief  SPI Write an amount of data to device
 * @param  Value: value to be written
 * @param  DataLength: number of bytes to write
 */
static void SPI2_WriteData(uint8_t *DataIn, uint16_t DataLength) {
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_SPI_Transmit(&hboard_Spi2, DataIn, DataLength, SpixTimeout);

	/* Check the communication status */
	if (status != HAL_OK) {
		/* Execute user timeout callback */
		SPI2_Error();
	}
}

/**
 * @brief  SPI Write a byte to device
 * @param  Value: value to be written
 */
static void SPI2_Write(uint8_t Value) {
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_SPI_Transmit(&hboard_Spi2, (uint8_t*) &Value, 1,
			SpixTimeout);

	/* Check the communication status */
	if (status != HAL_OK) {
		/* Execute user timeout callback */
		SPI2_Error();
	}
}

/**
 * @brief  SPI Read Data from device
 * @param  Data: value to be read
 * @param  DataLength: length of data
 */
static void SPI2_ReadData(const uint8_t *Data, uint16_t DataLength) {
	HAL_StatusTypeDef status = HAL_OK;

	status = HAL_SPI_Receive(&hboard_Spi2, (uint8_t*) Data, DataLength,
			SpixTimeout);

	/* Check the communication status */
	if (status != HAL_OK) {
		/* Execute user timeout callback */
		SPI1_Error();
	}
}

/**
 * @brief  SPI error treatment function
 * @retval None
 */
static void SPI2_Error(void) {
	/* De-initialize the SPI communication BUS */
	HAL_SPI_DeInit(&hboard_Spi2);

	/* Re-Initiaize the SPI communication BUS */
	SPI2_Init();
}
/**
  * @}
  */

/** @defgroup STM3210C_BOARD_LinkOperations_Functions STM3210C BOARD LinkOperations Functions
  * @{
  */

/*******************************************************************************
                            LINK OPERATIONS
*******************************************************************************/

#ifdef HAL_I2C_MODULE_ENABLED
/***************************** LINK IOE ***************************************/

/**
  * @brief  Initializes IOE low level.
  */
void IOE_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  Configures IOE low level Interrupt.
  */
void IOE_ITConfig(void)
{
  I2Cx_ITConfig();
}

/**
  * @brief  IOE writes single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  Value: Data to be written
  */
void IOE_Write(uint8_t Addr, uint8_t Reg, uint8_t Value)
{
  I2Cx_WriteData(Addr, Reg, Value);
}

/**
  * @brief  IOE reads single data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @retval Read data
  */
uint8_t IOE_Read(uint8_t Addr, uint8_t Reg)
{
  return I2Cx_ReadData(Addr, Reg);
}

/**
  * @brief  IOE reads multiple data.
  * @param  Addr: I2C address
  * @param  Reg: Reg address
  * @param  Buffer: Pointer to data buffer
  * @param  Length: Length of the data
  * @retval Number of read data
  */
uint16_t IOE_ReadMultiple(uint8_t Addr, uint8_t Reg, uint8_t *Buffer, uint16_t Length)
{
 return I2Cx_ReadMultiple(Addr, Reg, I2C_MEMADD_SIZE_8BIT, Buffer, Length);
}

/**
  * @brief  IOE delay.
  * @param  Delay: Delay in ms
  */
void IOE_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

#endif /* HAL_I2C_MODULE_ENABLED */


/********************************* LINK LCD ***********************************/
/**
  * @brief  Initializes the LCD
  * @param  None
  * @retval None
  */
void LCDex_IO_Init(void)
{
	FSMC_BANK1NORSRAM4_Init();
	TIM5_Init();
	/* Start channel 4 */
	if (HAL_TIM_PWM_Start(&htim5, TIM_CHANNEL_2) != HAL_OK) {
		/* PWM generation Error */
		Error_Handler();
	}
}

/**
  * @brief  Writes data on LCD data register.
  * @param  RegValue: Data to be written
  * @retval None
  */
void LCDex_IO_WriteData(uint16_t RegValue)
{
    FSMC_BANK1NORSRAM4_WriteData(RegValue);
}

/**
  * @brief  Writes multiple data on LCD data register.
  * @param  pData: Data to be written
  * @param  Size: number of data to write
  */
void LCDex_IO_WriteMultipleData(uint16_t *pData, uint32_t Size)
{
  while(Size-- > 0)
  {
    /* Write 16-bit Reg */
    FSMC_BANK1NORSRAM4_WriteData(*pData++);
  }
}
/**
  * @brief  Read multiple data from LCD data register.
  * @param  pData: Data to be written
  * @param  Size: number of data to write
  */
void LCDex_IO_ReadMultipleData(uint16_t *pData, uint32_t Size)
{
	  while(Size-- > 0)
	  {
	    /* Write 16-bit Reg */
		*pData++ = FSMC_BANK1NORSRAM4_ReadData();
	  }
}
/**
  * @brief  Writes register on LCD register.
  * @param  Reg: Register to be written
  */
void LCDex_IO_WriteReg(uint8_t Reg)
{
  FSMC_BANK1NORSRAM4_WriteReg(Reg);
}

/**
  * @brief  Reads data from LCD data register.
  * @param  Reg: Register to be read
  * @retval Read data.
  */
uint16_t LCDex_IO_ReadData()
{
  /* Read 16-bit Reg */
  return (FSMC_BANK1NORSRAM4_ReadData());
}

/**
  * @brief  Wait for loop in ms.
  * @param  Delay in ms.
  */
void LCDex_Delay(uint32_t Delay)
{
  HAL_Delay(Delay);
}

/**
 * @brief  Initializes the LCD
 * @param  None
 * @retval None
 */
void LCD_IO_Init(void) {

	GPIO_InitTypeDef gpioinitstruct;

	/* Configure the LCD Control pins ------------------------------------------*/
	LCD_NCS_GPIO_CLK_ENABLE()
	;
	LCD_A0_GPIO_CLK_ENABLE()
	;
	LCD_RES_GPIO_CLK_ENABLE()
	;
	LCD_BL_GPIO_CLK_ENABLE()
	;

	/* Configure NCS in Output Push-Pull mode */
	gpioinitstruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioinitstruct.Pull = GPIO_PULLUP;
	gpioinitstruct.Speed = GPIO_SPEED_FREQ_HIGH;

	gpioinitstruct.Pin = LCD_NCS_PIN;
	HAL_GPIO_Init(LCD_NCS_GPIO_PORT, &gpioinitstruct);

	gpioinitstruct.Pin = LCD_A0_PIN;
	HAL_GPIO_Init(LCD_A0_GPIO_PORT, &gpioinitstruct);

	gpioinitstruct.Pin = LCD_RES_PIN;
	HAL_GPIO_Init(LCD_RES_GPIO_PORT, &gpioinitstruct);

	gpioinitstruct.Pin = LCD_BL_Pin;
	HAL_GPIO_Init(LCD_BL_GPIO_Port, &gpioinitstruct);




	/* Set or Reset the control line */
	LCD_CS_HIGH();
	LCD_RES_HIGH();
	HAL_GPIO_WritePin(LCD_BL_GPIO_Port, LCD_BL_Pin, GPIO_PIN_SET);

	SPI2_Init();

	//TIM1_Init();
	/* Start channel 2 */
	//	if (HAL_TIMEx_PWMN_Start(&htim1, TIM_CHANNEL_2) != HAL_OK) {
	//		/* PWM generation Error */
	//		Error_Handler();
	//	}
}

/**
 * @brief  Writes data on LCD data register.
 * @param  RegValue: Data to be written
 * @retval None
 */
void LCD_IO_WriteData(uint8_t RegValue) {
	/* Reset LCD control line CS */
	LCD_CS_LOW();

	/* Set LCD data/command line DC to High */
	LCD_DC_HIGH();

	SPI2_Write(RegValue);

	/* Deselect : Chip Select high */
	LCD_CS_HIGH();
}

void LCD_IO_ReadReg(uint8_t Reg, uint8_t *Data, uint16_t DataLength) {
	/* Reset LCD control line CS */
	LCD_CS_LOW();

	/* Set LCD data/command line DC to High */
	LCD_DC_HIGH();

	SPI2_Write(Reg);

	LCD_DC_HIGH();
	SPI2_ReadData(Data, DataLength);
	/* Deselect : Chip Select high */
	LCD_CS_HIGH();
}

/**
 * @brief  Writes multiple data on LCD data register.
 * @param  pData: Data to be written
 * @param  Size: number of data to write
 */
void LCD_IO_WriteMultipleData(uint8_t *pData, uint32_t Size) {
	uint32_t counter = 0;
	__IO uint32_t data = 0;

	/* Reset LCD control line CS */
	LCD_CS_LOW();

	/* Set LCD data/command line DC to High */
	LCD_DC_HIGH();

	if (Size == 1) {
		/* Only 1 byte to be sent to LCD - general interface can be used */
		/* Send Data */
		SPI2_Write(*pData);
	} else {
		/* Several data should be sent in a raw */
		/* Direct SPI accesses for optimization */
		for (counter = Size; counter != 0; counter--) {
			while (((hboard_Spi2.Instance->SR) & SPI_FLAG_TXE) != SPI_FLAG_TXE)
				;
			*((__IO uint8_t*) &hboard_Spi2.Instance->DR) = *(pData++);
		}

		/* Wait until the bus is ready before releasing Chip select */
		while (((hboard_Spi2.Instance->SR) & SPI_FLAG_BSY) != RESET) {
		}
	}

	/* Empty the Rx fifo */
//	data = *(&hboard_Spi2.Instance->DR);
//	UNUSED(data); /* Remove GNU warning */

	/* Deselect : Chip Select high */
	LCD_CS_HIGH();
}

/**
 * @brief  Write command to select the LCD register.
 * @param  Reg: Address of the selected register.
 * @retval None
 */
void LCD_IO_WriteReg(uint8_t Reg) {
	/* Reset LCD control line CS */
	LCD_CS_LOW();

	/* Set LCD data/command line DC to Low */
	LCD_DC_LOW();

	/* Send Command */
	SPI2_Write(Reg);

	/* Deselect : Chip Select high */
	LCD_CS_HIGH();
}

/**
 * @brief  Wait for loop in ms.
 * @param  Delay in ms.
 */
void LCD_Delay(uint32_t Delay) {
	HAL_Delay(Delay);
}

/**
 * @brief  Initializes the NRF
 * @param  None
 * @retval None
 */
void NRF_IO_Init(void) {

	GPIO_InitTypeDef gpioinitstruct;

	/* Configure the LCD Control pins ------------------------------------------*/
	NRF_NCS_GPIO_CLK_ENABLE()
	;

	/* Configure NCS in Output Push-Pull mode */
	gpioinitstruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioinitstruct.Pull = GPIO_PULLUP;
	gpioinitstruct.Speed = GPIO_SPEED_FREQ_HIGH;

	gpioinitstruct.Pin = NRF_NCS_PIN;
	HAL_GPIO_Init(NRF_NCS_GPIO_PORT, &gpioinitstruct);

	SPI2_Init();

	/* Set or Reset the control line */
	NRF_NCS_HIGH();
}
#ifdef HAL_SPI_MODULE_ENABLED

/******************************** LINK FLASH SPI ********************************/
/**
 * @brief  Initializes the FLASH SPI and put it into StandBy State (Ready for
 *         data transfer).
 */
HAL_StatusTypeDef FLASH_SPI_IO_Init(void) {
	HAL_StatusTypeDef Status = HAL_OK;

	GPIO_InitTypeDef gpioinitstruct = { 0 };

	/* EEPROM_CS_GPIO Periph clock enable */
	FLASH_SPI_CS_GPIO_CLK_ENABLE();

	/* Configure EEPROM_CS_PIN pin: EEPROM SPI CS pin */
	gpioinitstruct.Pin = FLASH_SPI_CS_PIN;
	gpioinitstruct.Mode = GPIO_MODE_OUTPUT_PP;
	gpioinitstruct.Pull = GPIO_PULLUP;
	gpioinitstruct.Speed = GPIO_SPEED_FREQ_HIGH;
	HAL_GPIO_Init(FLASH_SPI_CS_GPIO_PORT, &gpioinitstruct);

	/* SPI FLASH Config */
	Status = SPI1_Init();

	/* EEPROM chip select high */
	FLASH_SPI_CS_HIGH();

	return Status;
}

/**
 * @brief  Write a byte on the FLASH SPI.
 * @param  Data: byte to send.
 */
uint8_t FLASH_SPI_IO_WriteByte(uint8_t Data) {
	/* Send the byte */
	return (SPI1_Write(Data));
}

/**
 * @brief  Read a byte from the FLASH SPI.
 * @retval uint8_t (The received byte).
 */
uint8_t FLASH_SPI_IO_ReadByte(void) {
	uint8_t data = 0;

	/* Get the received data */
	data = SPI1_Read();

	/* Return the shifted data */
	return data;
}

/**
 * @brief  Read data from FLASH SPI driver
 * @param  MemAddress: Internal memory address
 * @param  pBuffer: Pointer to data buffer
 * @param  BufferSize: Amount of data to be read
 * @retval HAL_StatusTypeDef HAL Status
 */
HAL_StatusTypeDef FLASH_SPI_IO_ReadData(uint32_t MemAddress, uint8_t* pBuffer,
		uint32_t BufferSize) {
	/*!< Select the FLASH: Chip Select low */
	FLASH_SPI_CS_LOW();

	/*!< Send "Read from Memory " instruction */
	SPI1_Write(FLASH_SPI_CMD_READ);

	/*!< Send ReadAddr high nibble address byte to read from */
	SPI1_Write((MemAddress & 0xFF0000) >> 16);
	/*!< Send ReadAddr medium nibble address byte to read from */
	SPI1_Write((MemAddress & 0xFF00) >> 8);
	/*!< Send ReadAddr low nibble address byte to read from */
	SPI1_Write(MemAddress & 0xFF);

	while (BufferSize--) /*!< while there is data to be read */
	{
		/*!< Read a byte from the FLASH */
		*pBuffer = SPI1_Write(FLASH_SPI_DUMMY_BYTE);
		/*!< Point to the next location where the byte read will be saved */
		pBuffer++;
	}

	/*!< Deselect the FLASH: Chip Select high */
	FLASH_SPI_CS_HIGH();

	return HAL_OK;
}

/**
 * @brief  Select the FLASH SPI and send "Write Enable" instruction
 */
void FLASH_SPI_IO_WriteEnable(void) {
	/*!< Select the FLASH: Chip Select low */
	FLASH_SPI_CS_LOW();

	/*!< Send "Write Enable" instruction */
	SPI1_Write(FLASH_SPI_CMD_WREN);

	/*!< Select the FLASH: Chip Select low */
	FLASH_SPI_CS_HIGH();

	/*!< Select the FLASH: Chip Select low */
	FLASH_SPI_CS_LOW();
}

/**
 * @brief  Wait response from the FLASH SPI and Deselect the device
 * @retval HAL_StatusTypeDef HAL Status
 */
HAL_StatusTypeDef FLASH_SPI_IO_WaitForWriteEnd(void) {
	/*!< Select the FLASH: Chip Select low */
	FLASH_SPI_CS_HIGH();

	/*!< Select the FLASH: Chip Select low */
	FLASH_SPI_CS_LOW();

	uint8_t flashstatus = 0;

	/*!< Send "Read Status Register" instruction */
	SPI1_Write(FLASH_SPI_CMD_RDSR);

	/*!< Loop as long as the memory is busy with a write cycle */
	do {
		/*!< Send a dummy byte to generate the clock needed by the FLASH
		 and put the value of the status register in FLASH_Status variable */
		flashstatus = SPI1_Write(FLASH_SPI_DUMMY_BYTE);

	} while ((flashstatus & FLASH_SPI_WIP_FLAG) == SET); /* Write in progress */

	/*!< Deselect the FLASH: Chip Select high */
	FLASH_SPI_CS_HIGH();

	return HAL_OK;
}

/**
 * @brief  Reads FLASH SPI identification.
 * @retval FLASH identification
 */
uint32_t FLASH_SPI_IO_ReadID(void) {
	uint32_t Temp = 0, Temp0 = 0, Temp1 = 0, Temp2 = 0;

	/*!< Select the FLASH: Chip Select low */
	FLASH_SPI_CS_LOW();

	/*!< Send "RDID " instruction */
	SPI1_Write(0x9F);

	/*!< Read a byte from the FLASH */
	Temp0 = SPI1_Write(FLASH_SPI_DUMMY_BYTE);

	/*!< Read a byte from the FLASH */
	Temp1 = SPI1_Write(FLASH_SPI_DUMMY_BYTE);

	/*!< Read a byte from the FLASH */
	Temp2 = SPI1_Write(FLASH_SPI_DUMMY_BYTE);

	/*!< Deselect the FLASH: Chip Select high */
	FLASH_SPI_CS_HIGH();

	Temp = (Temp0 << 16) | (Temp1 << 8) | Temp2;

	return Temp;
}
#endif /* HAL_SPI_MODULE_ENABLED */

#ifdef HAL_I2C_MODULE_ENABLED
/********************************* LINK I2C EEPROM *****************************/
/**
  * @brief  Initializes peripherals used by the I2C EEPROM driver.
  */
void EEPROM_I2C_IO_Init(void)
{
  I2Cx_Init();
}

/**
  * @brief  Write data to I2C EEPROM driver
  * @param  DevAddress: Target device address
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be sent
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_I2C_IO_WriteData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  return (I2Cx_WriteBuffer(DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
}

/**
  * @brief  Read data from I2C EEPROM driver
  * @param  DevAddress: Target device address
  * @param  MemAddress: Internal memory address
  * @param  pBuffer: Pointer to data buffer
  * @param  BufferSize: Amount of data to be read
  * @retval HAL status
  */
HAL_StatusTypeDef EEPROM_I2C_IO_ReadData(uint16_t DevAddress, uint16_t MemAddress, uint8_t* pBuffer, uint32_t BufferSize)
{
  return (I2Cx_ReadBuffer(DevAddress, MemAddress, I2C_MEMADD_SIZE_16BIT, pBuffer, BufferSize));
}

/**
* @brief  Checks if target device is ready for communication.
* @note   This function is used with Memory devices
* @param  DevAddress: Target device address
* @param  Trials: Number of trials
* @retval HAL status
*/
HAL_StatusTypeDef EEPROM_I2C_IO_IsDeviceReady(uint16_t DevAddress, uint32_t Trials)
{
  return (I2Cx_IsDeviceReady(DevAddress, Trials));
}

#endif /* HAL_I2C_MODULE_ENABLED */



/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/**
  * @}
  */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
