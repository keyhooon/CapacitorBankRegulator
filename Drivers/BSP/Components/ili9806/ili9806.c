/**
 ******************************************************************************
 * @file    ili9806.c
 * @author  Keyhooon
 * @version V1.0.2
 * @date    02-December-2014
 * @brief   This file includes the LCD driver for ILI9806 LCD.
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

/* Includes ------------------------------------------------------------------*/
#include "ili9806.h"

/** @addtogroup BSP
 * @{
 */

/** @addtogroup Components
 * @{
 */

/** @addtogroup ILI9806
 * @brief This file provides a set of functions needed to drive the
 *        ILI9806 LCD.
 * @{
 */

/** @defgroup ILI9806_Private_TypesDefinitions
 * @{
 */
/**
 * @}
 */

/** @defgroup ILI9806_Private_Defines
 * @{
 */
/**
 * @}
 */

/** @defgroup ILI9806_Private_Macros
 * @{
 */
/**
 * @}
 */

/** @defgroup ILI9806_Private_Variables
 * @{
 */


LCD_DrvTypeDef ili9806_drv =
		{ ili9806_Init, ili9806_ReadID, ili9806_DisplayOn, ili9806_DisplayOff,
				ili9806_SetCursor, ili9806_WritePixel, 0,
				ili9806_SetDisplayWindow, ili9806_DrawHLine, ili9806_DrawVLine,
				ili9806_GetLcdPixelWidth, ili9806_GetLcdPixelHeight,
				ili9806_DrawBitmap, };
/**
 * @}
 */

/** @defgroup ILI9806_Private_FunctionPrototypes
 * @{
 */

/**
 * @}
 */

/** @defgroup ILI9806_Private_Functions
 * @{
 */

/**
 * @brief  Power on the LCD.
 * @param  None
 * @retval None
 */
void ili9806_Init(void) {
	/* Initialize ILI9806 low level bus layer ----------------------------------*/
	LCDex_IO_Init();

	/* Configure LCD */
	ili9806_WriteReg(LCD_EXCOM_SET_EN); // EXTC Command Set enable register
	ili9806_WriteData(0xFF);
	ili9806_WriteData(0x98);
	ili9806_WriteData(0x06);

	ili9806_WriteReg(0xBA); // SPI Interface Setting
	ili9806_WriteData(0x60);

	/////GIP Timing Setting for //
	ili9806_WriteReg(0xBC); //GPI
	ili9806_WriteData(0x03);
	ili9806_WriteData(0x0D);
	ili9806_WriteData(0x03);
	ili9806_WriteData(0x63);
	ili9806_WriteData(0x01);
	ili9806_WriteData(0x01);
	ili9806_WriteData(0x1B);
	ili9806_WriteData(0x11);
	ili9806_WriteData(0x6E);
	ili9806_WriteData(0x00);
	ili9806_WriteData(0x00);
	ili9806_WriteData(0x00);
	ili9806_WriteData(0x01);
	ili9806_WriteData(0x01);
	ili9806_WriteData(0x16);
	ili9806_WriteData(0x00);
	ili9806_WriteData(0xFF);
	ili9806_WriteData(0xF2);
	ili9806_WriteData(0x01);
	ili9806_WriteData(0x00);
	ili9806_WriteData(0xC0);

	ili9806_WriteReg(0xBD); //GPI
	ili9806_WriteData(0x02);
	ili9806_WriteData(0x13);
	ili9806_WriteData(0x45);
	ili9806_WriteData(0x67);
	ili9806_WriteData(0x45);
	ili9806_WriteData(0x67);
	ili9806_WriteData(0x01);
	ili9806_WriteData(0x23);

	ili9806_WriteReg(0xBE); //GPI
	ili9806_WriteData(0x01);
	ili9806_WriteData(0x22);
	ili9806_WriteData(0x22);
	ili9806_WriteData(0xDC);
	ili9806_WriteData(0xBA);
	ili9806_WriteData(0x67);
	ili9806_WriteData(0x22);
	ili9806_WriteData(0x22);
	ili9806_WriteData(0x22);


	ili9806_WriteReg(LCD_PIXEL_FORMAT);
	ili9806_WriteData(0x55); //55-16BIT,66-18BIT,77-24BIT

	ili9806_WriteReg(LCD_SLEEP_OUT);
	LCDex_Delay(120);
	ili9806_WriteReg(LCD_DISPLAY_ON);
	LCDex_Delay(25);
	ili9806_WriteReg(LCD_GRAM);

}

