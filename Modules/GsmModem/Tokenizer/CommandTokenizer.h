/*
 * CommandTokenizer.h
 *
 *  Created on: Nov 10, 2018
 *      Author: HP
 */

#ifndef GSMMODEM_TOKENIZER_COMMANDTOKENIZER_H_
#define GSMMODEM_TOKENIZER_COMMANDTOKENIZER_H_

#include "bufferTokenizer.h"
#include "bufferStream.h"

typedef struct {
	char ** Items;
	int ResultIndex;
	int IndexNeedToBeReleased;
} CommandTokensList_TypeDef;

typedef struct {
	BufferStream_TypeDef * bufferStream;
	char * Footer;
	unsigned int FooterCount;
	char * Separator;
	unsigned int SeparatorCount;
} CommandTokenizer_TypeDef;

CommandTokenizer_TypeDef * CommandTokenizer_Init(BufferStream_TypeDef *bufferStream,
		const char * separator,
		const char * footer);

void CommandTokenizer_DeInit(CommandTokenizer_TypeDef * tokenizer);
CommandTokensList_TypeDef CommandTokenizer_tokenize(
		CommandTokenizer_TypeDef Tokenizer, unsigned int length);
void CommandTokenizer_FreeTokenList(CommandTokensList_TypeDef commandTokenList);

#endif /* GSMMODEM_TOKENIZER_COMMANDTOKENIZER_H_ */
