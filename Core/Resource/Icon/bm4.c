/*
 * bm4.c
 *
 *  Created on: Sep 4, 2018
 *      Author: HP
 */

#include "DIALOG.h"

/*********************************************************************
 *
 *       bm4
 */
static GUI_CONST_STORAGE unsigned char _ac4[] = {
/* RLE: 034 Pixels @ 000,000 */34, 0xFF,
/* ABS: 003 Pixels @ 002,001 */0, 3, 0xC5, 0x56, 0x2B,
/* RLE: 012 Pixels @ 005,001 */12, 0x2D,
/* ABS: 003 Pixels @ 017,001 */0, 3, 0x23, 0x81, 0xFD,
/* RLE: 004 Pixels @ 020,001 */4, 0xFF,
/* ABS: 005 Pixels @ 024,001 */0, 5, 0xFD, 0x6B, 0x54, 0x8B, 0xD6,
/* RLE: 004 Pixels @ 029,001 */4, 0xFF,
/* ABS: 002 Pixels @ 001,002 */0, 2, 0xC5, 0x0C,
/* RLE: 014 Pixels @ 003,002 */14, 0x00,
/* ABS: 002 Pixels @ 017,002 */0, 2, 0x46, 0xEB,
/* RLE: 004 Pixels @ 019,002 */4, 0xFF,
/* ABS: 011 Pixels @ 023,002 */0, 11, 0xF7, 0x62, 0x00, 0x00, 0x00, 0x12, 0x9A,
		0xFF, 0xFF, 0xFF, 0x52,
		/* RLE: 014 Pixels @ 002,003 */14, 0x00,
		/* ABS: 002 Pixels @ 016,003 */0, 2, 0x57, 0xF3,
		/* RLE: 005 Pixels @ 018,003 */5, 0xFF,
		/* ABS: 002 Pixels @ 023,003 */0, 2, 0xEF, 0x54,
		/* RLE: 004 Pixels @ 025,003 */4, 0x00,
		/* ABS: 005 Pixels @ 029,003 */0, 5, 0x04, 0xCB, 0xFF, 0xFF, 0x32,
		/* RLE: 013 Pixels @ 002,004 */13, 0x00,
		/* RLE: 001 Pixels @ 015,004 */1, 0x7F,
		/* RLE: 005 Pixels @ 016,004 */5, 0xFF,
		/* ABS: 018 Pixels @ 021,004 */0, 18, 0xFB, 0xD5, 0xFF, 0xFF, 0x94,
		0x07, 0x00, 0x00, 0x00, 0x6D, 0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00, 0x6D,
		0xAB,
		/* RLE: 007 Pixels @ 007,005 */7, 0xA8,
		/* RLE: 001 Pixels @ 014,005 */1, 0xB7,
		/* RLE: 006 Pixels @ 015,005 */6, 0xFF,
		/* ABS: 017 Pixels @ 021,005 */0, 17, 0x6C, 0x0B, 0x6B, 0xF1, 0xFF,
		0xAC, 0x0A, 0x00, 0x00, 0x36, 0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00, 0xAD,
		/* RLE: 014 Pixels @ 006,006 */14, 0xFF,
		/* ABS: 018 Pixels @ 020,006 */0, 18, 0x6D, 0x00, 0x00, 0x00, 0x37,
		0xE0, 0xFF, 0xA2, 0x02, 0x00, 0x30, 0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00,
		0xA5,
		/* RLE: 012 Pixels @ 006,007 */12, 0xFF,
		/* ABS: 002 Pixels @ 018,007 */0, 2, 0xFE, 0x6C,
		/* RLE: 005 Pixels @ 020,007 */5, 0x00,
		/* ABS: 013 Pixels @ 025,007 */0, 13, 0x31, 0xEA, 0xFF, 0x6B, 0x19,
		0xCA, 0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00, 0xA5,
		/* RLE: 011 Pixels @ 006,008 */11, 0xFF,
		/* ABS: 002 Pixels @ 017,008 */0, 2, 0xFE, 0x6C,
		/* RLE: 007 Pixels @ 019,008 */7, 0x00,
		/* ABS: 012 Pixels @ 026,008 */0, 12, 0x58, 0xFE, 0xEE, 0xD4, 0xFF,
		0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00, 0xA5,
		/* RLE: 011 Pixels @ 006,009 */11, 0xFF,
		/* RLE: 001 Pixels @ 017,009 */1, 0x6C,
		/* RLE: 009 Pixels @ 018,009 */9, 0x00,
		/* RLE: 001 Pixels @ 027,009 */1, 0xAD,
		/* RLE: 005 Pixels @ 028,009 */5, 0xFF,
		/* ABS: 005 Pixels @ 001,010 */0, 5, 0x35, 0x00, 0x00, 0x00, 0xA5,
		/* RLE: 009 Pixels @ 006,010 */9, 0xFF,
		/* ABS: 002 Pixels @ 015,010 */0, 2, 0xEB, 0x5D,
		/* RLE: 009 Pixels @ 017,010 */9, 0x00,
		/* ABS: 002 Pixels @ 026,010 */0, 2, 0x1C, 0xCA,
		/* RLE: 005 Pixels @ 028,010 */5, 0xFF,
		/* ABS: 005 Pixels @ 001,011 */0, 5, 0x35, 0x00, 0x00, 0x00, 0xA5,
		/* RLE: 008 Pixels @ 006,011 */8, 0xFF,
		/* ABS: 002 Pixels @ 014,011 */0, 2, 0xEB, 0x3E,
		/* RLE: 009 Pixels @ 016,011 */9, 0x00,
		/* ABS: 002 Pixels @ 025,011 */0, 2, 0x1D, 0xCE,
		/* RLE: 006 Pixels @ 027,011 */6, 0xFF,
		/* ABS: 005 Pixels @ 001,012 */0, 5, 0x35, 0x00, 0x00, 0x00, 0xA5,
		/* RLE: 007 Pixels @ 006,012 */7, 0xFF,
		/* ABS: 002 Pixels @ 013,012 */0, 2, 0xEB, 0x3E,
		/* RLE: 009 Pixels @ 015,012 */9, 0x00,
		/* ABS: 002 Pixels @ 024,012 */0, 2, 0x1D, 0xCE,
		/* RLE: 007 Pixels @ 026,012 */7, 0xFF,
		/* ABS: 005 Pixels @ 001,013 */0, 5, 0x35, 0x00, 0x00, 0x00, 0xA5,
		/* RLE: 006 Pixels @ 006,013 */6, 0xFF,
		/* ABS: 002 Pixels @ 012,013 */0, 2, 0xEB, 0x3F,
		/* RLE: 009 Pixels @ 014,013 */9, 0x00,
		/* ABS: 002 Pixels @ 023,013 */0, 2, 0x1D, 0xCD,
		/* RLE: 005 Pixels @ 025,013 */5, 0xFF,
		/* ABS: 008 Pixels @ 030,013 */0, 8, 0xC0, 0xFF, 0xFF, 0x35, 0x00, 0x00,
		0x00, 0xA5,
		/* RLE: 005 Pixels @ 006,014 */5, 0xFF,
		/* ABS: 002 Pixels @ 011,014 */0, 2, 0xEB, 0x3E,
		/* RLE: 009 Pixels @ 013,014 */9, 0x00,
		/* ABS: 002 Pixels @ 022,014 */0, 2, 0x1D, 0xCE,
		/* RLE: 005 Pixels @ 024,014 */5, 0xFF,
		/* ABS: 009 Pixels @ 029,014 */0, 9, 0x9F, 0x23, 0xFF, 0xFF, 0x35, 0x00,
		0x00, 0x00, 0xA5,
		/* RLE: 004 Pixels @ 006,015 */4, 0xFF,
		/* ABS: 002 Pixels @ 010,015 */0, 2, 0xE7, 0x3E,
		/* RLE: 009 Pixels @ 012,015 */9, 0x00,
		/* ABS: 002 Pixels @ 021,015 */0, 2, 0x1B, 0xCD,
		/* RLE: 005 Pixels @ 023,015 */5, 0xFF,
		/* ABS: 010 Pixels @ 028,015 */0, 10, 0xA9, 0x04, 0x1B, 0xFF, 0xFF,
		0x35, 0x00, 0x00, 0x00, 0xA5,
		/* RLE: 004 Pixels @ 006,016 */4, 0xFF,
		/* RLE: 001 Pixels @ 010,016 */1, 0x74,
		/* RLE: 009 Pixels @ 011,016 */9, 0x00,
		/* ABS: 002 Pixels @ 020,016 */0, 2, 0x05, 0xB4,
		/* RLE: 005 Pixels @ 022,016 */5, 0xFF,
		/* ABS: 011 Pixels @ 027,016 */0, 11, 0xD1, 0x10, 0x00, 0x22, 0xFF,
		0xFF, 0x35, 0x00, 0x00, 0x00, 0xA5,
		/* RLE: 004 Pixels @ 006,017 */4, 0xFF,
		/* ABS: 002 Pixels @ 010,017 */0, 2, 0xDF, 0x5B,
		/* RLE: 007 Pixels @ 012,017 */7, 0x00,
		/* ABS: 002 Pixels @ 019,017 */0, 2, 0x05, 0xA1,
		/* RLE: 005 Pixels @ 021,017 */5, 0xFF,
		/* ABS: 019 Pixels @ 026,017 */0, 19, 0xED, 0x28, 0x00, 0x00, 0x22,
		0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00, 0xA5, 0xFF, 0xFB, 0x86, 0xAF, 0xFF,
		0xFF, 0x85,
		/* RLE: 005 Pixels @ 013,018 */5, 0x00,
		/* ABS: 002 Pixels @ 018,018 */0, 2, 0x04, 0xA1,
		/* RLE: 006 Pixels @ 020,018 */6, 0xFF,
		/* ABS: 025 Pixels @ 026,018 */0, 25, 0xDB, 0x04, 0x00, 0x00, 0x22,
		0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00, 0xA5, 0xFF, 0xF0, 0x03, 0x00, 0x68,
		0xF6, 0xFF, 0x8D, 0x00, 0x00, 0x00, 0x05, 0xA1,
		/* RLE: 007 Pixels @ 019,019 */7, 0xFF,
		/* ABS: 024 Pixels @ 026,019 */0, 24, 0xDD, 0x0A, 0x00, 0x00, 0x22,
		0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00, 0xA5, 0xFF, 0xF0, 0x0F, 0x00, 0x00,
		0x4A, 0xF3, 0xFF, 0x6D, 0x00, 0x04, 0xA1,
		/* RLE: 008 Pixels @ 018,020 */8, 0xFF,
		/* ABS: 023 Pixels @ 026,020 */0, 23, 0xDD, 0x0A, 0x00, 0x00, 0x22,
		0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00, 0xA5, 0xFF, 0xF0, 0x0F, 0x00, 0x00,
		0x00, 0x5C, 0xFF, 0xF4, 0x51, 0xA9,
		/* RLE: 009 Pixels @ 017,021 */9, 0xFF,
		/* ABS: 015 Pixels @ 026,021 */0, 15, 0xDD, 0x0A, 0x00, 0x00, 0x22,
		0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00, 0xA5, 0xFF, 0xF0, 0x0D,
		/* RLE: 004 Pixels @ 009,022 */4, 0x00,
		/* RLE: 001 Pixels @ 013,022 */1, 0x9B,
		/* RLE: 012 Pixels @ 014,022 */12, 0xFF,
		/* ABS: 015 Pixels @ 026,022 */0, 15, 0xDD, 0x0A, 0x00, 0x00, 0x22,
		0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00, 0xA5, 0xFF, 0xF0, 0x0E,
		/* RLE: 004 Pixels @ 009,023 */4, 0x00,
		/* ABS: 002 Pixels @ 013,023 */0, 2, 0x3E, 0xFC,
		/* RLE: 011 Pixels @ 015,023 */11, 0xFF,
		/* ABS: 015 Pixels @ 026,023 */0, 15, 0xDD, 0x0A, 0x00, 0x00, 0x22,
		0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00, 0xA5, 0xFF, 0xFB, 0xBC,
		/* RLE: 004 Pixels @ 009,024 */4, 0xB7,
		/* RLE: 001 Pixels @ 013,024 */1, 0xD8,
		/* RLE: 012 Pixels @ 014,024 */12, 0xFF,
		/* ABS: 012 Pixels @ 026,024 */0, 12, 0xDD, 0x0A, 0x00, 0x00, 0x22,
		0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00, 0xA9,
		/* RLE: 020 Pixels @ 006,025 */20, 0xFF,
		/* ABS: 013 Pixels @ 026,025 */0, 13, 0xE3, 0x0A, 0x00, 0x00, 0x22,
		0xFF, 0xFF, 0x35, 0x00, 0x00, 0x00, 0x8F, 0xDF,
		/* RLE: 018 Pixels @ 007,026 */18, 0xDD,
		/* ABS: 013 Pixels @ 025,026 */0, 13, 0xDE, 0xBF, 0x09, 0x00, 0x00,
		0x22, 0xFF, 0xFF, 0x33, 0x00, 0x00, 0x00, 0x06,
		/* RLE: 020 Pixels @ 006,027 */20, 0x0A,
		/* ABS: 008 Pixels @ 026,027 */0, 8, 0x09, 0x00, 0x00, 0x00, 0x21, 0xFF,
		0xFF, 0x40,
		/* RLE: 028 Pixels @ 002,028 */28, 0x00,
		/* ABS: 004 Pixels @ 030,028 */0, 4, 0x25, 0xFF, 0xFF, 0xA8,
		/* RLE: 028 Pixels @ 002,029 */28, 0x00,
		/* ABS: 007 Pixels @ 030,029 */0, 7, 0x71, 0xFF, 0xFF, 0xFF, 0x93, 0x33,
		0x21,
		/* RLE: 022 Pixels @ 005,030 */22, 0x22,
		/* ABS: 004 Pixels @ 027,030 */0, 4, 0x21, 0x2B, 0x72, 0xF2,
		/* RLE: 033 Pixels @ 031,030 */33, 0xFF, 0 }; // 656 bytes for 1024 pixels

GUI_CONST_STORAGE GUI_BITMAP bm4 = { 32, // xSize
		32, // ySize
		32, // BytesPerLine
		GUI_COMPRESS_RLE8, // BitsPerPixel
		(unsigned char *) _ac4,  // Pointer to picture data
		NULL,  // Pointer to palette
		GUI_DRAW_RLEALPHA };
