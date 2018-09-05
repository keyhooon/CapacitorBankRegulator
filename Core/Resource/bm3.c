/*
 * bm3.c
 *
 *  Created on: Sep 4, 2018
 *      Author: HP
 */

#include "DIALOG.h"

/*********************************************************************
 *
 *       bm3
 */
static GUI_CONST_STORAGE unsigned char _ac3[] = {
/* RLE: 032 Pixels @ 000,000 */32, 0xFF,
/* ABS: 003 Pixels @ 000,001 */0, 3, 0x80, 0x33, 0x34,
/* RLE: 026 Pixels @ 003,001 */26, 0x35,
/* ABS: 004 Pixels @ 029,001 */0, 4, 0x34, 0x33, 0x81, 0x09,
/* RLE: 030 Pixels @ 001,002 */30, 0x00,
/* ABS: 002 Pixels @ 031,002 */0, 2, 0x0B, 0x0E,
/* RLE: 030 Pixels @ 001,003 */30, 0x00,
/* ABS: 002 Pixels @ 031,003 */0, 2, 0x10, 0x0F,
/* RLE: 030 Pixels @ 001,004 */30, 0x00,
/* ABS: 002 Pixels @ 031,004 */0, 2, 0x11, 0x0F,
/* RLE: 030 Pixels @ 001,005 */30, 0x00,
/* ABS: 002 Pixels @ 031,005 */0, 2, 0x11, 0x07,
/* RLE: 030 Pixels @ 001,006 */30, 0x00,
/* ABS: 003 Pixels @ 031,006 */0, 3, 0x0A, 0x4B, 0x11,
/* RLE: 028 Pixels @ 002,007 */28, 0x13,
/* ABS: 004 Pixels @ 030,007 */0, 4, 0x11, 0x4D, 0xFC, 0xF0,
/* RLE: 028 Pixels @ 002,008 */28, 0xF1,
/* ABS: 002 Pixels @ 030,008 */0, 2, 0xF0, 0xFC,
/* RLE: 096 Pixels @ 000,009 */96, 0xFF,
/* RLE: 001 Pixels @ 000,012 */1, 0x81,
/* RLE: 030 Pixels @ 001,012 */30, 0x47,
/* ABS: 002 Pixels @ 031,012 */0, 2, 0x83, 0x07,
/* RLE: 030 Pixels @ 001,013 */30, 0x00,
/* ABS: 002 Pixels @ 031,013 */0, 2, 0x09, 0x0E,
/* RLE: 030 Pixels @ 001,014 */30, 0x00,
/* ABS: 002 Pixels @ 031,014 */0, 2, 0x10, 0x0F,
/* RLE: 030 Pixels @ 001,015 */30, 0x00,
/* ABS: 002 Pixels @ 031,015 */0, 2, 0x11, 0x0F,
/* RLE: 030 Pixels @ 001,016 */30, 0x00,
/* ABS: 002 Pixels @ 031,016 */0, 2, 0x11, 0x07,
/* RLE: 030 Pixels @ 001,017 */30, 0x00,
/* ABS: 003 Pixels @ 031,017 */0, 3, 0x09, 0x5B, 0x21,
/* RLE: 028 Pixels @ 002,018 */28, 0x22,
/* ABS: 003 Pixels @ 030,018 */0, 3, 0x21, 0x5D, 0xFF,
/* RLE: 030 Pixels @ 001,019 */30, 0xF5,
/* RLE: 066 Pixels @ 031,019 */66, 0xFF,
/* RLE: 030 Pixels @ 001,022 */30, 0xFB,
/* ABS: 004 Pixels @ 031,022 */0, 4, 0xFF, 0x70, 0x35, 0x34,
/* RLE: 026 Pixels @ 003,023 */26, 0x35,
/* ABS: 004 Pixels @ 029,023 */0, 4, 0x34, 0x35, 0x71, 0x07,
/* RLE: 030 Pixels @ 001,024 */30, 0x00,
/* ABS: 002 Pixels @ 031,024 */0, 2, 0x09, 0x0E,
/* RLE: 030 Pixels @ 001,025 */30, 0x00,
/* ABS: 002 Pixels @ 031,025 */0, 2, 0x10, 0x0F,
/* RLE: 030 Pixels @ 001,026 */30, 0x00,
/* ABS: 002 Pixels @ 031,026 */0, 2, 0x11, 0x0E,
/* RLE: 030 Pixels @ 001,027 */30, 0x00,
/* ABS: 002 Pixels @ 031,027 */0, 2, 0x10, 0x06,
/* RLE: 030 Pixels @ 001,028 */30, 0x00,
/* ABS: 002 Pixels @ 031,028 */0, 2, 0x09, 0x6D,
/* RLE: 030 Pixels @ 001,029 */30, 0x38,
/* RLE: 001 Pixels @ 031,029 */1, 0x70,
/* RLE: 064 Pixels @ 000,030 */64, 0xFF, 0 };  // 164 bytes for 1024 pixels

GUI_CONST_STORAGE GUI_BITMAP bm3 = { 32, // xSize
		32, // ySize
		32, // BytesPerLine
		GUI_COMPRESS_RLE8, // BitsPerPixel
		(unsigned char *) _ac3,  // Pointer to picture data
		NULL,  // Pointer to palette
		GUI_DRAW_RLEALPHA };
