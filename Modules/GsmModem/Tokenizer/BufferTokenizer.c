/*
 * Tokenizer.c
 *
 *  Created on: Jul 5, 2018
 *      Author: HP
 */

#include <Tokenizer/BufferTokenizer.h>
#include "string.h"

// maxLength variable gonna out from static attribute, and testing for error,
// we assume idle occure in end of the packet, if in packetizing any byte remain
// we raise error, if error occure, we must change code to maxLength parameter,
// static.
bufToken_TypeDef BufTok(BufferStream_TypeDef * bufferStream, int Length,
		char * delimiter) {
	bufToken_TypeDef tok = { 0, 0, 0 };
	int currentIndex = bufferStream->tail;

	int delimiterFoundCount = 0;
	int delimiterLength = strlen(delimiter);
	for (int i = 0; i < Length; i++) {
		if (*(bufferStream->buffer + currentIndex) == *(delimiter + delimiterFoundCount))
			delimiterFoundCount++;
		else if (*(bufferStream->buffer + currentIndex) == *(delimiter))
			delimiterFoundCount = 1;
		else
			delimiterFoundCount = 0;
		if (delimiterLength == delimiterFoundCount) {
			*(bufferStream->buffer + currentIndex - delimiterLength + 1) = 0;
			int tokLength = currentIndex - bufferStream->tail - delimiterLength
					+ 1;
			if (tokLength < 0) {
				tokLength += bufferStream->length;
				tok.needTobeRealesed =  1;
				tok.item = pvPortMalloc(tokLength);
				int e = bufferStream->length - bufferStream->tail;
				memcpy(tok.item, bufferStream->buffer + bufferStream->tail, e);
				memcpy(tok.item + e, bufferStream->buffer, tokLength - e);
			} else
				tok.item = bufferStream->buffer + bufferStream->tail;
			bufferStream->tail = currentIndex + 1;
			tok.length = tokLength;
			break;
		}
		if (currentIndex ++==bufferStream->length)
			currentIndex = 0;
	}

	return tok;
}
int CheckPattern(BufferStream_TypeDef * bufferStream, char * pattern) {
	int delimiterFoundCount = 0;
	int index = 0;
	int delimiterLength;
	for (delimiterLength = strlen(pattern);
			delimiterLength > 0
					&& *(bufferStream->buffer + index + bufferStream->tail)
							== *(pattern + index);
			delimiterLength--) {
		delimiterFoundCount++;
		*(bufferStream->buffer + index) = 0;
	}
	if (delimiterLength == 0) {
		bufferStream->tail += delimiterFoundCount;
		return 1;
	}
	return 0;
}

