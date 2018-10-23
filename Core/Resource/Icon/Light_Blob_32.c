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
* Source file: Light_Blob_32                                         *
* Dimensions:  32 * 32                                               *
* NumColors:   25                                                    *
*                                                                    *
**********************************************************************
*/

#include <stdlib.h>

#include "GUI.h"

#ifndef GUI_CONST_STORAGE
  #define GUI_CONST_STORAGE const
#endif

extern GUI_CONST_STORAGE GUI_BITMAP bmLight_Blob_32;

#if 0


/*********************************************************************
*
*  This palette is included for reference only
*  As it is saved as device dependent bitmap without color info.
*  Please note that this bitmap requires the physical palette to be
*  identical to the palette of the display.
*  If this does not work out, please convert your bitmap into a DIB 
*/
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
static GUI_CONST_STORAGE GUI_COLOR _ColorsLight_Blob_32[] = {
  0xFFFFFF, 0x000000, 0x191919, 0x4C4C4C,
  0xFEFEFE, 0x080808, 0x343434, 0x404040,
  0x8D8D8D, 0x9A9A9A, 0xB3B3B3, 0xD6D6D6,
  0xFBFBFB, 0x808080, 0x0F0F0F, 0x202020,
  0x2D2D2D, 0x585858, 0x727272, 0x787878,
  0xB4B4B4, 0xB9B9B9, 0xE5E5E5, 0xFCFCFC,
  0x7F7F7F
};

#endif

static GUI_CONST_STORAGE GUI_LOGPALETTE _PalLight_Blob_32 = {
  25,  // Number of entries
  1,   // Has transparency
  NULL
};

