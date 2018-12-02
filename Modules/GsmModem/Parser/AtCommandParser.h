/*
 * command.h
 *
 *  Created on: Apr 26, 2018
 *      Author: home
 */

#ifndef GSMMODEM_PARSER_ATCOMMANDPARSER_COMMAND_H_
#define GSMMODEM_PARSER_ATCOMMANDPARSER_COMMAND_H_

#include <Tokenizer/CommandTokenizer.h>
#include "stdint.h"
#include "cmsis_os.h"

/* Acknowledges execution of a Command
 * */
#define RESULT_NUMBER_OK					0
#define RESULT_CODE_OK						"OK"

/* A connection has been established; the DCE is moving from
 * Command state to online data state
 * */
#define RESULT_NUMBER_CONNECT				1
#define RESULT_CODE_CONNECT					"CONNECT"

/* The DCE has detected an incoming call signal from
 * network
 * */
#define RESULT_NUMBER_RING					2
#define RESULT_CODE_RING					"RING"

/* The connection has been terminated or the attempt to
 * establish a connection failed
 * */
#define RESULT_NUMBER_NOCARRIER				3
#define RESULT_CODE_NOCARRIER				"NO CARRIER"

/* Command not recognized, Command line maximum length
 * exceeded, parameter value invalid, or other problem with
 * processing the Command line
 * */
#define RESULT_NUMBER_ERROR					4
#define RESULT_CODE_ERROR					"ERROR"

/* No dial tone detected
 * */
#define RESULT_NUMBER_NODIALTONE			6
#define RESULT_CODE_NODIALTONE				"NO DIALTONE"

/* Engaged (busy) signal detected
 * */
#define RESULT_NUMBER_BUSY					7
#define RESULT_CODE_BUSY					"BUSY"
/* "@" (Wait for Quiet Answer) dial modifier was used, but
 * remote ringing followed by five seconds of silence was not
 * detected before expiration of the connection timer (S7)
 * */
#define RESULT_NUMBER_NOANSWER				8
#define RESULT_CODE_NOANSWER				"NO ANSWER"


typedef enum {
	final, intermediate, unsolicited,
} ResponseType_TypeDef;

typedef struct {
	const ResponseType_TypeDef type;
	char * code;
} ResponseResult_TypeDef;

extern const ResponseResult_TypeDef responseResultList[];

typedef enum {
	ResponseStatusOk,
	ResponseStatusError_Timeout,
	ResponseStatusError_ResultIsntThere,
	ResponseStatusError_BadFormat,
} ResponseStatus_TypeDef;

typedef struct {
	int32_t resultNumber;
	ResponseStatus_TypeDef status;
	CommandTokensList_TypeDef Tokens;
} Response_TypeDef;

Response_TypeDef ResponseParse(CommandTokenizer_TypeDef tokenizer,
		unsigned int length);
#endif /* GSMMODEM_PARSER_ATCOMMANDPARSER_COMMAND_H_ */
