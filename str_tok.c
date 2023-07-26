#include <stdio.h>
#include "main.h"
/**
 * str_tok - tokenizes a string
 * @str: pointer to the string
 * @delim: pointer to the delimiter
 *
 * Return: returns tokenized string.
 */
char *str_tok(char *str, char *delim)
{
	static char *last_token;
	char *token_start = str ? str : last_token;
	char *token_end;

	while (token_start != NULL && (*token_start == ' ' || *token_start == '\t'))
		token_start++;

	if (token_start == NULL || *token_start == '\0')
		return (NULL);

	token_end = token_start;
	while (*token_end != '\0' && *token_end != *delim)
		token_end++;

	if (*token_end == '\0')
	{
		last_token = NULL;
	}
	else
	{
		*token_end = '\0';
		last_token = token_end + 1;
	}
	return (token_start);
}
