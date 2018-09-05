/*
 * bm5.c
 *
 *  Created on: Sep 4, 2018
 *      Author: HP
 */


#include "DIALOG.h"

/*********************************************************************
 *
 *       bm5
 */
static GUI_CONST_STORAGE unsigned char _ac5[] = {
	/* RLE: 041 Pixels @ 000,000 */41, 0xFF,
	/* ABS: 004 Pixels @ 009,001 */0, 4, 0xF7, 0x8E, 0x3E, 0x2B,
	/* RLE: 006 Pixels @ 013,001 */6, 0x2D,
	/* ABS: 004 Pixels @ 019,001 */0, 4, 0x2C, 0x35, 0x7B, 0xEA,
	/* RLE: 018 Pixels @ 023,001 */18, 0xFF,
	/* RLE: 001 Pixels @ 009,002 */1, 0x67,
	/* RLE: 012 Pixels @ 010,002 */12, 0x00,
	/* ABS: 002 Pixels @ 022,002 */0, 2, 0x41, 0xF8,
	/* RLE: 016 Pixels @ 024,002 */16, 0xFF,
	/* ABS: 002 Pixels @ 008,003 */0, 2, 0xD0, 0x04,
	/* RLE: 013 Pixels @ 010,003 */13, 0x00,
	/* RLE: 001 Pixels @ 023,003 */1, 0xA9,
	/* RLE: 016 Pixels @ 024,003 */16, 0xFF,
	/* RLE: 001 Pixels @ 008,004 */1, 0x62,
	/* RLE: 014 Pixels @ 009,004 */14, 0x00,
	/* ABS: 002 Pixels @ 023,004 */0, 2, 0x3A, 0xFD,
	/* RLE: 008 Pixels @ 025,004 */8, 0xFF,
	/* ABS: 008 Pixels @ 001,005 */0, 8, 0xEC, 0x91, 0x61, 0x56, 0x56, 0x57, 0x53, 0x09,
	/* RLE: 015 Pixels @ 009,005 */15, 0x00,
	/* ABS: 010 Pixels @ 024,005 */0, 10, 0x4A, 0x57, 0x56, 0x56, 0x61, 0x8D, 0xE7, 0xFF, 0xD7, 0x2C,
	/* RLE: 028 Pixels @ 002,006 */28, 0x00,
	/* ABS: 003 Pixels @ 030,006 */0, 3, 0x26, 0xD0, 0x43,
	/* RLE: 030 Pixels @ 001,007 */30, 0x00,
	/* ABS: 002 Pixels @ 031,007 */0, 2, 0x3E, 0x0B,
	/* RLE: 030 Pixels @ 001,008 */30, 0x00,
	/* ABS: 002 Pixels @ 031,008 */0, 2, 0x0B, 0x0F,
	/* RLE: 011 Pixels @ 001,009 */11, 0x00,
	/* ABS: 008 Pixels @ 012,009 */0, 8, 0x07, 0x48, 0x83, 0xA0, 0xA0, 0x83, 0x48, 0x07,
	/* RLE: 011 Pixels @ 020,009 */11, 0x00,
	/* ABS: 002 Pixels @ 031,009 */0, 2, 0x0F, 0x0F,
	/* RLE: 010 Pixels @ 001,010 */10, 0x00,
	/* ABS: 002 Pixels @ 011,010 */0, 2, 0x38, 0xCD,
	/* RLE: 006 Pixels @ 013,010 */6, 0xFF,
	/* ABS: 002 Pixels @ 019,010 */0, 2, 0xCD, 0x37,
	/* RLE: 010 Pixels @ 021,010 */10, 0x00,
	/* ABS: 002 Pixels @ 031,010 */0, 2, 0x0F, 0x0F,
	/* RLE: 009 Pixels @ 001,011 */9, 0x00,
	/* ABS: 002 Pixels @ 010,011 */0, 2, 0x47, 0xE8,
	/* RLE: 008 Pixels @ 012,011 */8, 0xFF,
	/* ABS: 002 Pixels @ 020,011 */0, 2, 0xE7, 0x46,
	/* RLE: 009 Pixels @ 022,011 */9, 0x00,
	/* ABS: 002 Pixels @ 031,011 */0, 2, 0x0F, 0x0F,
	/* RLE: 008 Pixels @ 001,012 */8, 0x00,
	/* ABS: 014 Pixels @ 009,012 */0, 14, 0x39, 0xF1, 0xFF, 0xFF, 0xD1, 0x7C, 0x4E, 0x4E, 0x7C, 0xD2, 0xFF, 0xFF, 0xF1, 0x38,
	/* RLE: 008 Pixels @ 023,012 */8, 0x00,
	/* ABS: 002 Pixels @ 031,012 */0, 2, 0x0F, 0x0F,
	/* RLE: 007 Pixels @ 001,013 */7, 0x00,
	/* ABS: 006 Pixels @ 008,013 */0, 6, 0x0B, 0xD0, 0xFF, 0xFF, 0x8F, 0x0D,
	/* RLE: 004 Pixels @ 014,013 */4, 0x00,
	/* ABS: 006 Pixels @ 018,013 */0, 6, 0x0E, 0x90, 0xFF, 0xFF, 0xD0, 0x0A,
	/* RLE: 007 Pixels @ 024,013 */7, 0x00,
	/* ABS: 002 Pixels @ 031,013 */0, 2, 0x0F, 0x0F,
	/* RLE: 007 Pixels @ 001,014 */7, 0x00,
	/* ABS: 004 Pixels @ 008,014 */0, 4, 0x60, 0xFF, 0xFF, 0xA6,
	/* RLE: 008 Pixels @ 012,014 */8, 0x00,
	/* ABS: 004 Pixels @ 020,014 */0, 4, 0xA6, 0xFF, 0xFF, 0x60,
	/* RLE: 007 Pixels @ 024,014 */7, 0x00,
	/* ABS: 002 Pixels @ 031,014 */0, 2, 0x0F, 0x0F,
	/* RLE: 007 Pixels @ 001,015 */7, 0x00,
	/* ABS: 004 Pixels @ 008,015 */0, 4, 0xB1, 0xFF, 0xF4, 0x25,
	/* RLE: 008 Pixels @ 012,015 */8, 0x00,
	/* ABS: 004 Pixels @ 020,015 */0, 4, 0x25, 0xF4, 0xFF, 0xB0,
	/* RLE: 007 Pixels @ 024,015 */7, 0x00,
	/* ABS: 002 Pixels @ 031,015 */0, 2, 0x0F, 0x0F,
	/* RLE: 006 Pixels @ 001,016 */6, 0x00,
	/* ABS: 004 Pixels @ 007,016 */0, 4, 0x09, 0xDF, 0xFF, 0xBF,
	/* RLE: 010 Pixels @ 011,016 */10, 0x00,
	/* ABS: 004 Pixels @ 021,016 */0, 4, 0xC0, 0xFF, 0xDE, 0x09,
	/* RLE: 006 Pixels @ 025,016 */6, 0x00,
	/* ABS: 002 Pixels @ 031,016 */0, 2, 0x0F, 0x0F,
	/* RLE: 006 Pixels @ 001,017 */6, 0x00,
	/* ABS: 004 Pixels @ 007,017 */0, 4, 0x0F, 0xEF, 0xFF, 0xA4,
	/* RLE: 010 Pixels @ 011,017 */10, 0x00,
	/* ABS: 004 Pixels @ 021,017 */0, 4, 0xA5, 0xFF, 0xEE, 0x0F,
	/* RLE: 006 Pixels @ 025,017 */6, 0x00,
	/* ABS: 002 Pixels @ 031,017 */0, 2, 0x0F, 0x0F,
	/* RLE: 006 Pixels @ 001,018 */6, 0x00,
	/* ABS: 004 Pixels @ 007,018 */0, 4, 0x0B, 0xE2, 0xFF, 0xB8,
	/* RLE: 010 Pixels @ 011,018 */10, 0x00,
	/* ABS: 004 Pixels @ 021,018 */0, 4, 0xB9, 0xFF, 0xE2, 0x0B,
	/* RLE: 006 Pixels @ 025,018 */6, 0x00,
	/* ABS: 002 Pixels @ 031,018 */0, 2, 0x0F, 0x0F,
	/* RLE: 006 Pixels @ 001,019 */6, 0x00,
	/* ABS: 005 Pixels @ 007,019 */0, 5, 0x02, 0xBA, 0xFF, 0xED, 0x19,
	/* RLE: 008 Pixels @ 012,019 */8, 0x00,
	/* ABS: 005 Pixels @ 020,019 */0, 5, 0x1A, 0xED, 0xFF, 0xBA, 0x02,
	/* RLE: 006 Pixels @ 025,019 */6, 0x00,
	/* ABS: 002 Pixels @ 031,019 */0, 2, 0x0F, 0x0F,
	/* RLE: 007 Pixels @ 001,020 */7, 0x00,
	/* ABS: 004 Pixels @ 008,020 */0, 4, 0x82, 0xFF, 0xFF, 0x72,
	/* RLE: 008 Pixels @ 012,020 */8, 0x00,
	/* ABS: 004 Pixels @ 020,020 */0, 4, 0x73, 0xFF, 0xFF, 0x81,
	/* RLE: 007 Pixels @ 024,020 */7, 0x00,
	/* ABS: 002 Pixels @ 031,020 */0, 2, 0x0F, 0x0F,
	/* RLE: 007 Pixels @ 001,021 */7, 0x00,
	/* ABS: 005 Pixels @ 008,021 */0, 5, 0x28, 0xF4, 0xFF, 0xEC, 0x3F,
	/* RLE: 006 Pixels @ 013,021 */6, 0x00,
	/* ABS: 005 Pixels @ 019,021 */0, 5, 0x40, 0xED, 0xFF, 0xF3, 0x27,
	/* RLE: 007 Pixels @ 024,021 */7, 0x00,
	/* ABS: 002 Pixels @ 031,021 */0, 2, 0x0F, 0x0F,
	/* RLE: 008 Pixels @ 001,022 */8, 0x00,
	/* ABS: 014 Pixels @ 009,022 */0, 14, 0x79, 0xFF, 0xFF, 0xF2, 0x7B, 0x20, 0x06, 0x06, 0x21, 0x7B, 0xF2, 0xFF, 0xFF, 0x79,
	/* RLE: 008 Pixels @ 023,022 */8, 0x00,
	/* ABS: 002 Pixels @ 031,022 */0, 2, 0x0F, 0x0F,
	/* RLE: 008 Pixels @ 001,023 */8, 0x00,
	/* ABS: 014 Pixels @ 009,023 */0, 14, 0x02, 0x97, 0xFF, 0xFF, 0xFF, 0xF2, 0xD1, 0xD1, 0xF2, 0xFF, 0xFF, 0xFF, 0x96, 0x02,
	/* RLE: 008 Pixels @ 023,023 */8, 0x00,
	/* ABS: 002 Pixels @ 031,023 */0, 2, 0x0F, 0x0F,
	/* RLE: 010 Pixels @ 001,024 */10, 0x00,
	/* ABS: 002 Pixels @ 011,024 */0, 2, 0x6D, 0xE5,
	/* RLE: 006 Pixels @ 013,024 */6, 0xFF,
	/* ABS: 002 Pixels @ 019,024 */0, 2, 0xE5, 0x6C,
	/* RLE: 010 Pixels @ 021,024 */10, 0x00,
	/* ABS: 002 Pixels @ 031,024 */0, 2, 0x0F, 0x0F,
	/* RLE: 011 Pixels @ 001,025 */11, 0x00,
	/* ABS: 008 Pixels @ 012,025 */0, 8, 0x1C, 0x6D, 0xA7, 0xC5, 0xC5, 0xA7, 0x6D, 0x1B,
	/* RLE: 011 Pixels @ 020,025 */11, 0x00,
	/* ABS: 002 Pixels @ 031,025 */0, 2, 0x0F, 0x08,
	/* RLE: 014 Pixels @ 001,026 */14, 0x00,
	/* ABS: 002 Pixels @ 015,026 */0, 2, 0x03, 0x03,
	/* RLE: 014 Pixels @ 017,026 */14, 0x00,
	/* ABS: 002 Pixels @ 031,026 */0, 2, 0x08, 0x55,
	/* RLE: 030 Pixels @ 001,027 */30, 0x00,
	/* ABS: 003 Pixels @ 031,027 */0, 3, 0x52, 0xF2, 0x58,
	/* RLE: 028 Pixels @ 002,028 */28, 0x00,
	/* ABS: 007 Pixels @ 030,028 */0, 7, 0x51, 0xEF, 0xFF, 0xFE, 0x9D, 0x46, 0x37,
	/* RLE: 022 Pixels @ 005,029 */22, 0x38,
	/* ABS: 004 Pixels @ 027,029 */0, 4, 0x37, 0x45, 0x96, 0xFC,
	/* RLE: 065 Pixels @ 031,029 */65, 0xFF,
	0
};  // 499 bytes for 1024 pixels

GUI_CONST_STORAGE GUI_BITMAP bm5 = { 32, // xSize
		32, // ySize
		32, // BytesPerLine
		GUI_COMPRESS_RLE8, // BitsPerPixel
		(unsigned char *) _ac5,  // Pointer to picture data
		NULL,  // Pointer to palette
		GUI_DRAW_RLEALPHA };
