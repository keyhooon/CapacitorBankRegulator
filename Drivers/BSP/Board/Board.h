/**
  ******************************************************************************
  * @file    stm3210c_eval.h
  * @author  MCD Application Team
  * @version V6.1.0
  * @date    14-April-2017
 * @brief   This file contains definitions for STM3210C_BOARD's LEDs,
  *          push-buttons and COM ports hardware resources.
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

/** @addtogroup BSP
  * @{
  */

/** @addtogroup STM3210C_BOARD
  * @{
  */

/** @addtogroup STM3210C_BOARD_COMMON
  * @{
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __STM3210C_BOARD_H
#define __STM3210C_BOARD_H

#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "stm32f1xx_hal.h"

/** @defgroup STM3210C_BOARD_Exported_Types STM3210C BOARD Exported Types
  * @{
  */

/**
 * @brief LED Types Definition
 */
typedef enum
{
  LED1 = 0,
  LED2 = 1,
  LED3 = 2,
  LED4 = 3,

  LED_GREEN  = LED1,
  LED_ORANGE = LED2,
  LED_RED    = LED3,
  LED_BLUE   = LED4

} Led_TypeDef;

/**
 * @brief BUTTON Types Definition
 */
typedef enum
{
  BUTTON_WAKEUP = 0,
  BUTTON_TAMPER = 1,
  BUTTON_KEY1 = 2, BUTTON_KEY2 = 3,
} Button_TypeDef;

typedef enum
{
  BUTTON_MODE_GPIO = 0,
  BUTTON_MODE_EXTI = 1
} ButtonMode_TypeDef;


/**
  * @}
  */

/** @defgroup STM3210C_BOARD_Exported_Constants STM3210C BOARD Exported Constants
  * @{
  */

/**
 * @brief  Define for STM3210C_BOARD board
  */

/** @addtogroup STM3210C_BOARD_LED STM3210C BOARD LED
  * @{
  */
#define LEDn                             4

#define LED1_PIN                         GPIO_PIN_6             /* PF.6*/
#define LED1_GPIO_PORT                   GPIOF
#define LED1_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()
#define LED1_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOF_CLK_DISABLE()

#define LED2_PIN                         GPIO_PIN_7            /* PF.7*/
#define LED2_GPIO_PORT                   GPIOF
#define LED2_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()
#define LED2_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOF_CLK_DISABLE()


#define LED3_PIN                         GPIO_PIN_8            /* PF.8*/
#define LED3_GPIO_PORT                   GPIOF
#define LED3_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()
#define LED3_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOF_CLK_DISABLE()


#define LED4_PIN                         GPIO_PIN_9            /* PF.09*/
#define LED4_GPIO_PORT                   GPIOF
#define LED4_GPIO_CLK_ENABLE()           __HAL_RCC_GPIOF_CLK_ENABLE()
#define LED4_GPIO_CLK_DISABLE()          __HAL_RCC_GPIOF_CLK_DISABLE()

#define LEDx_GPIO_CLK_ENABLE(__LED__)    do { if ((__LED__) == LED1) LED1_GPIO_CLK_ENABLE(); else \
                                              if ((__LED__) == LED2) LED2_GPIO_CLK_ENABLE(); else \
                                              if ((__LED__) == LED3) LED3_GPIO_CLK_ENABLE(); else \
                                              if ((__LED__) == LED4) LED4_GPIO_CLK_ENABLE();} while(0)

#define LEDx_GPIO_CLK_DISABLE(__LED__)   (((__LED__) == LED1) ? LED1_GPIO_CLK_DISABLE() :\
                                          ((__LED__) == LED2) ? LED2_GPIO_CLK_DISABLE() :\
                                          ((__LED__) == LED3) ? LED3_GPIO_CLK_DISABLE() :\
                                          ((__LED__) == LED4) ? LED4_GPIO_CLK_DISABLE() : 0 )

/**
  * @}
  */

/** @addtogroup STM3210C_BOARD_BUTTON STM3210C BOARD BUTTON
  * @{
  */
#define BUTTONn                          4

/**
 * @brief Tamper push-button
 */
#define TAMPER_BUTTON_PIN                   GPIO_PIN_13             /* PC.13*/
#define TAMPER_BUTTON_GPIO_PORT             GPIOC
#define TAMPER_BUTTON_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOC_CLK_ENABLE()
#define TAMPER_BUTTON_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOC_CLK_DISABLE()
#define TAMPER_BUTTON_EXTI_IRQn             EXTI15_10_IRQn

