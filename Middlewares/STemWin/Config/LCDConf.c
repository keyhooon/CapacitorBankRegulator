/*********************************************************************
*          Portions COPYRIGHT 2016 STMicroelectronics                *
*          Portions SEGGER Microcontroller GmbH & Co. KG             *
*        Solutions for real time microcontroller applications        *
**********************************************************************
*                                                                    *
*        (c) 1996 - 2015  SEGGER Microcontroller GmbH & Co. KG       *
*                                                                    *
*        Internet: www.segger.com    Support:  support@segger.com    *
*                                                                    *
**********************************************************************

** emWin V5.32 - Graphical user interface for embedded applications **
All  Intellectual Property rights  in the Software belongs to  SEGGER.
emWin is protected by  international copyright laws.  Knowledge of the
source code may not be used to write a similar product.  This file may
only be used in accordance with the following terms:

The  software has  been licensed  to STMicroelectronics International
N.V. a Dutch company with a Swiss branch and its headquarters in Plan-
les-Ouates, Geneva, 39 Chemin du Champ des Filles, Switzerland for the
purposes of creating libraries for ARM Cortex-M-based 32-bit microcon_
troller products commercialized by Licensee only, sublicensed and dis_
tributed under the terms and conditions of the End User License Agree_
ment supplied by STMicroelectronics International N.V.
Full source code is available at: www.segger.com

We appreciate your understanding and fairness.
----------------------------------------------------------------------
File        : LCDConf_FlexColor_Template.c
Purpose     : Display controller configuration (single layer)
---------------------------END-OF-HEADER------------------------------
*/

/**
  ******************************************************************************
  * @attention
  *
  * Licensed under MCD-ST Liberty SW License Agreement V2, (the "License");
  * You may not use this file except in compliance with the License.
  * You may obtain a copy of the License at:
  *
  *        http://www.st.com/software_license_agreement_liberty_v2
  *
  * Unless required by applicable law or agreed to in writing, software
  * distributed under the License is distributed on an "AS IS" BASIS,
  * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
  * See the License for the specific language governing permissions and
  * limitations under the License.
  *
  ******************************************************************************
  */

#include "GUI.h"
#include "GUIDRV_FlexColor.h"
#include "Common/lcd.h"
#include "Board.h"

typedef struct {
	__IO uint16_t REG; /* Read Register */
	__IO uint16_t RAM; /* Read RAM */
} TFT_LCD_TypeDef;

extern LCD_DrvTypeDef st7735_drv;
extern LCD_DrvTypeDef ili9806_drv;
LCD_DrvTypeDef * lcd_drv[2] = { &ili9806_drv, &st7735_drv };
#define TFT_LCD_BASE           FSMC_BANK1_4
#define TFT_LCD                ((TFT_LCD_TypeDef *) TFT_LCD_BASE)

/*********************************************************************
*
*       Layer configuration (to be modified)
*
**********************************************************************
*/

//
// Physical display size
//
#define XSIZE_PHYS  481 // To be adapted to x-screen size
#define YSIZE_PHYS  851 // To be adapted to y-screen size

#define XSIZE_PHYS2  128 // To be adapted to x-screen size
#define YSIZE_PHYS2  161 // To be adapted to y-screen size


/*********************************************************************
*
*       Configuration checking
*
**********************************************************************
*/
#ifndef   VXSIZE_PHYS
  #define VXSIZE_PHYS XSIZE_PHYS
#endif
#ifndef   VYSIZE_PHYS
  #define VYSIZE_PHYS YSIZE_PHYS
#endif
#ifndef   VXSIZE_PHYS2
#define VXSIZE_PHYS2 XSIZE_PHYS2
#endif
#ifndef   VYSIZE_PHYS2
#define VYSIZE_PHYS2 YSIZE_PHYS2
#endif
#ifndef   XSIZE_PHYS
  #error Physical X size of display is not defined!
#endif
#ifndef   YSIZE_PHYS
  #error Physical Y size of display is not defined!
#endif
#ifndef   GUICC_565
  #error Color conversion not defined!
#endif
#ifndef   GUIDRV_FLEXCOLOR
  #error No display driver defined!
#endif

/*********************************************************************
*
*       Local functions
*
**********************************************************************
*/
/********************************************************************
*
*       LcdWriteReg
*
* Function description:
*   Sets display register
*/
static void LcdexWriteReg(U16 Data)
{
	TFT_LCD->REG = Data;
}

/********************************************************************
*
*       LcdReadData
*
* Function description:
*   Writes a value to a display register
*/
static U16 LcdexReadData() {
	return TFT_LCD->RAM;
}


/********************************************************************
*
*       LcdWriteData
*
* Function description:
*   Writes a value to a display register
*/
static void LcdexWriteData(U16 Data) {
	TFT_LCD->RAM = Data;
}

/********************************************************************
*
*       LcdWriteDataMultiple
*
* Function description:
*   Writes multiple values to a display register.
*/
static void LcdexWriteDataMultiple(U16 * pData, int NumItems) {
	while (NumItems-- > 0) {
		/* Write 16-bit Reg */
		TFT_LCD->RAM = *pData++;
	}
}

