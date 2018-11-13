/*
 * command.c
 *
 *  Created on: Apr 26, 2018
 *      Author: home
 */
#include <Parser/AtCommandParser.h>
#include "cmsis_os.h"

Response_TypeDef ResponseParse(CommandTokenizer_TypeDef tokenizer,
		unsigned int length) {
	CommandTokensList_TypeDef tokensList = CommandTokenizer_tokenize(tokenizer,
			length);
	Response_TypeDef result = { -1, ResponseStatusOk, tokensList };
	if (tokensList.ResultIndex != -1) {
		register char* string = *(tokensList.Items + tokensList.ResultIndex);
		register unsigned int digit;
		while (*string != 0) {
			digit = *string++ - '0';
			if (digit < 0 || digit > 9) {
				result.resultNumber = -1;
				result.status = ResponseStatusError_BadFormat;
				break;
			} else
				result.resultNumber = result.resultNumber * 10 + digit;
		}
	} else {
		result.resultNumber = -1;
		result.status = ResponseStatusError_ResultIsntThere;
	}
	return result;
}