/**
 * @brief Key push-button
 */
#define KEY1_BUTTON_PIN                      GPIO_PIN_8             /* PA.8*/
#define KEY1_BUTTON_GPIO_PORT                GPIOA
#define KEY1_BUTTON_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOA_CLK_ENABLE()
#define KEY1_BUTTON_GPIO_CLK_DISABLE()       __HAL_RCC_GPIOA_CLK_DISABLE()
#define KEY1_BUTTON_EXTI_IRQn                EXTI9_5_IRQn

#define KEY2_BUTTON_PIN                      GPIO_PIN_3             /* PD.3*/
#define KEY2_BUTTON_GPIO_PORT                GPIOD
#define KEY2_BUTTON_GPIO_CLK_ENABLE()        __HAL_RCC_GPIOD_CLK_ENABLE()
#define KEY2_BUTTON_GPIO_CLK_DISABLE()       __HAL_RCC_GPIOD_CLK_DISABLE()
#define KEY2_BUTTON_EXTI_IRQn                EXTI3_IRQn

/**
 * @brief Wake-up push-button
 */
#define WAKEUP_BUTTON_PIN                   GPIO_PIN_0             /* PA.00*/
#define WAKEUP_BUTTON_GPIO_PORT             GPIOA
#define WAKEUP_BUTTON_GPIO_CLK_ENABLE()     __HAL_RCC_GPIOA_CLK_ENABLE()
#define WAKEUP_BUTTON_GPIO_CLK_DISABLE()    __HAL_RCC_GPIOA_CLK_DISABLE()
#define WAKEUP_BUTTON_EXTI_IRQn             EXTI0_IRQn

#define BUTTONx_GPIO_CLK_ENABLE(__BUTTON__) do { if ((__BUTTON__) == BUTTON_TAMPER) TAMPER_BUTTON_GPIO_CLK_ENABLE()  ; else \
												 if ((__BUTTON__) == BUTTON_KEY1) KEY1_BUTTON_GPIO_CLK_ENABLE()  ; else \
												 if ((__BUTTON__) == BUTTON_KEY2) KEY2_BUTTON_GPIO_CLK_ENABLE()  ; else \
                                                 if ((__BUTTON__) == BUTTON_WAKEUP) WAKEUP_BUTTON_GPIO_CLK_ENABLE();} while(0)

#define BUTTONx_GPIO_CLK_DISABLE(__BUTTON__)    (((__BUTTON__) == BUTTON_TAMPER) TAMPER_BUTTON_GPIO_CLK_DISABLE()  :\
												((__BUTTON__) == BUTTON_KEY1) KEY1_BUTTON_GPIO_CLK_DISABLE()  :\
												((__BUTTON__) == BUTTON_KEY2) KEY2_BUTTON_GPIO_CLK_DISABLE()  :\
                                                 ((__BUTTON__) == BUTTON_WAKEUP) WAKEUP_BUTTON_GPIO_CLK_DISABLE()  : 0 )



/**
  * @brief IO Pins definition
  */

typedef struct {
	uint32_t index;
	uint32_t length;
} COM_DataRecv_TypeDef;

typedef enum {
	COM1 = 0, COM2 = 1, GSM_COM = COM1, GPS_COM = COM2
} COM_TypeDef;

#define DEFAULT_BUFFER_LENGTH		1024
#define DEFAULT_QUEUE_LENGTH		5



typedef void (*COM_DataRecv_Callback_TypeDef)(COM_DataRecv_TypeDef DataRecv);

/**
 * @brief Definition for COM
 */

#define COMn                             ((uint8_t)2)

#define BOARD_COM1                          USART1
#define BOARD_COM1_CLK_ENABLE()             __HAL_RCC_USART1_CLK_ENABLE()
#define BOARD_COM1_CLK_DISABLE()            __HAL_RCC_USART1_CLK_DISABLE()
#define BOARD_COM1_IRQn                     USART1_IRQn
#define BOARD_COM1_IRQHANDLER             	USART1_IRQHandler

#define BOARD_COM1_BAUDRATE					115200

#define BOARD_COM1_GPIO_PORT            	 GPIOA
#define BOARD_COM1_GPIO_CLK_ENABLE()     	__HAL_RCC_GPIOA_CLK_ENABLE()
#define BOARD_COM1_GPIO_CLK_DISABLE()    	__HAL_RCC_GPIOA_CLK_DISABLE()

