/*
 /**
 ******************************************************************************
 * @file    ili9806.h
 * @author  keyhooon
 * @version V1.0.2
 * @date    02-December-2014
 * @brief   This file contains all the functions prototypes for the ili9806.c
 *          driver.
 ******************************************************************************
 * @attention
 *
 * <h2><center>&copy; COPYRIGHT(c) 2017 ICRC</center></h2>
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

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __ILI9806_H
#define __ILI9806_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "../Common/lcd.h"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup Components
 * @{
 */

/** @addtogroup ILI9806
 * @{
 */

/** @defgroup ILI9806_Exported_Types
 * @{
 */
/**
 * @}
 */

/** @defgroup ILI9806_Exported_Constants
 * @{
 */

/**
 * @brief ILI9806 chip IDs
 */
#define ILI9806_ID                  0x9806

/**
 * @brief  ILI9806 Size
 */
#define  ILI9806_LCD_PIXEL_WIDTH    ((uint16_t)480)
#define  ILI9806_LCD_PIXEL_HEIGHT   ((uint16_t)864)

/**
 * @brief  ILI9806 Timing
 */
/* Timing configuration  (Typical configuration from ILI9806 datasheet)
 HSYNC=10 (9+1)
 HBP=20 (29-10+1)
 ActiveW=240 (269-20-10+1)
 HFP=10 (279-240-20-10+1)

 VSYNC=2 (1+1)
 VBP=2 (3-2+1)
 ActiveH=320 (323-2-2+1)
 VFP=4 (327-320-2-2+1)
 */
#define  ILI9806_HSYNC            ((uint32_t)9)   /* Horizontal synchronization */
#define  ILI9806_HBP              ((uint32_t)29)    /* Horizontal back porch      */
#define  ILI9806_HFP              ((uint32_t)2)    /* Horizontal front porch     */
#define  ILI9806_VSYNC            ((uint32_t)1)   /* Vertical synchronization   */
#define  ILI9806_VBP              ((uint32_t)3)    /* Vertical back porch        */
#define  ILI9806_VFP              ((uint32_t)2)    /* Vertical front porch       */

/**
 * @brief  ILI9806 Registers
 */

/* Level 1 Commands */
#define LCD_NOP					0x00
#define LCD_SWRESET             0x01   /* Software Reset */
#define LCD_READ_DISPLAY_ID     0x04   /* Read display identification information */
#define LCD_READ_ERR_NUMBER		0x05   /* Read Number of the Errors on DSI */
#define LCD_RDDST               0x09   /* Read Display Status */
#define LCD_RDDPM               0x0A   /* Read Display Power Mode */
#define LCD_RDDMADCTL           0x0B   /* Read Display MADCTL */
#define LCD_RDDCOLMOD           0x0C   /* Read Display Pixel Format */
#define LCD_RDDIM               0x0D   /* Read Display Image Format */
#define LCD_RDDSM               0x0E   /* Read Display Signal Mode */
#define LCD_RDDSDR              0x0F   /* Read Display Self-Diagnostic Result */
#define LCD_SPLIN               0x10   /* Enter Sleep Mode */
#define LCD_SLEEP_OUT           0x11   /* Sleep out register */
#define LCD_PTLON               0x12   /* Partial Mode ON */
#define LCD_NORMAL_MODE_ON      0x13   /* Normal Display Mode ON */
#define LCD_DINVOFF             0x20   /* Display Inversion OFF */
#define LCD_DINVON              0x21   /* Display Inversion ON */
#define LCD_ALL_PIXLE_OFF		0x22   /* All Pixel Off */
#define LCD_ALL_PIXLE_ON		0x23   /* All Pixel On */
#define LCD_DISPLAY_OFF         0x28   /* Display off register */
#define LCD_DISPLAY_ON          0x29   /* Display on register */
#define LCD_COLUMN_ADDR         0x2A   /* Colomn address register */
#define LCD_PAGE_ADDR           0x2B   /* Page address register */
#define LCD_GRAM                0x2C   /* GRAM register */
#define LCD_RAMRD               0x2E   /* Memory Read */
#define LCD_PLTAR               0x30   /* Partial Area */
#define LCD_VSCRDEF             0x33   /* Vertical Scrolling Definition */
#define LCD_TEOFF               0x34   /* Tearing Effect Line OFF */
#define LCD_TEON                0x35   /* Tearing Effect Line ON */
#define LCD_MAC                 0x36   /* Memory Access Control register*/
#define LCD_VSCRSADD            0x37   /* Vertical Scrolling Start Address */
#define LCD_IDMOFF              0x38   /* Idle Mode OFF */
#define LCD_IDMON               0x39   /* Idle Mode ON */
#define LCD_PIXEL_FORMAT        0x3A   /* Pixel Format register */
#define LCD_WRITE_MEM_CONTINUE  0x3C   /* Write Memory Continue */
#define LCD_READ_MEM_CONTINUE   0x3E   /* Read Memory Continue */
#define LCD_SET_TEAR_SCANLINE   0x44   /* Set Tear Scanline */
#define LCD_GET_SCANLINE        0x45   /* Get Scanline */
#define LCD_WDB                 0x51   /* Write Brightness Display register */
#define LCD_RDDISBV             0x52   /* Read Display Brightness */
#define LCD_WCD                 0x53   /* Write Control Display register*/
#define LCD_RDCTRLD             0x54   /* Read CTRL Display */
#define LCD_WRCABC              0x55   /* Write Content Adaptive Brightness Control */
#define LCD_RDCABC              0x56   /* Read Content Adaptive Brightness Control */
#define LCD_WRITE_CABC          0x5E   /* Write CABC Minimum Brightness */
#define LCD_READ_CABC           0x5F   /* Read CABC Minimum Brightness */
#define LCD_READ_ABCR           0x68   /* Read Automatic Brightness Control Self-diagnostic Result */
#define LCD_READ_ID1            0xDA   /* Read ID1 */
#define LCD_READ_ID2            0xDB   /* Read ID2 */
#define LCD_READ_ID3            0xDC   /* Read ID3 */