/********************************************************************
*
*       LcdReadDataMultiple
*
* Function description:
*   Reads multiple values from a display register.
*/
static void LcdexReadDataMultiple(U16 * pData, int NumItems) {
	while (NumItems-- > 0) {
		/* Write 16-bit Reg */
		*pData++ = TFT_LCD->RAM;
	}
}

/********************************************************************
 *
 *       LcdWriteReg
 *
 * Function description:
 *   Sets display register
 */
static void LcdWriteReg(U8 Data) {
	LCD_IO_WriteReg(Data);
}


/********************************************************************
 *
 *       LcdWriteData
 *
 * Function description:
 *   Writes a value to a display register
 */
static void LcdWriteData(U8 Data) {
	LCD_IO_WriteData(Data);
}

/********************************************************************
 *
 *       LcdWriteDataMultiple
 *
 * Function description:
 *   Writes multiple values to a display register.
 */
static void LcdWriteDataMultiple(U8 * pData, int NumItems) {
	LCD_IO_WriteMultipleData(pData, NumItems);
}
/*********************************************************************
*
*       Public functions
*
**********************************************************************
*/
/*********************************************************************
*
*       LCD_X_Config
*
* Function description:
*   Called during the initialization process in order to set up the
*   display driver configuration.
*
*/
void LCD_X_Config(void) {
	GUI_DEVICE * pDevice1;
	CONFIG_FLEXCOLOR Config1 = { 0 };
	GUI_PORT_API PortAPI1 = { 0 };
	GUI_DEVICE * pDevice2;
	CONFIG_FLEXCOLOR Config2 = { 0 };
	GUI_PORT_API PortAPI2 = { 0 };
  //
  // Set display driver and color conversion
  //
	pDevice1 = GUI_DEVICE_CreateAndLink(GUIDRV_FLEXCOLOR, GUICC_565, 0, 0);
  //
  // Display driver configuration, required for Lin-driver
  //
  LCD_SetSizeEx (0, XSIZE_PHYS , YSIZE_PHYS);
  LCD_SetVSizeEx(0, VXSIZE_PHYS, VYSIZE_PHYS);
  //
  // Orientation
  //
	Config1.Orientation = GUI_SWAP_XY | GUI_MIRROR_X;
	GUIDRV_FlexColor_Config(pDevice1, &Config1);
	//
	// Set controller and operation mode
	//
	PortAPI1.pfWrite16_A0 = LcdexWriteReg;
	PortAPI1.pfWrite16_A1 = LcdexWriteData;
	PortAPI1.pfRead16_A1 = LcdexReadData;
	PortAPI1.pfWriteM16_A1 = LcdexWriteDataMultiple;
	PortAPI1.pfReadM16_A1 = LcdexReadDataMultiple;
	GUIDRV_FlexColor_SetFunc(pDevice1, &PortAPI1, GUIDRV_FLEXCOLOR_F66709,
	GUIDRV_FLEXCOLOR_M16C0B16);

	//
	// Set display driver and color conversion
	//
	pDevice2 = GUI_DEVICE_CreateAndLink(GUIDRV_FLEXCOLOR, GUICC_565, 0, 1);
	//
	// Display driver configuration, required for Lin-driver
	//
	LCD_SetSizeEx(1, XSIZE_PHYS2, YSIZE_PHYS2);
	LCD_SetVSizeEx(1, VXSIZE_PHYS2, VYSIZE_PHYS2);
	//
	// Orientation
	//
	Config2.Orientation = GUI_MIRROR_Y | GUI_MIRROR_X;
	GUIDRV_FlexColor_Config(pDevice2, &Config2);
	//
	// Set controller and operation mode
	//
	PortAPI2.pfWrite8_A0 = LcdWriteReg;
	PortAPI2.pfWrite8_A1 = LcdWriteData;
	PortAPI2.pfWriteM8_A1 = LcdWriteDataMultiple;
	GUIDRV_FlexColor_SetFunc(pDevice2, &PortAPI2, GUIDRV_FLEXCOLOR_F66709,
	GUIDRV_FLEXCOLOR_M16C0B8);
}

/*********************************************************************
*
*       LCD_X_DisplayDriver
*
* Function description:
*   This function is called by the display driver for several purposes.
*   To support the according task the routine needs to be adapted to
*   the display controller. Please note that the commands marked with
*   'optional' are not cogently required and should only be adapted if
*   the display controller supports these features.
*
* Parameter:
*   LayerIndex - Index of layer to be configured
*   Cmd        - Please refer to the details in the switch statement below
*   pData      - Pointer to a LCD_X_DATA structure
*
* Return Value:
*   < -1 - Error
*     -1 - Command not handled
*      0 - Ok
*/
int LCD_X_DisplayDriver(unsigned LayerIndex, unsigned Cmd, void * pData) {
	int r;
	(void) LayerIndex;
	(void) pData;
	switch (Cmd) {
	case LCD_X_INITCONTROLLER: {
		/**
		 * @brief  Initializes the LCD.
		 * @param  None
		 * @retval LCD state
		 */
		lcd_drv[LayerIndex]->Init();
		return 0;
	}
	case LCD_X_ON: {
		lcd_drv[LayerIndex]->DisplayOn();
		return 0;
	}
	case LCD_X_OFF: {
		lcd_drv[LayerIndex]->DisplayOff();
		return 0;
	}

	default:
		r = -1;
	}

  return r;
}

/*************************** End of file ****************************/

