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
* Source file: loupe                                                 *
* Dimensions:  16 * 16                                               *
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
static GUI_CONST_STORAGE GUI_COLOR _Colorsloupe[] = {
  0xFAFAFA, 0x656565, 0x9F9F9F, 0x070707
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _Palloupe = {
  4,  // Number of entries
  1,  // Has transparency
  &_Colorsloupe[0]
};

static GUI_CONST_STORAGE unsigned char _acloupe[] = {
  /* RLE: 004 Pixels @ 000,000 */ 4, 0x00,
  /* ABS: 006 Pixels @ 004,000 */ 0, 6, 0x13, 0x33, 0x12,
  /* RLE: 008 Pixels @ 010,000 */ 8, 0x00,
  /* RLE: 001 Pixels @ 002,001 */ 1, 0x01,
  /* RLE: 008 Pixels @ 003,001 */ 8, 0x03,
  /* RLE: 006 Pixels @ 011,001 */ 6, 0x00,
  /* ABS: 007 Pixels @ 001,002 */ 0, 7, 0x13, 0x33, 0x11, 0x10,
  /* RLE: 004 Pixels @ 008,002 */ 4, 0x03,
  /* RLE: 005 Pixels @ 012,002 */ 5, 0x00,
  /* RLE: 003 Pixels @ 001,003 */ 3, 0x03,
  /* RLE: 005 Pixels @ 004,003 */ 5, 0x00,
  /* ABS: 010 Pixels @ 009,003 */ 0, 10, 0x23, 0x31, 0x00, 0x01, 0x33,
  /* RLE: 007 Pixels @ 003,004 */ 7, 0x00,
  /* ABS: 009 Pixels @ 010,004 */ 0, 9, 0x13, 0x30, 0x00, 0x33, 0x10,
  /* RLE: 008 Pixels @ 003,005 */ 8, 0x00,
  /* ABS: 008 Pixels @ 011,005 */ 0, 8, 0x33, 0x20, 0x03, 0x31,
  /* RLE: 008 Pixels @ 003,006 */ 8, 0x00,
  /* ABS: 008 Pixels @ 011,006 */ 0, 8, 0x33, 0x10, 0x03, 0x31,
  /* RLE: 008 Pixels @ 003,007 */ 8, 0x00,
  /* ABS: 008 Pixels @ 011,007 */ 0, 8, 0x33, 0x20, 0x01, 0x33,
  /* RLE: 007 Pixels @ 003,008 */ 7, 0x00,
  /* ABS: 010 Pixels @ 010,008 */ 0, 10, 0x23, 0x32, 0x00, 0x23, 0x31,
  /* RLE: 006 Pixels @ 004,009 */ 6, 0x00,
  /* RLE: 003 Pixels @ 010,009 */ 3, 0x03,
  /* RLE: 004 Pixels @ 013,009 */ 4, 0x00,
  /* RLE: 003 Pixels @ 001,010 */ 3, 0x03,
  /* ABS: 009 Pixels @ 004,010 */ 0, 9, 0x12, 0x00, 0x23, 0x33, 0x10,
  /* RLE: 005 Pixels @ 013,010 */ 5, 0x00,
  /* RLE: 011 Pixels @ 002,011 */ 11, 0x03,
  /* RLE: 001 Pixels @ 013,011 */ 1, 0x02,
  /* RLE: 005 Pixels @ 014,011 */ 5, 0x00,
  /* RLE: 001 Pixels @ 003,012 */ 1, 0x01,
  /* RLE: 006 Pixels @ 004,012 */ 6, 0x03,
  /* ABS: 005 Pixels @ 010,012 */ 0, 5, 0x13, 0x33, 0x20,
  /* RLE: 006 Pixels @ 015,012 */ 6, 0x00,
  /* ABS: 011 Pixels @ 005,013 */ 0, 11, 0x21, 0x22, 0x00, 0x23, 0x33, 0x20,
  /* RLE: 012 Pixels @ 000,014 */ 12, 0x00,
  /* ABS: 004 Pixels @ 012,014 */ 0, 4, 0x23, 0x33,
  /* RLE: 013 Pixels @ 000,015 */ 13, 0x00,
  /* ABS: 003 Pixels @ 013,015 */ 0, 3, 0x23, 0x20,
  0
};  // 132 bytes for 256 pixels

GUI_CONST_STORAGE GUI_BITMAP bmloupe = {
  16, // xSize
  16, // ySize
  8, // BytesPerLine
  GUI_COMPRESS_RLE4, // BitsPerPixel
  _acloupe,  // Pointer to picture data (indices)
  &_Palloupe,  // Pointer to palette
  GUI_DRAW_RLE4
};

/*************************** End of file ****************************/