/* Level 2 Commands */
#define LCD_MODE_INTERFACE      0xB0   /* Interface Mode Control */
#define LCD_FRMCTR1             0xB1   /* Frame Rate Control (In Normal Mode) */
#define LCD_FRMCTR2             0xB2   /* Frame Rate Control (In Idle Mode) */
#define LCD_FRMCTR3             0xB3   /* Frame Rate Control (In Partial Mode) */
#define LCD_INVTR               0xB4   /* Display Inversion Control */
#define LCD_BPC                 0xB5   /* Blanking Porch Control register */
#define LCD_DFC                 0xB6   /* Display Function Control register */
#define LCD_ETMOD               0xB7   /* Entry Mode Set */
#define LCD_INTERFACE_SETTING   0xB8   /* Interface Setting */
#define LCD_PNLCTRL				0xB9   /* Panel Control */
#define LCD_SPI_SETTING   		0xBA   /* SPI Interface Setting */
#define LCD_POWER1              0xC0   /* Power Control 1 register */
#define LCD_POWER2              0xC1   /* Power Control 2 register */
#define LCD_PFC		            0xC6   /* Pumping Frequency Control */
#define LCD_VCOM1               0xC7   /* VCOM Control 2 register */
#define LCD_BACKLIGHT1          0xC8   /* Backlight Control 1 */
#define LCD_BACKLIGHT2          0xC9   /* Backlight Control 2 */
#define LCD_NVMWR               0xD0   /* NV Memory Write */
#define LCD_NVMPKEY             0xD1   /* NV Memory Protection Key */
#define LCD_RDNVM               0xD2   /* NV Memory Status Read */
#define LCD_READ_DEVICE_CODE    0xD3   /* Read Device Code */
#define LCD_READ_CLAMP_CONTROL  0xD7   /* Clamp Control */
#define LCD_PGAMMA              0xE0   /* Positive Gamma Correction register */
#define LCD_NGAMMA              0xE1   /* Negative Gamma Correction register */
#define LCD_DGAMCTRL1           0xE2   /* Digital Gamma Control 1 */
#define LCD_DGAMCTRL2           0xE3   /* Digital Gamma Control 2 */
#define LCD_DGAMCTRL3           0xE4   /* Digital Gamma Control 3 */
#define LCD_D3GAMENA            0xEA   /* Digital 3 Gamma Enable */
#define LCD_VOLT_MSET           0xED   /* VGMP / VGMN /VGSP / VGSN Voltage Measurement Set */
#define LCD_PNLTCTRL1           0xF1   /* Panel Timing Control 1 */
#define LCD_PNLTCTRL2           0xF2   /* Panel Timing Control 2 */

#define LCD_DVDD_V          	0xF3   /* DVDD Voltage Setting */
#define LCD_POWER5          	0xF5   /* Power Control 5 register*/

#define LCD_RESCTRL           	0xF7   /* Resolution Control */
#define LCD_READ_EXTCOM_SPI    	0xFB   /* Read EXTC Command In SPI Mode */
#define LCD_LVGL_V		    	0xFC   /* LVGL Voltage Setting  */
#define LCD_EXCOM_SET_EN       	0xFF   /* EXTC Command Set enable register */


/* Size of read registers */
#define LCD_READ_ID_SIZE        2      /* Size of Read ID4 */

/**
 * @}
 */

/** @defgroup ILI9806_Exported_Functions
 * @{
 */



void ili9806_WriteReg(uint8_t LCDReg);
void ili9806_WriteData(uint16_t value);
uint16_t ili9806_ReadData(uint8_t LCDReg);

void ili9806_Init(void);
uint16_t ili9806_ReadID(void);
void ili9806_DisplayOn(void);
void ili9806_DisplayOff(void);
uint16_t ili9806_GetLcdPixelWidth(void);
uint16_t ili9806_GetLcdPixelHeight(void);

void ili9806_SetCursor(uint16_t Xpos, uint16_t Ypos);
void ili9806_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode);
void ili9806_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width,
		uint16_t Height);
void ili9806_DrawHLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos,
		uint16_t Length);
void ili9806_DrawVLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos,
		uint16_t Length);
void ili9806_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp);
/* LCD driver structure */
extern LCD_DrvTypeDef ili9806_drv;

/* LCD IO functions */
void LCD_IO_Init(void);
void LCD_IO_WriteData(uint16_t RegValue);
void LCD_IO_WriteReg(uint8_t Reg);
uint16_t LCD_IO_ReadData();
void LCD_IO_ReadMultipleData(uint16_t * pData,int32_t Size);
void LCD_IO_WriteMultipleData(uint16_t *pData, int32_t Size);

void LCD_Delay(uint32_t delay);

#ifdef __cplusplus
}
#endif

#endif /* __ILI9806_H */

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