#define BOARD_COM1_TX_PIN                   GPIO_PIN_9
#define BOARD_COM1_TX_DMA_STREAM			DMA1_Channel4
#define BOARD_COM1_TX_DMA_IRQ  				DMA1_Channel4_IRQn
#define BOARD_COM1_TX_DMA_IRQHandler		DMA1_Channel4_IRQHandler
#define BOARD_COM1_TX_DMA_CLK_ENABLE()		__HAL_RCC_DMA1_CLK_ENABLE()

#define BOARD_COM1_RX_PIN                   GPIO_PIN_10
#define BOARD_COM1_RX_DMA_STREAM			DMA1_Channel5
#define BOARD_COM1_RX_DMA_IRQ  				DMA1_Channel5_IRQn
#define BOARD_COM1_RX_DMA_IRQHandler		DMA1_Channel5_IRQHandler
#define BOARD_COM1_RX_DMA_CLK_ENABLE()		__HAL_RCC_DMA1_CLK_ENABLE()

#define BOARD_COM2                          USART2
#define BOARD_COM2_BAUDRATE					9600
#define BOARD_COM2_CLK_ENABLE()             __HAL_RCC_USART3_CLK_ENABLE()
#define BOARD_COM2_CLK_DISABLE()            __HAL_RCC_USART3_CLK_DISABLE()
#define BOARD_COM2_IRQn                     USART3_IRQn
#define BOARD_COM2_IRQHANDLER             	USART3_IRQHandler

#define BOARD_COM2_GPIO_PORT             	GPIOA
#define BOARD_COM2_GPIO_CLK_ENABLE()     	__HAL_RCC_GPIOB_CLK_ENABLE()
#define BOARD_COM2_GPIO_CLK_DISABLE()    	__HAL_RCC_GPIOB_CLK_DISABLE()

#define BOARD_COM2_TX_PIN                   GPIO_PIN_2
#define BOARD_COM2_TX_DMA_STREAM			DMA1_Channel7
#define BOARD_COM2_TX_DMA_IRQ  				DMA1_Channel7_IRQn
#define BOARD_COM2_TX_DMA_IRQHandler		DMA1_Channel7_IRQHandler
#define BOARD_COM2_TX_DMA_CLK_ENABLE()		__HAL_RCC_DMA1_CLK_ENABLE()

#define BOARD_COM2_RX_PIN                   GPIO_PIN_3
#define BOARD_COM2_RX_DMA_STREAM			DMA1_Channel6
#define BOARD_COM2_RX_DMA_IRQ  				DMA1_Channel6_IRQn
#define BOARD_COM2_RX_DMA_IRQHandler		DMA1_Channel6_IRQHandler
#define BOARD_COM2_RX_DMA_CLK_ENABLE()		__HAL_RCC_DMA1_CLK_ENABLE()

#define BOARD_COMx_CLK_ENABLE(__INDEX__)    	  do { 	if((__INDEX__) == COM1) BOARD_COM1_CLK_ENABLE(); else\
																					BOARD_COM2_CLK_ENABLE(); } while(0)
#define BOARD_COMx_CLK_DISABLE(__INDEX__)    	  do { 	if((__INDEX__) == COM1) BOARD_COM1_CLK_DISABLE(); else\
																					BOARD_COM2_CLK_DISABLE(); } while(0)
#define BOARD_COMx_GPIO_CLK_ENABLE(__INDEX__)  do { 	if((__INDEX__) == COM1) BOARD_COM1_GPIO_CLK_ENABLE(); else\
																					BOARD_COM2_GPIO_CLK_ENABLE();} while(0)
#define BOARD_COMx_GPIO_CLK_DISABLE(__INDEX__) do { 	if((__INDEX__) == COM1) BOARD_COM1_RX_TX_GPIO_CLK_DISABLE(); else\
																					BOARD_COM2_RX_TX_GPIO_CLK_DISABLE(); } while(0)
#define BOARD_COMx_RX_DMA_CLK_ENABLE(__INDEX__)  do { 	if((__INDEX__) == COM1) BOARD_COM1_RX_DMA_CLK_ENABLE(); else\
																					BOARD_COM2_RX_DMA_CLK_ENABLE(); } while(0)


void BSP_UART_IRQHandler(COM_TypeDef COM);
void GSM_IO_Init(void);
void GSM_IO_DeInit(void);
void GSM_IO_Delay(uint32_t Delay);
void GSM_IO_Write(char * buffer, uint32_t length);
void GSM_IO_Read(char * data, uint32_t length);
void GSM_IO_ReadBefore(char * data, uint32_t length);
char * GSM_IO_Read_Char();
int GSM_IO_Check_Chars_Equality(char *data, int length);
BufferStream_TypeDef * GSM_IO_GetBuffer();