/**
 * @brief  Disables the Display.
 * @param  None
 * @retval LCD Register Value.
 */
uint16_t ili9806_ReadID(void) {
	LCDex_IO_Init();
	return  ili9806_ReadData(LCD_READ_ID1);
}

/**
 * @brief  Enables the Display.
 * @param  None
 * @retval None
 */
void ili9806_DisplayOn(void) {
	/* Display On */
	ili9806_WriteReg(LCD_DISPLAY_ON);
}

/**
 * @brief  Disables the Display.
 * @param  None
 * @retval None
 */
void ili9806_DisplayOff(void) {
	/* Display Off */
	ili9806_WriteReg(LCD_DISPLAY_OFF);
}

/**
 * @brief  Sets Cursor position.
 * @param  Xpos: specifies the X position.
 * @param  Ypos: specifies the Y position.
 * @retval None
 */
void ili9806_SetCursor(uint16_t Xpos, uint16_t Ypos) {
	ili9806_WriteReg(LCD_COLUMN_ADDR);
	ili9806_WriteData((Xpos) >> 8);
	ili9806_WriteData((Xpos) & 0xFF);
	ili9806_WriteReg(LCD_PAGE_ADDR);
	ili9806_WriteData((Ypos) >> 8);
	ili9806_WriteData((Ypos) & 0xFF);
	ili9806_WriteReg(LCD_GRAM);
}

/**
 * @brief  Writes pixel.
 * @param  Xpos: specifies the X position.
 * @param  Ypos: specifies the Y position.
 * @param  RGBCode: the RGB pixel color
 * @retval None
 */
void ili9806_WritePixel(uint16_t Xpos, uint16_t Ypos, uint16_t RGBCode) {
	uint8_t data = 0;
	if ((Xpos >= ILI9806_LCD_PIXEL_WIDTH)
			|| (Ypos >= ILI9806_LCD_PIXEL_HEIGHT)) {
		return;
	}

	/* Set Cursor */
	ili9806_SetCursor(Xpos, Ypos);

	ili9806_WriteData(RGBCode);
}

/**
 * @brief  Sets a display window
 * @param  Xpos:   specifies the X bottom left position.
 * @param  Ypos:   specifies the Y bottom left position.
 * @param  Height: display window height.
 * @param  Width:  display window width.
 * @retval None
 */
void ili9806_SetDisplayWindow(uint16_t Xpos, uint16_t Ypos, uint16_t Width,
		uint16_t Height) {
	/* Column addr set, 4 args, no delay: XSTART = Xpos, XEND = (Xpos + Width - 1) */
	ili9806_WriteReg(LCD_COLUMN_ADDR);
	ili9806_WriteData((Xpos) >> 8);
	ili9806_WriteData((Xpos) & 0xFF);
	ili9806_WriteData((Xpos + Width - 1) >> 8);
	ili9806_WriteData((Xpos + Width - 1) & 0xFF);
	/* Row addr set, 4 args, no delay: YSTART = Ypos, YEND = (Ypos + Height - 1) */
	ili9806_WriteReg(LCD_PAGE_ADDR);
	ili9806_WriteData((Ypos) >> 8);
	ili9806_WriteData((Ypos) & 0xFF);
	ili9806_WriteData((Ypos + Height - 1) >> 8);
	ili9806_WriteData((Ypos + Height - 1) & 0xFF);
}

/**
 * @brief  Draws horizontal line.
 * @param  RGBCode: Specifies the RGB color
 * @param  Xpos: specifies the X position.
 * @param  Ypos: specifies the Y position.
 * @param  Length: specifies the line length.
 * @retval None
 */
