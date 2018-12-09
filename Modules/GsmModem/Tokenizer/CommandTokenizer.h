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
	char * Separator;
	char * Footer;
} CommandTokenizer_TypeDef;

CommandTokensList_TypeDef CommandTokenizer_tokenize(
		CommandTokenizer_TypeDef Tokenizer, unsigned int *length);
void CommandTokenizer_FreeTokenList(CommandTokensList_TypeDef commandTokenList);

#endif /* GSMMODEM_TOKENIZER_COMMANDTOKENIZER_H_ */
