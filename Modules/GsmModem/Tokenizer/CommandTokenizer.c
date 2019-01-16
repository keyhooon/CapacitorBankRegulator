/*
 * CommandTokenizer.c
 *
 *  Created on: Nov 10, 2018
 *      Author: HP
 */

#include "Tokenizer/CommandTokenizer.h"

CommandTokensList_TypeDef CommandTokenizer_tokenize(
		CommandTokenizer_TypeDef tokenizer, unsigned int *commandLength) {
	CommandTokensList_TypeDef result = { 0, -1, -1 };
	char * TokenizedItems[10];
	bufToken_TypeDef currentBuffToken;
	int tokenCount = 0;

	currentBuffToken = BufTok(tokenizer.bufferStream, *commandLength,
			tokenizer.Separator);
	while (currentBuffToken.item != 0) {
		if (currentBuffToken.needTobeRealesed)
			result.IndexNeedToBeReleased = tokenCount;

		TokenizedItems[tokenCount++] = currentBuffToken.item;
		*commandLength -= currentBuffToken.length + strlen(tokenizer.Separator);
		if (strlen(currentBuffToken.item) == 1
				&& isdigit(*currentBuffToken.item))
		{
			result.ResultIndex = tokenCount - 1;
			break;
		}
		currentBuffToken = BufTok(tokenizer.bufferStream, *commandLength,
				tokenizer.Separator);
	}
	if (tokenCount) {
		TokenizedItems[tokenCount++] = 0;
		result.Items = pvPortMalloc(sizeof(char *) * tokenCount);
		memcpy(result.Items, TokenizedItems, sizeof(char *) * tokenCount);
	}
	return result;
}
void CommandTokenizer_FreeTokenList(CommandTokensList_TypeDef commandTokenList) {
	if (commandTokenList.IndexNeedToBeReleased != -1)
	{
		vPortFree(
				commandTokenList.Items[commandTokenList.IndexNeedToBeReleased]);
		commandTokenList.IndexNeedToBeReleased = -1;
	}

	if (commandTokenList.Items != (void*) 0)
	{
		vPortFree(commandTokenList.Items);
		commandTokenList.Items = 0;
	}
}
void CommandTokenizer_RemoveTokenFromList(
		CommandTokensList_TypeDef commandTokenList, int index) {
	if (commandTokenList.IndexNeedToBeReleased > index)
		commandTokenList.IndexNeedToBeReleased--;
	else if (commandTokenList.IndexNeedToBeReleased == index) {
		vPortFree(commandTokenList.Items[index]);
		commandTokenList.IndexNeedToBeReleased = -1;
	}
	if (commandTokenList.ResultIndex > index)
		commandTokenList.ResultIndex--;
	for (int j = index; *(commandTokenList.Items + j) != 0; j++)
		commandTokenList.Items[j] = commandTokenList.Items[j + 1];
}