void GSM_DataReceivedCallback(uint32_t Length);

/*The Slave ADdress (SAD) associated to the LIS302DL is 001110xb. SDO pad can be used
to modify less significant bit of the device address. If SDO pad is connected to voltage
supply LSb is ‘1’ (address 0011101b) else if SDO pad is connected to ground LSb value is
‘0’ (address 0011100b).*/
#define L1S302DL_I2C_ADDRESS                  0x38


/*##################### ACCELEROMETER ##########################*/
/* Read/Write command */
#define READWRITE_CMD                     ((uint8_t)0x80)
/* Multiple byte read/write command */
#define MULTIPLEBYTE_CMD                  ((uint8_t)0x40)

/*##################### I2Cx ###################################*/
/* User can use this section to tailor I2Cx instance used and associated
   resources */
/* Definition for I2Cx Pins */
#define BOARD_I2Cx_SCL_PIN                       GPIO_PIN_6        /* PB.06*/
#define BOARD_I2Cx_SCL_GPIO_PORT                 GPIOB
#define BOARD_I2Cx_SDA_PIN                       GPIO_PIN_7        /* PB.07*/
#define BOARD_I2Cx_SDA_GPIO_PORT                 GPIOB

/* Definition for I2Cx clock resources */
#define BOARD_I2Cx                               I2C1
#define BOARD_I2Cx_CLK_ENABLE()                  __HAL_RCC_I2C1_CLK_ENABLE()
#define BOARD_I2Cx_SDA_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define BOARD_I2Cx_SCL_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()

#define BOARD_I2Cx_FORCE_RESET()                 __HAL_RCC_I2C1_FORCE_RESET()
#define BOARD_I2Cx_RELEASE_RESET()               __HAL_RCC_I2C1_RELEASE_RESET()

/* Definition for I2Cx's NVIC */
#define BOARD_I2Cx_EV_IRQn                       I2C1_EV_IRQn
#define BOARD_I2Cx_EV_IRQHandler                 I2C1_EV_IRQHandler
#define BOARD_I2Cx_ER_IRQn                       I2C1_ER_IRQn
#define BOARD_I2Cx_ER_IRQHandler                 I2C1_ER_IRQHandler

/* I2C clock speed configuration (in Hz) */
#ifndef BSP_I2C_SPEED
 #define BSP_I2C_SPEED                            400000
#endif /* I2C_SPEED */


/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the I2C communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */
#define BOARD_I2Cx_TIMEOUT_MAX                   3000

/*##################### SPI1 ###################################*/
#define BOARD_SPI1                               SPI1
#define BOARD_SPI1_CLK_ENABLE()                  __HAL_RCC_SPI1_CLK_ENABLE()

#define BOARD_SPI1_SCK_GPIO_PORT                 GPIOA             /* PA.05*/
#define BOARD_SPI1_SCK_PIN                       GPIO_PIN_5
#define BOARD_SPI1_SCK_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOA_CLK_ENABLE()
#define BOARD_SPI1_SCK_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOA_CLK_DISABLE()

#define BOARD_SPI1_MISO_MOSI_GPIO_PORT           GPIOA
#define BOARD_SPI1_MISO_MOSI_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOA_CLK_ENABLE()
#define BOARD_SPI1_MISO_MOSI_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOA_CLK_DISABLE()
#define BOARD_SPI1_MISO_PIN                      GPIO_PIN_6       /* PA.06*/
#define BOARD_SPI1_MOSI_PIN                      GPIO_PIN_7       /* PA.07*/

/*##################### SPI2 ###################################*/
#define BOARD_SPI2                               SPI2
#define BOARD_SPI2_CLK_ENABLE()                  __HAL_RCC_SPI2_CLK_ENABLE()

#define BOARD_SPI2_SCK_GPIO_PORT                 GPIOB             /* Pb.13*/
#define BOARD_SPI2_SCK_PIN                       GPIO_PIN_13
#define BOARD_SPI2_SCK_GPIO_CLK_ENABLE()         __HAL_RCC_GPIOB_CLK_ENABLE()
#define BOARD_SPI2_SCK_GPIO_CLK_DISABLE()        __HAL_RCC_GPIOB_CLK_DISABLE()

