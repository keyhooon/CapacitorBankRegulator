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
* Source file: phonecall                                             *
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
static GUI_CONST_STORAGE GUI_COLOR _Colorsphonecall[] = {
  0xFEFEFE, 0x747474, 0x9E9E9E, 0x060606
};

static GUI_CONST_STORAGE GUI_LOGPALETTE _Palphonecall = {
  4,  // Number of entries
  1,  // Has transparency
  &_Colorsphonecall[0]
};

static GUI_CONST_STORAGE unsigned char _acphonecall[] = {
  /* RLE: 013 Pixels @ 000,000 */ 13, 0x00,
  /* ABS: 002 Pixels @ 013,000 */ 0, 2, 0x11,
  /* RLE: 013 Pixels @ 015,000 */ 13, 0x00,
  /* ABS: 004 Pixels @ 012,001 */ 0, 4, 0x13, 0x32,
  /* RLE: 011 Pixels @ 000,002 */ 11, 0x00,
  /* RLE: 001 Pixels @ 011,002 */ 1, 0x01,
  /* RLE: 004 Pixels @ 012,002 */ 4, 0x03,
  /* RLE: 010 Pixels @ 000,003 */ 10, 0x00,
  /* RLE: 001 Pixels @ 010,003 */ 1, 0x01,
  /* RLE: 005 Pixels @ 011,003 */ 5, 0x03,
  /* RLE: 010 Pixels @ 000,004 */ 10, 0x00,
  /* RLE: 001 Pixels @ 010,004 */ 1, 0x02,
  /* RLE: 005 Pixels @ 011,004 */ 5, 0x03,
  /* RLE: 011 Pixels @ 000,005 */ 11, 0x00,
  /* ABS: 005 Pixels @ 011,005 */ 0, 5, 0x13, 0x33, 0x20,
  /* RLE: 010 Pixels @ 000,006 */ 10, 0x00,
  /* RLE: 001 Pixels @ 010,006 */ 1, 0x02,
  /* RLE: 004 Pixels @ 011,006 */ 4, 0x03,
  /* RLE: 010 Pixels @ 015,006 */ 10, 0x00,
  /* RLE: 001 Pixels @ 009,007 */ 1, 0x02,
  /* RLE: 004 Pixels @ 010,007 */ 4, 0x03,
  /* RLE: 001 Pixels @ 014,007 */ 1, 0x02,
  /* RLE: 009 Pixels @ 015,007 */ 9, 0x00,
  /* RLE: 001 Pixels @ 008,008 */ 1, 0x02,
  /* RLE: 004 Pixels @ 009,008 */ 4, 0x03,
  /* RLE: 001 Pixels @ 013,008 */ 1, 0x01,
  /* RLE: 009 Pixels @ 014,008 */ 9, 0x00,
  /* RLE: 001 Pixels @ 007,009 */ 1, 0x02,
  /* RLE: 005 Pixels @ 008,009 */ 5, 0x03,
  /* RLE: 006 Pixels @ 013,009 */ 6, 0x00,
  /* ABS: 004 Pixels @ 003,010 */ 0, 4, 0x12, 0x02,
  /* RLE: 005 Pixels @ 007,010 */ 5, 0x03,
  /* RLE: 006 Pixels @ 012,010 */ 6, 0x00,
  /* ABS: 004 Pixels @ 002,011 */ 0, 4, 0x13, 0x31,
  /* RLE: 005 Pixels @ 006,011 */ 5, 0x03,
  /* RLE: 006 Pixels @ 011,011 */ 6, 0x00,
  /* RLE: 001 Pixels @ 001,012 */ 1, 0x01,
  /* RLE: 008 Pixels @ 002,012 */ 8, 0x03,
  /* RLE: 006 Pixels @ 010,012 */ 6, 0x00,
  /* RLE: 001 Pixels @ 000,013 */ 1, 0x01,
  /* RLE: 007 Pixels @ 001,013 */ 7, 0x03,
  /* RLE: 001 Pixels @ 008,013 */ 1, 0x01,
  /* RLE: 007 Pixels @ 009,013 */ 7, 0x00,
  /* RLE: 001 Pixels @ 000,014 */ 1, 0x01,
  /* RLE: 006 Pixels @ 001,014 */ 6, 0x03,
  /* RLE: 001 Pixels @ 007,014 */ 1, 0x02,
  /* RLE: 009 Pixels @ 008,014 */ 9, 0x00,
  /* ABS: 005 Pixels @ 001,015 */ 0, 5, 0x23, 0x33, 0x20,
  /* RLE: 010 Pixels @ 006,015 */ 10, 0x00,
  0
};  // 111 bytes for 256 pixels

GUI_CONST_STORAGE GUI_BITMAP bmphonecall = {
  16, // xSize
  16, // ySize
  8, // BytesPerLine
  GUI_COMPRESS_RLE4, // BitsPerPixel
  _acphonecall,  // Pointer to picture data (indices)
  &_Palphonecall,  // Pointer to palette
  GUI_DRAW_RLE4
};

/*************************** End of file ****************************/
