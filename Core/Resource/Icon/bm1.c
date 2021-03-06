/*
 * bm1.c
 *
 *  Created on: Sep 4, 2018
 *      Author: HP
 */

#include "DIALOG.h"

/*********************************************************************
 *
 *       bm1
 */
static GUI_CONST_STORAGE unsigned char _ac1[] = {
/* RLE: 065 Pixels @ 000,000 */65, 0xFF,
/* ABS: 003 Pixels @ 001,002 */0, 3, 0xA1, 0x66, 0x59,
/* RLE: 024 Pixels @ 004,002 */24, 0x5A,
/* ABS: 005 Pixels @ 028,002 */0, 5, 0x59, 0x67, 0xA6, 0xFF, 0x85,
/* RLE: 030 Pixels @ 001,003 */30, 0x00,
/* ABS: 002 Pixels @ 031,003 */0, 2, 0x8F, 0x17,
/* RLE: 030 Pixels @ 001,004 */30, 0x00,
/* ABS: 002 Pixels @ 031,004 */0, 2, 0x1F, 0x03,
/* RLE: 030 Pixels @ 001,005 */30, 0x00,
/* ABS: 002 Pixels @ 031,005 */0, 2, 0x06, 0x5A,
/* RLE: 030 Pixels @ 001,006 */30, 0x00,
/* ABS: 004 Pixels @ 031,006 */0, 4, 0x4B, 0xFD, 0x84, 0x03,
/* RLE: 027 Pixels @ 003,007 */27, 0x00,
/* ABS: 006 Pixels @ 030,007 */0, 6, 0x70, 0xF6, 0xFF, 0xFF, 0xB1, 0x19,
/* RLE: 024 Pixels @ 004,008 */24, 0x00,
/* ABS: 002 Pixels @ 028,008 */0, 2, 0x0F, 0xA1,
/* RLE: 005 Pixels @ 030,008 */5, 0xFF,
/* ABS: 002 Pixels @ 003,009 */0, 2, 0xC3, 0x19,
/* RLE: 022 Pixels @ 005,009 */22, 0x00,
/* ABS: 011 Pixels @ 027,009 */0, 11, 0x0F, 0xB2, 0xFF, 0xFF, 0xFF, 0xED, 0xFF,
		0xFF, 0xFF, 0xD6, 0x41,
		/* RLE: 020 Pixels @ 006,010 */20, 0x00,
		/* ABS: 014 Pixels @ 026,010 */0, 14, 0x34, 0xC9, 0xFF, 0xFF, 0xFF,
		0xEB, 0x34, 0xBB, 0xFF, 0xFF, 0xFF, 0xF7, 0x75, 0x01,
		/* RLE: 017 Pixels @ 008,011 */17, 0x00,
		/* ABS: 016 Pixels @ 025,011 */0, 16, 0x67, 0xF0, 0xFF, 0xFF, 0xFF,
		0xB8, 0x34, 0x05, 0x07, 0x8A, 0xFE, 0xFF, 0xFF, 0xFF, 0xAE, 0x21,
		/* RLE: 014 Pixels @ 009,012 */14, 0x00,
		/* ABS: 019 Pixels @ 023,012 */0, 19, 0x19, 0xA3, 0xFF, 0xFF, 0xFF,
		0xFE, 0x8A, 0x06, 0x09, 0x0F, 0x00, 0x00, 0x53, 0xE4, 0xFF, 0xFF, 0xFF,
		0xE0, 0x52,
		/* RLE: 012 Pixels @ 010,013 */12, 0x00,
		/* ABS: 016 Pixels @ 022,013 */0, 16, 0x47, 0xD8, 0xFF, 0xFF, 0xFF,
		0xE6, 0x54, 0x00, 0x00, 0x13, 0x0F, 0x00, 0x00, 0x00, 0x24, 0xB4,
		/* RLE: 004 Pixels @ 006,014 */4, 0xFF,
		/* ABS: 002 Pixels @ 010,014 */0, 2, 0x96, 0x14,
		/* RLE: 008 Pixels @ 012,014 */8, 0x00,
		/* ABS: 013 Pixels @ 020,014 */0, 13, 0x10, 0x8D, 0xFB, 0xFF, 0xFF,
		0xFF, 0xB8, 0x27, 0x00, 0x00, 0x00, 0x13, 0x0F,
		/* RLE: 004 Pixels @ 001,015 */4, 0x00,
		/* ABS: 008 Pixels @ 005,015 */0, 8, 0x03, 0x76, 0xF8, 0xFF, 0xFF, 0xFF,
		0xD6, 0x51,
		/* RLE: 006 Pixels @ 013,015 */6, 0x00,
		/* ABS: 008 Pixels @ 019,015 */0, 8, 0x4D, 0xD2, 0xFF, 0xFF, 0xFF, 0xFB,
		0x7D, 0x05,
		/* RLE: 004 Pixels @ 027,015 */4, 0x00,
		/* ABS: 002 Pixels @ 031,015 */0, 2, 0x13, 0x0F,
		/* RLE: 006 Pixels @ 001,016 */6, 0x00,
		/* ABS: 002 Pixels @ 007,016 */0, 2, 0x57, 0xED,
		/* RLE: 004 Pixels @ 009,016 */4, 0xFF,
		/* ABS: 006 Pixels @ 013,016 */0, 6, 0x80, 0x11, 0x00, 0x00, 0x11, 0x7E,
		/* RLE: 004 Pixels @ 019,016 */4, 0xFF,
		/* ABS: 002 Pixels @ 023,016 */0, 2, 0xF1, 0x5F,
		/* RLE: 006 Pixels @ 025,016 */6, 0x00,
		/* ABS: 002 Pixels @ 031,016 */0, 2, 0x13, 0x0F,
		/* RLE: 007 Pixels @ 001,017 */7, 0x00,
		/* ABS: 002 Pixels @ 008,017 */0, 2, 0x2F, 0xBC,
		/* RLE: 004 Pixels @ 010,017 */4, 0xFF,
		/* ABS: 004 Pixels @ 014,017 */0, 4, 0xD8, 0x83, 0x84, 0xD8,
		/* RLE: 004 Pixels @ 018,017 */4, 0xFF,
		/* ABS: 002 Pixels @ 022,017 */0, 2, 0xC4, 0x35,
		/* RLE: 007 Pixels @ 024,017 */7, 0x00,
		/* ABS: 002 Pixels @ 031,017 */0, 2, 0x12, 0x0F,
		/* RLE: 008 Pixels @ 001,018 */8, 0x00,
		/* ABS: 003 Pixels @ 009,018 */0, 3, 0x05, 0x72, 0xEE,
		/* RLE: 008 Pixels @ 012,018 */8, 0xFF,
		/* ABS: 003 Pixels @ 020,018 */0, 3, 0xF2, 0x7C, 0x09,
		/* RLE: 008 Pixels @ 023,018 */8, 0x00,
		/* ABS: 002 Pixels @ 031,018 */0, 2, 0x12, 0x0F,
		/* RLE: 010 Pixels @ 001,019 */10, 0x00,
		/* ABS: 002 Pixels @ 011,019 */0, 2, 0x2A, 0xAA,
		/* RLE: 006 Pixels @ 013,019 */6, 0xFF,
		/* ABS: 002 Pixels @ 019,019 */0, 2, 0xB2, 0x31,
		/* RLE: 010 Pixels @ 021,019 */10, 0x00,
		/* ABS: 002 Pixels @ 031,019 */0, 2, 0x12, 0x0F,
		/* RLE: 012 Pixels @ 001,020 */12, 0x00,
		/* ABS: 006 Pixels @ 013,020 */0, 6, 0x4A, 0xBB, 0xFA, 0xFA, 0xBD, 0x4F,
		/* RLE: 012 Pixels @ 019,020 */12, 0x00,
		/* ABS: 002 Pixels @ 031,020 */0, 2, 0x11, 0x0F,
		/* RLE: 014 Pixels @ 001,021 */14, 0x00,
		/* ABS: 002 Pixels @ 015,021 */0, 2, 0x33, 0x32,
		/* RLE: 014 Pixels @ 017,021 */14, 0x00,
		/* ABS: 002 Pixels @ 031,021 */0, 2, 0x11, 0x0F,
		/* RLE: 030 Pixels @ 001,022 */30, 0x00,
		/* ABS: 002 Pixels @ 031,022 */0, 2, 0x11, 0x0F,
		/* RLE: 030 Pixels @ 001,023 */30, 0x00,
		/* ABS: 002 Pixels @ 031,023 */0, 2, 0x10, 0x0F,
		/* RLE: 030 Pixels @ 001,024 */30, 0x00,
		/* ABS: 002 Pixels @ 031,024 */0, 2, 0x10, 0x0F,
		/* RLE: 030 Pixels @ 001,025 */30, 0x00,
		/* ABS: 002 Pixels @ 031,025 */0, 2, 0x10, 0x0E,
		/* RLE: 030 Pixels @ 001,026 */30, 0x00,
		/* ABS: 002 Pixels @ 031,026 */0, 2, 0x0E, 0x0F,
		/* RLE: 030 Pixels @ 001,027 */30, 0x00,
		/* ABS: 002 Pixels @ 031,027 */0, 2, 0x15, 0x60,
		/* RLE: 030 Pixels @ 001,028 */30, 0x00,
		/* ABS: 004 Pixels @ 031,028 */0, 4, 0x6A, 0xEF, 0x76, 0x3C,
		/* RLE: 026 Pixels @ 003,029 */26, 0x38,
		/* ABS: 003 Pixels @ 029,029 */0, 3, 0x3D, 0x7B, 0xF3,
		/* RLE: 064 Pixels @ 000,030 */64, 0xFF, 0 }; // 386 bytes for 1024 pixels

GUI_CONST_STORAGE GUI_BITMAP bm1 = { 32, // xSize
		32, // ySize
		32, // BytesPerLine
		GUI_COMPRESS_RLE8, // BitsPerPixel
		(unsigned char *) _ac1,  // Pointer to picture data
		NULL,  // Pointer to palette
		GUI_DRAW_RLEALPHA };