#define BOARD_SPI2_MISO_MOSI_GPIO_PORT           GPIOB
#define BOARD_SPI2_MISO_MOSI_GPIO_CLK_ENABLE()   __HAL_RCC_GPIOB_CLK_ENABLE()
#define BOARD_SPI2_MISO_MOSI_GPIO_CLK_DISABLE()  __HAL_RCC_GPIOB_CLK_DISABLE()
#define BOARD_SPI2_MOSI_PIN                      GPIO_PIN_15      /* PB.15*/

/* Maximum Timeout values for flags waiting loops. These timeouts are not based
   on accurate values, they just guarantee that the application will not remain
   stuck if the SPI communication is corrupted.
   You may modify these timeout values depending on CPU frequency and application
   conditions (interrupts routines ...). */
#define BOARD_SPI1_TIMEOUT_MAX                   1000
#define BOARD_SPI2_TIMEOUT_MAX                   1000

/**
  * @}
  */

/** @addtogroup STM3210C_BOARD_COMPONENT STM3210C BOARD COMPONENT
  * @{
  */

/*##################### LCD ###################################*/
/* Chip Select macro definition */
/**
 * @brief  LCD Control Interface pins
 */

#define LCDex_BL_Pin							GPIO_PIN_1
#define LCDex_BL_GPIO_Port 						GPIOA

#define LCDex_BL_GPIO_CLK_ENABLE()              __HAL_RCC_GPIOA_CLK_ENABLE()
#define LCDex_BL_GPIO_CLK_DISABLE()             __HAL_RCC_GPIOA_CLK_DISABLE()

#define LCD_BL_Pin								GPIO_PIN_14
#define LCD_BL_GPIO_Port 						GPIOB

#define LCD_BL_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOB_CLK_ENABLE()
#define LCD_BL_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOB_CLK_DISABLE()


/* Chip Select macro definition */
#define LCD_CS_LOW()       HAL_GPIO_WritePin(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, GPIO_PIN_RESET)
#define LCD_CS_HIGH()      HAL_GPIO_WritePin(LCD_NCS_GPIO_PORT, LCD_NCS_PIN, GPIO_PIN_SET)
#define LCD_DC_LOW()       HAL_GPIO_WritePin(LCD_A0_GPIO_PORT, LCD_A0_PIN, GPIO_PIN_RESET)
#define LCD_DC_HIGH()      HAL_GPIO_WritePin(LCD_A0_GPIO_PORT, LCD_A0_PIN, GPIO_PIN_SET)
#define LCD_RES_LOW()      HAL_GPIO_WritePin(LCD_RES_GPIO_PORT, LCD_RES_PIN, GPIO_PIN_RESET)
#define LCD_RES_HIGH()     HAL_GPIO_WritePin(LCD_RES_GPIO_PORT, LCD_RES_PIN, GPIO_PIN_SET)

/**
 * @brief  LCD Control Interface pins
 */
#define LCD_NCS_PIN                             GPIO_PIN_13        /* PD.13*/
#define LCD_NCS_GPIO_PORT                       GPIOD
#define LCD_NCS_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOD_CLK_ENABLE()
#define LCD_NCS_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOD_CLK_DISABLE()

#define LCD_A0_PIN                             GPIO_PIN_12        /* PB.12*/
#define LCD_A0_GPIO_PORT                       GPIOB
#define LCD_A0_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOB_CLK_ENABLE()
#define LCD_A0_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOB_CLK_DISABLE()

#define LCD_RES_PIN                             GPIO_PIN_8        /* PG.08*/
#define LCD_RES_GPIO_PORT                       GPIOG
#define LCD_RES_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOG_CLK_ENABLE()
#define LCD_RES_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOG_CLK_DISABLE()

/*##################### NRF ###################################*/

/* Chip Select macro definition */
#define NRF_NCS_LOW()       HAL_GPIO_WritePin(NRF_NCS_GPIO_PORT, NRF_NCS_PIN, GPIO_PIN_RESET)
#define NRF_NCS_HIGH()      HAL_GPIO_WritePin(NRF_NCS_GPIO_PORT, NRF_NCS_PIN, GPIO_PIN_SET)
/**
 * @brief NRF Interface pins
 */
#define NRF_NCS_PIN                             GPIO_PIN_5        /* PC.05*/
#define NRF_NCS_GPIO_PORT                       GPIOC
#define NRF_NCS_GPIO_CLK_ENABLE()               __HAL_RCC_GPIOC_CLK_ENABLE()
#define NRF_NCS_GPIO_CLK_DISABLE()              __HAL_RCC_GPIOC_CLK_DISABLE()


