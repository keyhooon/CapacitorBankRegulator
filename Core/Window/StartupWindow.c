/*
 * StartupWindow.c
 *
 *  Created on: Sep 5, 2018
 *      Author: HP
 */

#include "DIALOG.h"
/* Private function prototypes -----------------------------------------------*/
static void BackGroundCallback(WM_MESSAGE * pMsg);
/* Private functions ---------------------------------------------------------*/

/**
 * @brief  Backbground callbacsk
 * @param  pMsg: pointer to data structure of type WM_MESSAGE
 * @retval None
 */

static void BackGroundCallback(WM_MESSAGE * pMsg) {
	switch (pMsg->MsgId) {
	case WM_PAINT:

		GUI_SetBkColor(GUI_RED);
		GUI_Clear();
		break;

	default:
		WM_DefaultProc(pMsg);
	}
}

/*********************************************************************
 *
 *       bm0
 */
static GUI_CONST_STORAGE unsigned char _ac0[] = {
/* RLE: 011 Pixels @ 000,000 */11, 0xFF,
/* ABS: 010 Pixels @ 011,000 */0, 10, 0xF6, 0xA8, 0x48, 0x1D, 0x11, 0x0E, 0x1E,
		0x47, 0x8E, 0xE7,
		/* RLE: 021 Pixels @ 021,000 */21, 0xFF,
		/* ABS: 002 Pixels @ 010,001 */0, 2, 0xBF, 0x30,
		/* RLE: 008 Pixels @ 012,001 */8, 0x00,
		/* ABS: 003 Pixels @ 020,001 */0, 3, 0x17, 0x97, 0xFE,
		/* RLE: 017 Pixels @ 023,001 */17, 0xFF,
		/* ABS: 003 Pixels @ 008,002 */0, 3, 0xFE, 0x91, 0x08,
		/* RLE: 011 Pixels @ 011,002 */11, 0x00,
		/* ABS: 002 Pixels @ 022,002 */0, 2, 0x69, 0xF8,
		/* RLE: 016 Pixels @ 024,002 */16, 0xFF,
		/* RLE: 001 Pixels @ 008,003 */1, 0x7B,
		/* RLE: 005 Pixels @ 009,003 */5, 0x00,
		/* ABS: 004 Pixels @ 014,003 */0, 4, 0x03, 0x0E, 0x0F, 0x06,
		/* RLE: 005 Pixels @ 018,003 */5, 0x00,
		/* ABS: 002 Pixels @ 023,003 */0, 2, 0x49, 0xF6,
		/* RLE: 014 Pixels @ 025,003 */14, 0xFF,
		/* ABS: 013 Pixels @ 007,004 */0, 13, 0xBE, 0x04, 0x00, 0x00, 0x00,
		0x03, 0x60, 0xC2, 0xED, 0xF1, 0xD3, 0x7F, 0x13,
		/* RLE: 004 Pixels @ 020,004 */4, 0x00,
		/* RLE: 001 Pixels @ 024,004 */1, 0x85,
		/* RLE: 014 Pixels @ 025,004 */14, 0xFF,
		/* ABS: 006 Pixels @ 007,005 */0, 6, 0x4A, 0x00, 0x00, 0x00, 0x06, 0xA2,
		/* RLE: 006 Pixels @ 013,005 */6, 0xFF,
		/* ABS: 007 Pixels @ 019,005 */0, 7, 0xCE, 0x21, 0x00, 0x00, 0x00, 0x19,
		0xE4,
		/* RLE: 012 Pixels @ 026,005 */12, 0xFF,
		/* ABS: 006 Pixels @ 006,006 */0, 6, 0xD4, 0x08, 0x00, 0x00, 0x00, 0x7D,
		/* RLE: 008 Pixels @ 012,006 */8, 0xFF,
		/* ABS: 006 Pixels @ 020,006 */0, 6, 0xB8, 0x01, 0x00, 0x00, 0x00, 0x99,
		/* RLE: 012 Pixels @ 026,006 */12, 0xFF,
		/* ABS: 006 Pixels @ 006,007 */0, 6, 0x9B, 0x00, 0x00, 0x00, 0x15, 0xE5,
		/* RLE: 009 Pixels @ 012,007 */9, 0xFF,
		/* ABS: 005 Pixels @ 021,007 */0, 5, 0x48, 0x00, 0x00, 0x00, 0x5F,
		/* RLE: 012 Pixels @ 026,007 */12, 0xFF,
		/* ABS: 005 Pixels @ 006,008 */0, 5, 0x7A, 0x00, 0x00, 0x00, 0x46,
		/* RLE: 010 Pixels @ 011,008 */10, 0xFF,
		/* ABS: 006 Pixels @ 021,008 */0, 6, 0x82, 0x00, 0x00, 0x00, 0x3E, 0xFE,
		/* RLE: 011 Pixels @ 027,008 */11, 0xFF,
		/* ABS: 005 Pixels @ 006,009 */0, 5, 0x71, 0x00, 0x00, 0x00, 0x56,
		/* RLE: 010 Pixels @ 011,009 */10, 0xFF,
		/* ABS: 006 Pixels @ 021,009 */0, 6, 0x93, 0x00, 0x00, 0x00, 0x34, 0xFA,
		/* RLE: 011 Pixels @ 027,009 */11, 0xFF,
		/* ABS: 005 Pixels @ 006,010 */0, 5, 0x70, 0x00, 0x00, 0x00, 0x57,
		/* RLE: 010 Pixels @ 011,010 */10, 0xFF,
		/* ABS: 006 Pixels @ 021,010 */0, 6, 0x94, 0x00, 0x00, 0x00, 0x33, 0xFA,
		/* RLE: 011 Pixels @ 027,010 */11, 0xFF,
		/* ABS: 005 Pixels @ 006,011 */0, 5, 0x71, 0x00, 0x00, 0x00, 0x57,
		/* RLE: 010 Pixels @ 011,011 */10, 0xFF,
		/* ABS: 006 Pixels @ 021,011 */0, 6, 0x94, 0x00, 0x00, 0x00, 0x34, 0xFA,
		/* RLE: 011 Pixels @ 027,011 */11, 0xFF,
		/* ABS: 005 Pixels @ 006,012 */0, 5, 0x71, 0x00, 0x00, 0x00, 0x57,
		/* RLE: 010 Pixels @ 011,012 */10, 0xFF,
		/* ABS: 006 Pixels @ 021,012 */0, 6, 0x94, 0x00, 0x00, 0x00, 0x35, 0xFB,
		/* RLE: 008 Pixels @ 027,012 */8, 0xFF,
		/* ABS: 010 Pixels @ 003,013 */0, 10, 0xCF, 0x69, 0x59, 0x26, 0x00,
		0x00, 0x00, 0x1D, 0x58, 0x57,
		/* RLE: 007 Pixels @ 013,013 */7, 0x56,
		/* ABS: 009 Pixels @ 020,013 */0, 9, 0x5B, 0x32, 0x00, 0x00, 0x00, 0x11,
		0x53, 0x5E, 0xAF,
		/* RLE: 005 Pixels @ 029,013 */5, 0xFF,
		/* ABS: 002 Pixels @ 002,014 */0, 2, 0xD6, 0x18,
		/* RLE: 025 Pixels @ 004,014 */25, 0x00,
		/* RLE: 001 Pixels @ 029,014 */1, 0xA4,
		/* RLE: 004 Pixels @ 030,014 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,015 */1, 0x7E,
		/* RLE: 026 Pixels @ 003,015 */26, 0x00,
		/* RLE: 001 Pixels @ 029,015 */1, 0x46,
		/* RLE: 004 Pixels @ 030,015 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,016 */1, 0x63,
		/* RLE: 026 Pixels @ 003,016 */26, 0x00,
		/* RLE: 001 Pixels @ 029,016 */1, 0x34,
		/* RLE: 004 Pixels @ 030,016 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,017 */1, 0x64,
		/* RLE: 026 Pixels @ 003,017 */26, 0x00,
		/* RLE: 001 Pixels @ 029,017 */1, 0x35,
		/* RLE: 004 Pixels @ 030,017 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,018 */1, 0x64,
		/* RLE: 026 Pixels @ 003,018 */26, 0x00,
		/* RLE: 001 Pixels @ 029,018 */1, 0x35,
		/* RLE: 004 Pixels @ 030,018 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,019 */1, 0x64,
		/* RLE: 026 Pixels @ 003,019 */26, 0x00,
		/* RLE: 001 Pixels @ 029,019 */1, 0x35,
		/* RLE: 004 Pixels @ 030,019 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,020 */1, 0x64,
		/* RLE: 026 Pixels @ 003,020 */26, 0x00,
		/* RLE: 001 Pixels @ 029,020 */1, 0x35,
		/* RLE: 004 Pixels @ 030,020 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,021 */1, 0x64,
		/* RLE: 026 Pixels @ 003,021 */26, 0x00,
		/* RLE: 001 Pixels @ 029,021 */1, 0x35,
		/* RLE: 004 Pixels @ 030,021 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,022 */1, 0x64,
		/* RLE: 026 Pixels @ 003,022 */26, 0x00,
		/* RLE: 001 Pixels @ 029,022 */1, 0x35,
		/* RLE: 004 Pixels @ 030,022 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,023 */1, 0x64,
		/* RLE: 026 Pixels @ 003,023 */26, 0x00,
		/* RLE: 001 Pixels @ 029,023 */1, 0x35,
		/* RLE: 004 Pixels @ 030,023 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,024 */1, 0x64,
		/* RLE: 026 Pixels @ 003,024 */26, 0x00,
		/* RLE: 001 Pixels @ 029,024 */1, 0x35,
		/* RLE: 004 Pixels @ 030,024 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,025 */1, 0x64,
		/* RLE: 026 Pixels @ 003,025 */26, 0x00,
		/* RLE: 001 Pixels @ 029,025 */1, 0x35,
		/* RLE: 004 Pixels @ 030,025 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,026 */1, 0x64,
		/* RLE: 026 Pixels @ 003,026 */26, 0x00,
		/* RLE: 001 Pixels @ 029,026 */1, 0x35,
		/* RLE: 004 Pixels @ 030,026 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,027 */1, 0x64,
		/* RLE: 026 Pixels @ 003,027 */26, 0x00,
		/* RLE: 001 Pixels @ 029,027 */1, 0x35,
		/* RLE: 004 Pixels @ 030,027 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,028 */1, 0x62,
		/* RLE: 026 Pixels @ 003,028 */26, 0x00,
		/* RLE: 001 Pixels @ 029,028 */1, 0x34,
		/* RLE: 004 Pixels @ 030,028 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,029 */1, 0x6E,
		/* RLE: 026 Pixels @ 003,029 */26, 0x00,
		/* RLE: 001 Pixels @ 029,029 */1, 0x3B,
		/* RLE: 004 Pixels @ 030,029 */4, 0xFF,
		/* RLE: 001 Pixels @ 002,030 */1, 0xB5,
		/* RLE: 026 Pixels @ 003,030 */26, 0x00,
		/* RLE: 001 Pixels @ 029,030 */1, 0x7B,
		/* RLE: 005 Pixels @ 030,030 */5, 0xFF,
		/* ABS: 003 Pixels @ 003,031 */0, 3, 0x94, 0x1F, 0x0D,
		/* RLE: 020 Pixels @ 006,031 */20, 0x0F,
		/* ABS: 006 Pixels @ 026,031 */0, 6, 0x0D, 0x15, 0x6B, 0xF3, 0xFF, 0xFF,
		0 };  // 416 bytes for 1024 pixels

GUI_CONST_STORAGE GUI_BITMAP bm100 = { 32, // xSize
		32, // ySize
		32, // BytesPerLine
		GUI_COMPRESS_RLE8, // BitsPerPixel
		(unsigned char *) _ac0,  // Pointer to picture data
		NULL,  // Pointer to palette
		GUI_DRAW_RLEALPHA };


/**
 * @brief  Startup
 * @param  None
 * @retval None
 */
void StartUpWindow(void) {
	WM_SetCallback(WM_GetDesktopWindowEx(0), BackGroundCallback);
	GUI_DrawBitmap(&bm100, 18, 14);

	osDelay(1000);
}
