/*********************************************************************
*                SEGGER Microcontroller GmbH & Co. KG                *
*        Solutions for real time microcontroller applications        *
*                           www.segger.com                           *
**********************************************************************
*                                                                    *
* C-file generated by                                                *
*                                                                    *
*        Bitmap Converter (ST) for emWin V5.32.                      *
*        Compiled Oct  8 2015, 11:58:22                              *
*                                                                    *
*        (c) 1998 - 2015 Segger Microcontroller GmbH & Co. KG        *
*                                                                    *
**********************************************************************
*                                                                    *
* Source file: calling1                                              *
* Dimensions:  64 * 64                                               *
* NumColors:   4                                                     *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif



/*********************************************************************
*
*       Palette
*
*  Description
*    The following are the entries of the palette table.
*    The entries are stored as a 32-bit values of which 24 bits are
*    actually used according to the following bit mask: 0xBBGGRR
*
*    The lower   8 bits represent the Red   component.
*    The middle  8 bits represent the Green component.
*    The highest 8 bits represent the Blue  component.
*/
static GUI_CONST_STORAGE GUI_COLOR _Colorscalling[] = {
  0xFEFEFE, 0xA2E6F6, 0xCFF2FA, 0x55D1F0
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _Palcalling = {
  4,  // Number of entries
  1,  // Has transparency
		&_Colorscalling[0]
};

static GUI_CONST_STORAGE unsigned char _accalling1[] = {
  /* RLE: 988 Pixels @ 000,000 */ 254, 0x00, 254, 0x00, 254, 0x00, 226, 0x00,
  /* ABS: 005 Pixels @ 028,015 */ 0, 5, 0x21, 0x12, 0x20,
  /* RLE: 059 Pixels @ 033,015 */ 59, 0x00,
  /* RLE: 007 Pixels @ 028,016 */ 7, 0x03,
  /* RLE: 001 Pixels @ 035,016 */ 1, 0x01,
  /* RLE: 056 Pixels @ 036,016 */ 56, 0x00,
  /* ABS: 003 Pixels @ 028,017 */ 0, 3, 0x21, 0x10,
  /* RLE: 006 Pixels @ 031,017 */ 6, 0x03,
  /* ABS: 002 Pixels @ 037,017 */ 0, 2, 0x12,
  /* RLE: 058 Pixels @ 039,017 */ 58, 0x00,
  /* ABS: 002 Pixels @ 033,018 */ 0, 2, 0x21,
  /* RLE: 004 Pixels @ 035,018 */ 4, 0x03,
  /* RLE: 001 Pixels @ 039,018 */ 1, 0x01,
  /* RLE: 060 Pixels @ 040,018 */ 60, 0x00,
  /* RLE: 001 Pixels @ 036,019 */ 1, 0x02,
  /* RLE: 004 Pixels @ 037,019 */ 4, 0x03,
  /* RLE: 001 Pixels @ 041,019 */ 1, 0x02,
  /* RLE: 060 Pixels @ 042,019 */ 60, 0x00,
  /* ABS: 005 Pixels @ 038,020 */ 0, 5, 0x23, 0x33, 0x20,
  /* RLE: 061 Pixels @ 043,020 */ 61, 0x00,
  /* RLE: 003 Pixels @ 040,021 */ 3, 0x03,
  /* RLE: 001 Pixels @ 043,021 */ 1, 0x02,
  /* RLE: 061 Pixels @ 044,021 */ 61, 0x00,
  /* ABS: 004 Pixels @ 041,022 */ 0, 4, 0x13, 0x32,
  /* RLE: 061 Pixels @ 045,022 */ 61, 0x00,
  /* ABS: 003 Pixels @ 042,023 */ 0, 3, 0x13, 0x30,
  /* RLE: 062 Pixels @ 045,023 */ 62, 0x00,
  /* RLE: 003 Pixels @ 043,024 */ 3, 0x03,
  /* RLE: 061 Pixels @ 046,024 */ 61, 0x00,
  /* ABS: 004 Pixels @ 043,025 */ 0, 4, 0x23, 0x32,
  /* RLE: 061 Pixels @ 047,025 */ 61, 0x00,
  /* ABS: 003 Pixels @ 044,026 */ 0, 3, 0x13, 0x30,
  /* RLE: 062 Pixels @ 047,026 */ 62, 0x00,
  /* ABS: 003 Pixels @ 045,027 */ 0, 3, 0x33, 0x20,
  /* RLE: 061 Pixels @ 048,027 */ 61, 0x00,
  /* ABS: 003 Pixels @ 045,028 */ 0, 3, 0x13, 0x30,
  /* RLE: 061 Pixels @ 048,028 */ 61, 0x00,
  /* ABS: 003 Pixels @ 045,029 */ 0, 3, 0x23, 0x30,
  /* RLE: 062 Pixels @ 048,029 */ 62, 0x00,
  /* ABS: 003 Pixels @ 046,030 */ 0, 3, 0x33, 0x20,
  /* RLE: 061 Pixels @ 049,030 */ 61, 0x00,
  /* ABS: 003 Pixels @ 046,031 */ 0, 3, 0x13, 0x10,
  /* RLE: 061 Pixels @ 049,031 */ 61, 0x00,
  /* ABS: 003 Pixels @ 046,032 */ 0, 3, 0x23, 0x30,
  /* RLE: 061 Pixels @ 049,032 */ 61, 0x00,
  /* ABS: 003 Pixels @ 046,033 */ 0, 3, 0x23, 0x30,
  /* RLE: 061 Pixels @ 049,033 */ 61, 0x00,
  /* ABS: 003 Pixels @ 046,034 */ 0, 3, 0x23, 0x30,
  /* RLE: 062 Pixels @ 049,034 */ 62, 0x00,
  /* ABS: 002 Pixels @ 047,035 */ 0, 2, 0x33,
  /* RLE: 062 Pixels @ 049,035 */ 62, 0x00,
  /* ABS: 002 Pixels @ 047,036 */ 0, 2, 0x22,
  /* RLE: 1743 Pixels @ 049,036 */ 254, 0x00, 254, 0x00, 254, 0x00, 254, 0x00, 254, 0x00, 254, 0x00, 219, 0x00,
  0
};  // 160 bytes for 4096 pixels

GUI_CONST_STORAGE GUI_BITMAP bmcalling1 = {
  64, // xSize
  64, // ySize
  32, // BytesPerLine
  GUI_COMPRESS_RLE4, // BitsPerPixel
  _accalling1,  // Pointer to picture data (indices)
		&_Palcalling,  // Pointer to palette
		GUI_DRAW_RLE4 };

static GUI_CONST_STORAGE unsigned char _accalling3[] = {
/* RLE: 028 Pixels @ 000,000 */28, 0x00,
/* ABS: 006 Pixels @ 028,000 */0, 6, 0x21, 0x11, 0x22,
/* RLE: 058 Pixels @ 034,000 */58, 0x00,
/* RLE: 008 Pixels @ 028,001 */8, 0x03,
/* ABS: 003 Pixels @ 036,001 */0, 3, 0x11, 0x20,
/* RLE: 053 Pixels @ 039,001 */53, 0x00,
/* ABS: 004 Pixels @ 028,002 */0, 4, 0x21, 0x11,
/* RLE: 008 Pixels @ 032,002 */8, 0x03,
/* ABS: 002 Pixels @ 040,002 */0, 2, 0x12,
/* RLE: 057 Pixels @ 042,002 */57, 0x00,
/* ABS: 003 Pixels @ 035,003 */0, 3, 0x21, 0x10,
/* RLE: 005 Pixels @ 038,003 */5, 0x03,
/* RLE: 001 Pixels @ 043,003 */1, 0x01,
/* RLE: 059 Pixels @ 044,003 */59, 0x00,
/* ABS: 002 Pixels @ 039,004 */0, 2, 0x21,
/* RLE: 004 Pixels @ 041,004 */4, 0x03,
/* RLE: 001 Pixels @ 045,004 */1, 0x01,
/* RLE: 060 Pixels @ 046,004 */60, 0x00,
/* RLE: 001 Pixels @ 042,005 */1, 0x01,
/* RLE: 004 Pixels @ 043,005 */4, 0x03,
/* RLE: 001 Pixels @ 047,005 */1, 0x02,
/* RLE: 060 Pixels @ 048,005 */60, 0x00,
/* ABS: 005 Pixels @ 044,006 */0, 5, 0x13, 0x33, 0x10,
/* RLE: 061 Pixels @ 049,006 */61, 0x00,
/* ABS: 005 Pixels @ 046,007 */0, 5, 0x13, 0x33, 0x20,
/* RLE: 060 Pixels @ 051,007 */60, 0x00,
/* ABS: 005 Pixels @ 047,008 */0, 5, 0x23, 0x33, 0x20,
/* RLE: 061 Pixels @ 052,008 */61, 0x00,
/* RLE: 003 Pixels @ 049,009 */3, 0x03,
/* RLE: 001 Pixels @ 052,009 */1, 0x01,
/* RLE: 061 Pixels @ 053,009 */61, 0x00,
/* ABS: 004 Pixels @ 050,010 */0, 4, 0x13, 0x31,
/* RLE: 061 Pixels @ 054,010 */61, 0x00,
/* ABS: 004 Pixels @ 051,011 */0, 4, 0x13, 0x31,
/* RLE: 061 Pixels @ 055,011 */61, 0x00,
/* ABS: 004 Pixels @ 052,012 */0, 4, 0x13, 0x31,
/* RLE: 061 Pixels @ 056,012 */61, 0x00,
/* ABS: 004 Pixels @ 053,013 */0, 4, 0x13, 0x32,
/* RLE: 061 Pixels @ 057,013 */61, 0x00,
/* ABS: 003 Pixels @ 054,014 */0, 3, 0x13, 0x30,
/* RLE: 062 Pixels @ 057,014 */62, 0x00,
/* RLE: 003 Pixels @ 055,015 */3, 0x03,
/* RLE: 061 Pixels @ 058,015 */61, 0x00,
/* ABS: 004 Pixels @ 055,016 */0, 4, 0x23, 0x31,
/* RLE: 061 Pixels @ 059,016 */61, 0x00,
/* ABS: 003 Pixels @ 056,017 */0, 3, 0x13, 0x30,
/* RLE: 062 Pixels @ 059,017 */62, 0x00,
/* ABS: 003 Pixels @ 057,018 */0, 3, 0x33, 0x10,
/* RLE: 061 Pixels @ 060,018 */61, 0x00,
/* ABS: 004 Pixels @ 057,019 */0, 4, 0x23, 0x32,
/* RLE: 061 Pixels @ 061,019 */61, 0x00,
/* ABS: 003 Pixels @ 058,020 */0, 3, 0x13, 0x10,
/* RLE: 061 Pixels @ 061,020 */61, 0x00,
/* ABS: 004 Pixels @ 058,021 */0, 4, 0x23, 0x32,
/* RLE: 061 Pixels @ 062,021 */61, 0x00,
/* ABS: 003 Pixels @ 059,022 */0, 3, 0x33, 0x10,
/* RLE: 061 Pixels @ 062,022 */61, 0x00,
/* ABS: 003 Pixels @ 059,023 */0, 3, 0x23, 0x30,
/* RLE: 062 Pixels @ 062,023 */62, 0x00,
/* ABS: 003 Pixels @ 060,024 */0, 3, 0x33, 0x20,
/* RLE: 061 Pixels @ 063,024 */61, 0x00,
/* ABS: 003 Pixels @ 060,025 */0, 3, 0x13, 0x10,
/* RLE: 061 Pixels @ 063,025 */61, 0x00,
/* ABS: 003 Pixels @ 060,026 */0, 3, 0x23, 0x30,
/* RLE: 062 Pixels @ 063,026 */62, 0x00,
/* ABS: 002 Pixels @ 061,027 */0, 2, 0x33,
/* RLE: 062 Pixels @ 063,027 */62, 0x00,
/* ABS: 003 Pixels @ 061,028 */0, 3, 0x33, 0x20,
/* RLE: 061 Pixels @ 000,029 */61, 0x00,
/* ABS: 003 Pixels @ 061,029 */0, 3, 0x13, 0x10,
/* RLE: 061 Pixels @ 000,030 */61, 0x00,
/* ABS: 003 Pixels @ 061,030 */0, 3, 0x13, 0x10,
/* RLE: 061 Pixels @ 000,031 */61, 0x00,
/* ABS: 003 Pixels @ 061,031 */0, 3, 0x23, 0x30,
/* RLE: 061 Pixels @ 000,032 */61, 0x00,
/* ABS: 003 Pixels @ 061,032 */0, 3, 0x23, 0x30,
/* RLE: 061 Pixels @ 000,033 */61, 0x00,
/* ABS: 003 Pixels @ 061,033 */0, 3, 0x23, 0x30,
/* RLE: 061 Pixels @ 000,034 */61, 0x00,
/* ABS: 003 Pixels @ 061,034 */0, 3, 0x23, 0x30,
/* RLE: 062 Pixels @ 000,035 */62, 0x00,
/* ABS: 002 Pixels @ 062,035 */0, 2, 0x33,
/* RLE: 062 Pixels @ 000,036 */62, 0x00,
/* ABS: 002 Pixels @ 062,036 */0, 2, 0x22,
/* RLE: 1728 Pixels @ 000,037 */254, 0x00, 254, 0x00, 254, 0x00, 254, 0x00, 254,
		0x00, 254, 0x00, 204, 0x00, 0 };  // 251 bytes for 4096 pixels

GUI_CONST_STORAGE GUI_BITMAP bmcalling3 = { 64, // xSize
		64, // ySize
		32, // BytesPerLine
		GUI_COMPRESS_RLE4, // BitsPerPixel
		_accalling3,  // Pointer to picture data (indices)
		&_Palcalling,  // Pointer to palette
		GUI_DRAW_RLE4 };

static GUI_CONST_STORAGE unsigned char _accalling2[] = {
/* RLE: 540 Pixels @ 000,000 */254, 0x00, 254, 0x00, 32, 0x00,
/* RLE: 001 Pixels @ 028,008 */1, 0x01,
/* RLE: 004 Pixels @ 029,008 */4, 0x03,
/* ABS: 003 Pixels @ 033,008 */0, 3, 0x11, 0x20,
/* RLE: 056 Pixels @ 036,008 */56, 0x00,
/* RLE: 001 Pixels @ 028,009 */1, 0x01,
/* RLE: 008 Pixels @ 029,009 */8, 0x03,
/* ABS: 002 Pixels @ 037,009 */0, 2, 0x12,
/* RLE: 054 Pixels @ 039,009 */54, 0x00,
/* RLE: 004 Pixels @ 029,010 */4, 0x02,
/* ABS: 002 Pixels @ 033,010 */0, 2, 0x11,
/* RLE: 005 Pixels @ 035,010 */5, 0x03,
/* RLE: 001 Pixels @ 040,010 */1, 0x01,
/* RLE: 059 Pixels @ 041,010 */59, 0x00,
/* ABS: 002 Pixels @ 036,011 */0, 2, 0x21,
/* RLE: 004 Pixels @ 038,011 */4, 0x03,
/* RLE: 001 Pixels @ 042,011 */1, 0x01,
/* RLE: 060 Pixels @ 043,011 */60, 0x00,
/* RLE: 001 Pixels @ 039,012 */1, 0x02,
/* RLE: 004 Pixels @ 040,012 */4, 0x03,
/* RLE: 001 Pixels @ 044,012 */1, 0x02,
/* RLE: 060 Pixels @ 045,012 */60, 0x00,
/* ABS: 005 Pixels @ 041,013 */0, 5, 0x23, 0x33, 0x10,
/* RLE: 061 Pixels @ 046,013 */61, 0x00,
/* ABS: 004 Pixels @ 043,014 */0, 4, 0x13, 0x33,
/* RLE: 061 Pixels @ 047,014 */61, 0x00,
/* ABS: 004 Pixels @ 044,015 */0, 4, 0x23, 0x33,
/* RLE: 061 Pixels @ 048,015 */61, 0x00,
/* ABS: 004 Pixels @ 045,016 */0, 4, 0x23, 0x33,
/* RLE: 061 Pixels @ 049,016 */61, 0x00,
/* ABS: 004 Pixels @ 046,017 */0, 4, 0x23, 0x33,
/* RLE: 061 Pixels @ 050,017 */61, 0x00,
/* ABS: 004 Pixels @ 047,018 */0, 4, 0x23, 0x31,
/* RLE: 061 Pixels @ 051,018 */61, 0x00,
/* ABS: 004 Pixels @ 048,019 */0, 4, 0x23, 0x31,
/* RLE: 061 Pixels @ 052,019 */61, 0x00,
/* ABS: 003 Pixels @ 049,020 */0, 3, 0x13, 0x30,
/* RLE: 062 Pixels @ 052,020 */62, 0x00,
/* ABS: 003 Pixels @ 050,021 */0, 3, 0x33, 0x10,
/* RLE: 061 Pixels @ 053,021 */61, 0x00,
/* ABS: 004 Pixels @ 050,022 */0, 4, 0x23, 0x32,
/* RLE: 061 Pixels @ 054,022 */61, 0x00,
/* ABS: 003 Pixels @ 051,023 */0, 3, 0x13, 0x30,
/* RLE: 062 Pixels @ 054,023 */62, 0x00,
/* ABS: 003 Pixels @ 052,024 */0, 3, 0x33, 0x20,
/* RLE: 061 Pixels @ 055,024 */61, 0x00,
/* ABS: 003 Pixels @ 052,025 */0, 3, 0x13, 0x10,
/* RLE: 061 Pixels @ 055,025 */61, 0x00,
/* ABS: 003 Pixels @ 052,026 */0, 3, 0x23, 0x30,
/* RLE: 062 Pixels @ 055,026 */62, 0x00,
/* ABS: 003 Pixels @ 053,027 */0, 3, 0x33, 0x20,
/* RLE: 061 Pixels @ 056,027 */61, 0x00,
/* ABS: 003 Pixels @ 053,028 */0, 3, 0x13, 0x10,
/* RLE: 061 Pixels @ 056,028 */61, 0x00,
/* ABS: 003 Pixels @ 053,029 */0, 3, 0x23, 0x30,
/* RLE: 062 Pixels @ 056,029 */62, 0x00,
/* ABS: 002 Pixels @ 054,030 */0, 2, 0x33,
/* RLE: 062 Pixels @ 056,030 */62, 0x00,
/* ABS: 003 Pixels @ 054,031 */0, 3, 0x33, 0x20,
/* RLE: 061 Pixels @ 057,031 */61, 0x00,
/* ABS: 003 Pixels @ 054,032 */0, 3, 0x33, 0x20,
/* RLE: 061 Pixels @ 057,032 */61, 0x00,
/* ABS: 003 Pixels @ 054,033 */0, 3, 0x13, 0x10,
/* RLE: 061 Pixels @ 057,033 */61, 0x00,
/* ABS: 003 Pixels @ 054,034 */0, 3, 0x13, 0x10,
/* RLE: 061 Pixels @ 057,034 */61, 0x00,
/* ABS: 003 Pixels @ 054,035 */0, 3, 0x13, 0x10,
/* RLE: 062 Pixels @ 057,035 */62, 0x00,
/* RLE: 001 Pixels @ 055,036 */1, 0x02,
/* RLE: 1736 Pixels @ 056,036 */254, 0x00, 254, 0x00, 254, 0x00, 254, 0x00, 254,
		0x00, 254, 0x00, 212, 0x00, 0 };  // 207 bytes for 4096 pixels

GUI_CONST_STORAGE GUI_BITMAP bmcalling2 = { 64, // xSize
		64, // ySize
		32, // BytesPerLine
		GUI_COMPRESS_RLE4, // BitsPerPixel
		_accalling2,  // Pointer to picture data (indices)
		&_Palcalling,  // Pointer to palette
  GUI_DRAW_RLE4
};

GUI_CONST_STORAGE GUI_BITMAP * _abmcalling[] = { &bmcalling1, &bmcalling2,
		&bmcalling3 };

/*************************** End of file ****************************/
