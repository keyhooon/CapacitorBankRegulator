/*
 * AtTokenizer.h
 *
 *  Created on: Jul 5, 2018
 *      Author: HP
 */

#ifndef GSMMODEM_TOKENIZER__BUFFERTOKENIZER_H_
#define GSMMODEM_TOKENIZER__BUFFERTOKENIZER_H_

#include "bufferStream.h"

typedef struct {
	char * item;
	int length;
	int needTobeRealesed;
} bufToken_TypeDef;


bufToken_TypeDef BufTok(BufferStream_TypeDef * bufferStream, int Length,
		char * delimiter);

int CheckPattern(BufferStream_TypeDef * bufferStream, char * pattern);

#endif /* GSMMODEM_TOKENIZER__BUFFERTOKENIZER_H_ */