/*##################### FLASH SPI ###################################*/
/**
 * @brief  M25P FLASH SPI Chip Select macro definition
 */
#define FLASH_SPI_CS_LOW()       HAL_GPIO_WritePin(FLASH_SPI_CS_GPIO_PORT, FLASH_SPI_CS_PIN, GPIO_PIN_RESET)
#define FLASH_SPI_CS_HIGH()      HAL_GPIO_WritePin(FLASH_SPI_CS_GPIO_PORT, FLASH_SPI_CS_PIN, GPIO_PIN_SET)

/**
 * @brief  M25P FLASH SPI Control Interface pins
 */
#define FLASH_SPI_CS_PIN                           GPIO_PIN_4        /* PC.04*/
#define FLASH_SPI_CS_GPIO_PORT                     GPIOC
#define FLASH_SPI_CS_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOC_CLK_ENABLE()
#define FLASH_SPI_CS_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOC_CLK_DISABLE()

/**
 * @brief  M25P FLASH SPI supported commands
 */
#define FLASH_SPI_CMD_WRITE          0x02  /*!< Write to Memory instruction */
#define FLASH_SPI_CMD_WRSR           0x01  /*!< Write Status Register instruction */
#define FLASH_SPI_CMD_WREN           0x06  /*!< Write enable instruction */
#define FLASH_SPI_CMD_READ           0x03  /*!< Read from Memory instruction */
#define FLASH_SPI_CMD_RDSR           0x05  /*!< Read Status Register instruction  */
#define FLASH_SPI_CMD_RDID           0x9F  /*!< Read identification */
#define FLASH_SPI_CMD_SE             0xD8  /*!< Sector Erase instruction */
#define FLASH_SPI_CMD_BE             0xC7  /*!< Bulk Erase instruction */

#define FLASH_SPI_WIP_FLAG           0x01  /*!< Write In Progress (WIP) flag */

#define FLASH_SPI_DUMMY_BYTE         0xA5
#define FLASH_SPI_PAGESIZE           0x100

#define FLASH_SPI_M25P128_ID         0x202018
#define FLASH_SPI_M25P64_ID          0x202017


/*##################### SD ###################################*/
/* Chip Select macro definition */
#define SD_CS_LOW()       HAL_GPIO_WritePin(SD_CS_GPIO_PORT, SD_CS_PIN, GPIO_PIN_RESET)
#define SD_CS_HIGH()      HAL_GPIO_WritePin(SD_CS_GPIO_PORT, SD_CS_PIN, GPIO_PIN_SET)

/**
  * @brief  SD Control Interface pins
  */
#define SD_CS_PIN                               GPIO_PIN_4        /* PA.04*/
#define SD_CS_GPIO_PORT                         GPIOA
#define SD_CS_GPIO_CLK_ENABLE()                 __HAL_RCC_GPIOA_CLK_ENABLE()
#define SD_CS_GPIO_CLK_DISABLE()                __HAL_RCC_GPIOA_CLK_DISABLE()

/**
  * @brief  SD Detect Interface pins
  */
#define SD_DETECT_PIN                           GPIO_PIN_0
#define SD_DETECT_GPIO_PORT                     GPIOE
#define SD_DETECT_GPIO_CLK_ENABLE()             __HAL_RCC_GPIOE_CLK_ENABLE()
#define SD_DETECT_GPIO_CLK_DISABLE()            __HAL_RCC_GPIOE_CLK_DISABLE()
#define SD_DETECT_EXTI_IRQn                     EXTI0_IRQn

/*##################### AUDIO ##########################*/
/**
  * @brief  AUDIO I2C Interface pins
  */
#define AUDIO_I2C_ADDRESS                     0x94

/**
  * @}
  */

/**
  * @}
  */



/** @addtogroup STM3210C_BOARD_Exported_Functions
  * @{
  */
uint32_t                BSP_GetVersion(void);
void                    BSP_LED_Init(Led_TypeDef Led);
void                    BSP_LED_On(Led_TypeDef Led);
void                    BSP_LED_Off(Led_TypeDef Led);
void                    BSP_LED_Toggle(Led_TypeDef Led);
void                    BSP_PB_Init(Button_TypeDef Button, ButtonMode_TypeDef Button_Mode);
uint32_t                BSP_PB_GetState(Button_TypeDef Button);
void BSP_PB_EXTI_Callback(Button_TypeDef Button, int state);




/**
  * @}
  */


#ifdef __cplusplus
}
#endif

#endif /* __STM3210C_BOARD_H */

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
