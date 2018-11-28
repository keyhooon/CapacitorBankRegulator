/*
 * command.c
 *
 *  Created on: Apr 26, 2018
 *      Author: home
 */
#include <Parser/AtCommandParser.h>
#include "cmsis_os.h"
const ResponseResult_TypeDef responseResultList[9] = {
		{ final, RESULT_CODE_OK },/* 0 - OK */
		{ intermediate, RESULT_CODE_CONNECT },/* 1 - CONNECT */
		{ unsolicited, RESULT_CODE_RING },/* 2 - RING */
		{ unsolicited, RESULT_CODE_NOCARRIER },/* 3 - NOCARRIER */
		{ final, RESULT_CODE_ERROR },/* 4 - ERROR*/
		{ final, 0 },/*5 - RESERVED*/
		{ unsolicited, RESULT_CODE_NODIALTONE },/*6 - DIALTONE*/
		{ unsolicited, RESULT_CODE_BUSY },/*7 - BUSY*/
		{ unsolicited, RESULT_CODE_NOANSWER }/*8 - NOANSWER*/
};

Response_TypeDef ResponseParse(CommandTokenizer_TypeDef tokenizer,
		unsigned int length) {
	CommandTokensList_TypeDef tokensList = CommandTokenizer_tokenize(tokenizer,
			length);
	Response_TypeDef result = { 0, ResponseStatusOk, tokensList };
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

