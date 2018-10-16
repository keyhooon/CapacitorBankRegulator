/*
 * ArrowRight.c
 *
 *  Created on: Sep 4, 2018
 *      Author: HP
 */

#include "DIALOG.h"

/*********************************************************************
 *
 *       bmArrowRigth_15x24
 */
static GUI_CONST_STORAGE GUI_COLOR _ColorsArrowRigth_15x24[] = { 0xFFFFFF,
		0xccc7c7 };

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalArrowRigth_15x24 = { 2, // Number of entries
		1,  // Has transparency
		&_ColorsArrowRigth_15x24[0] };

static GUI_CONST_STORAGE unsigned char _acArrowRigth_15x24[] = {
___X____, ________,
__XXX___, ________,
_XXXXX__, ________,
XXXXXXX_, ________,
_XXXXXXX, ________,
__XXXXXX, X_______,
___XXXXX, XX______,
____XXXX, XXX_____,
_____XXX, XXXX____,
______XX, XXXXX___,
_______X, XXXXXX__,
________, XXXXXXX_,
________, XXXXXXX_,
_______X, XXXXXX__,
______XX, XXXXX___,
_____XXX, XXXX____,
____XXXX, XXX_____,
___XXXXX, XX______,
__XXXXXX, X_______,
_XXXXXXX, ________,
XXXXXXX_, ________,
_XXXXX__, ________,
__XXX___, ________,
___X____, ________ };

GUI_CONST_STORAGE GUI_BITMAP bmArrowRigth_15x24 = { 15, // xSize
		24, // ySize
		2, // BytesPerLine
		1, // BitsPerPixel
		_acArrowRigth_15x24,  // Pointer to picture data (indices)
		&_PalArrowRigth_15x24   // Pointer to palette
		};