void ili9806_DrawHLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos,
		uint16_t Length) {
	uint16_t counter = 0;

	if (Xpos + Length > ILI9806_LCD_PIXEL_WIDTH)
		return;

	/* Set Cursor */
	ili9806_SetCursor(Xpos, Ypos);

	for (counter = 0; counter < Length; counter++) {
		ili9806_WriteData(RGBCode);
	}
}

/**
 * @brief  Draws vertical line.
 * @param  RGBCode: Specifies the RGB color
 * @param  Xpos: specifies the X position.
 * @param  Ypos: specifies the Y position.
 * @param  Length: specifies the line length.
 * @retval None
 */
void ili9806_DrawVLine(uint16_t RGBCode, uint16_t Xpos, uint16_t Ypos,
		uint16_t Length) {
	uint16_t counter = 0;

	if (Ypos + Length > ILI9806_LCD_PIXEL_HEIGHT)
		return;
	for (counter = 0; counter < Length; counter++) {
		ili9806_WritePixel(Xpos, Ypos + counter, RGBCode);
	}
}

/**
 * @brief  Displays a bitmap picture loaded in the internal Flash.
 * @param  BmpAddress: Bmp picture address in the internal Flash.
 * @retval None
 */
void ili9806_DrawBitmap(uint16_t Xpos, uint16_t Ypos, uint8_t *pbmp) {
	uint32_t index = 0, size = 0;

	/* Read bitmap size */
	size = *(volatile uint16_t *) (pbmp + 2);
	size |= (*(volatile uint16_t *) (pbmp + 4)) << 16;
	/* Get bitmap data address offset */
	index = *(volatile uint16_t *) (pbmp + 10);
	index |= (*(volatile uint16_t *) (pbmp + 12)) << 16;
	size = (size - index) / 2;
	pbmp += index;

	/* Set GRAM write direction and BGR = 0 */
	/* Memory access control: MY = 0, MX = 1, MV = 0, ML = 0 */
	ili9806_WriteReg(LCD_MAC);
	ili9806_WriteData(0x40);

	/* Set Cursor */
	ili9806_SetCursor(Xpos, Ypos);
	for (int i = 0; i < size ; i++)
	{	ili9806_WriteData(*((uint16_t *)pbmp));
	pbmp+=2;
	}
	/* Set GRAM write direction and BGR = 0 */
	/* Memory access control: MY = 1, MX = 1, MV = 0, ML = 0 */
	ili9806_WriteReg(LCD_MAC);
	ili9806_WriteData(0xC0);
}

/**
 * @brief  Writes  to the selected LCD register.
 * @param  LCD_Reg: address of the selected register.
 * @retval None
 */
inline void ili9806_WriteReg(uint8_t Reg) {
	LCDex_IO_WriteReg(Reg);
}

/**
 * @brief  Writes data to the selected LCD register.
 * @param  LCD_Reg: address of the selected register.
 * @retval None
 */
inline void ili9806_WriteData(uint16_t Value) {
	LCDex_IO_WriteData(Value);
}

/**
 * @brief  Reads the selected LCD Register.
 * @param  RegValue: Address of the register to read
 * @param  ReadSize: Number of bytes to read
 * @retval LCD Register Value.
 */
inline uint16_t ili9806_ReadData(uint8_t Reg) {
	LCDex_IO_WriteReg(Reg);
	return (LCDex_IO_ReadData());
}

/**
 * @brief  Get LCD PIXEL WIDTH.
 * @param  None
 * @retval LCD PIXEL WIDTH.
 */
uint16_t ili9806_GetLcdPixelWidth(void) {
	/* Return LCD PIXEL WIDTH */
	return ILI9806_LCD_PIXEL_WIDTH;
}

/**
 * @brief  Get LCD PIXEL HEIGHT.
 * @param  None
 * @retval LCD PIXEL HEIGHT.
 */
uint16_t ili9806_GetLcdPixelHeight(void) {
	/* Return LCD PIXEL HEIGHT */
	return ILI9806_LCD_PIXEL_HEIGHT;
}

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