static GUI_CONST_STORAGE unsigned char _acLight_Blob_32[] = {
  /* RLE: 011 Pixels @ 000,000 */ 11, 0x00, 
  /* ABS: 010 Pixels @ 011,000 */ 0, 10, 0x0C, 0x0A, 0x0D, 0x03, 0x02, 0x02, 0x03, 0x18, 0x0A, 0x0C, 
  /* RLE: 021 Pixels @ 021,000 */ 21, 0x00, 
  /* ABS: 002 Pixels @ 010,001 */ 0, 2, 0x0B, 0x06, 
  /* RLE: 008 Pixels @ 012,001 */ 8, 0x01, 
  /* ABS: 002 Pixels @ 020,001 */ 0, 2, 0x06, 0x0B, 
  /* RLE: 018 Pixels @ 022,001 */ 18, 0x00, 
  /* ABS: 003 Pixels @ 008,002 */ 0, 3, 0x04, 0x08, 0x05, 
  /* RLE: 010 Pixels @ 011,002 */ 10, 0x01, 
  /* ABS: 003 Pixels @ 021,002 */ 0, 3, 0x05, 0x08, 0x04, 
  /* RLE: 016 Pixels @ 024,002 */ 16, 0x00, 
  /* RLE: 001 Pixels @ 008,003 */ 1, 0x08, 
  /* RLE: 014 Pixels @ 009,003 */ 14, 0x01, 
  /* RLE: 001 Pixels @ 023,003 */ 1, 0x08, 
  /* RLE: 015 Pixels @ 024,003 */ 15, 0x00, 
  /* ABS: 002 Pixels @ 007,004 */ 0, 2, 0x0B, 0x05, 
  /* RLE: 014 Pixels @ 009,004 */ 14, 0x01, 
  /* ABS: 002 Pixels @ 023,004 */ 0, 2, 0x05, 0x0B, 
  /* RLE: 013 Pixels @ 025,004 */ 13, 0x00, 
  /* ABS: 002 Pixels @ 006,005 */ 0, 2, 0x0C, 0x06, 
  /* RLE: 016 Pixels @ 008,005 */ 16, 0x01, 
  /* ABS: 002 Pixels @ 024,005 */ 0, 2, 0x06, 0x0C, 
  /* RLE: 012 Pixels @ 026,005 */ 12, 0x00, 
  /* RLE: 001 Pixels @ 006,006 */ 1, 0x0A, 
  /* RLE: 018 Pixels @ 007,006 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 025,006 */ 1, 0x0A, 
  /* RLE: 012 Pixels @ 026,006 */ 12, 0x00, 
  /* RLE: 001 Pixels @ 006,007 */ 1, 0x0D, 
  /* RLE: 018 Pixels @ 007,007 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 025,007 */ 1, 0x0D, 
  /* RLE: 012 Pixels @ 026,007 */ 12, 0x00, 
  /* RLE: 001 Pixels @ 006,008 */ 1, 0x03, 
  /* RLE: 018 Pixels @ 007,008 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 025,008 */ 1, 0x03, 
  /* RLE: 012 Pixels @ 026,008 */ 12, 0x00, 
  /* RLE: 001 Pixels @ 006,009 */ 1, 0x02, 
  /* RLE: 018 Pixels @ 007,009 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 025,009 */ 1, 0x02, 
  /* RLE: 012 Pixels @ 026,009 */ 12, 0x00, 
  /* RLE: 001 Pixels @ 006,010 */ 1, 0x0E, 
  /* RLE: 018 Pixels @ 007,010 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 025,010 */ 1, 0x0E, 
  /* RLE: 012 Pixels @ 026,010 */ 12, 0x00, 
  /* RLE: 001 Pixels @ 006,011 */ 1, 0x10, 
  /* RLE: 018 Pixels @ 007,011 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 025,011 */ 1, 0x10, 
  /* RLE: 012 Pixels @ 026,011 */ 12, 0x00, 
  /* RLE: 001 Pixels @ 006,012 */ 1, 0x11, 
  /* RLE: 018 Pixels @ 007,012 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 025,012 */ 1, 0x11, 
  /* RLE: 012 Pixels @ 026,012 */ 12, 0x00, 
  /* RLE: 001 Pixels @ 006,013 */ 1, 0x14, 
  /* RLE: 018 Pixels @ 007,013 */ 18, 0x01, 
  /* RLE: 001 Pixels @ 025,013 */ 1, 0x14, 
  /* RLE: 012 Pixels @ 026,013 */ 12, 0x00, 
  /* ABS: 002 Pixels @ 006,014 */ 0, 2, 0x17, 0x0F, 
  /* RLE: 016 Pixels @ 008,014 */ 16, 0x01, 
  /* ABS: 002 Pixels @ 024,014 */ 0, 2, 0x0F, 0x17, 
  /* RLE: 013 Pixels @ 026,014 */ 13, 0x00, 
  /* RLE: 001 Pixels @ 007,015 */ 1, 0x15, 
  /* RLE: 016 Pixels @ 008,015 */ 16, 0x01, 
  /* RLE: 001 Pixels @ 024,015 */ 1, 0x15, 
  /* RLE: 015 Pixels @ 025,015 */ 15, 0x00, 
  /* RLE: 001 Pixels @ 008,016 */ 1, 0x12, 
  /* RLE: 014 Pixels @ 009,016 */ 14, 0x01, 
  /* RLE: 001 Pixels @ 023,016 */ 1, 0x12, 
  /* RLE: 017 Pixels @ 024,016 */ 17, 0x00, 
  /* RLE: 001 Pixels @ 009,017 */ 1, 0x13, 
  /* RLE: 012 Pixels @ 010,017 */ 12, 0x01, 
  /* RLE: 001 Pixels @ 022,017 */ 1, 0x13, 
  /* RLE: 019 Pixels @ 023,017 */ 19, 0x00, 
  /* RLE: 012 Pixels @ 010,018 */ 12, 0x01, 
  /* RLE: 020 Pixels @ 022,018 */ 20, 0x00, 
  /* RLE: 012 Pixels @ 010,019 */ 12, 0x01, 
  /* RLE: 020 Pixels @ 022,019 */ 20, 0x00, 
  /* RLE: 012 Pixels @ 010,020 */ 12, 0x01, 
  /* RLE: 020 Pixels @ 022,020 */ 20, 0x00, 
  /* RLE: 012 Pixels @ 010,021 */ 12, 0x01, 
  /* RLE: 084 Pixels @ 022,021 */ 84, 0x00, 
  /* RLE: 012 Pixels @ 010,024 */ 12, 0x01, 
  /* RLE: 020 Pixels @ 022,024 */ 20, 0x00, 
  /* RLE: 012 Pixels @ 010,025 */ 12, 0x01, 
  /* RLE: 020 Pixels @ 022,025 */ 20, 0x00, 
  /* RLE: 001 Pixels @ 010,026 */ 1, 0x02, 
  /* RLE: 010 Pixels @ 011,026 */ 10, 0x01, 
  /* RLE: 001 Pixels @ 021,026 */ 1, 0x02, 
  /* RLE: 020 Pixels @ 022,026 */ 20, 0x00, 
  /* RLE: 001 Pixels @ 010,027 */ 1, 0x03, 
  /* RLE: 010 Pixels @ 011,027 */ 10, 0x01, 
  /* RLE: 001 Pixels @ 021,027 */ 1, 0x03, 
  /* RLE: 020 Pixels @ 022,027 */ 20, 0x00, 
  /* RLE: 001 Pixels @ 010,028 */ 1, 0x09, 
  /* RLE: 010 Pixels @ 011,028 */ 10, 0x01, 
  /* RLE: 001 Pixels @ 021,028 */ 1, 0x09, 
  /* RLE: 020 Pixels @ 022,028 */ 20, 0x00, 
  /* ABS: 002 Pixels @ 010,029 */ 0, 2, 0x04, 0x07, 
  /* RLE: 008 Pixels @ 012,029 */ 8, 0x01, 
  /* ABS: 002 Pixels @ 020,029 */ 0, 2, 0x07, 0x04, 
  /* RLE: 021 Pixels @ 022,029 */ 21, 0x00, 
  /* ABS: 002 Pixels @ 011,030 */ 0, 2, 0x16, 0x07, 
  /* RLE: 006 Pixels @ 013,030 */ 6, 0x01, 
  /* ABS: 002 Pixels @ 019,030 */ 0, 2, 0x07, 0x16, 
  /* RLE: 023 Pixels @ 021,030 */ 23, 0x00, 
  /* ABS: 008 Pixels @ 012,031 */ 0, 8, 0x04, 0x09, 0x03, 0x02, 0x02, 0x03, 0x09, 0x04, 
  /* RLE: 012 Pixels @ 020,031 */ 12, 0x00, 
  0
};  // 258 bytes for 1024 pixels

GUI_CONST_STORAGE GUI_BITMAP bmLight_Blob_32 = {
  32, // xSize
  32, // ySize
  32, // BytesPerLine
  GUI_COMPRESS_RLE8, // BitsPerPixel
  _acLight_Blob_32,  // Pointer to picture data (indices)
  &_PalLight_Blob_32,  // Pointer to palette
  GUI_DRAW_RLE8
};

/*************************** End of file ****************************/