#include <stdio.h>
#include "main.h"

/**
 * str_tok - Breaks a string into a sequence of tokens.
 * @str: The input string to be tokenized.
 * @delim: The set of delimiter characters used to determine the tokens.
 *
 * Return: If a token is found, a pointer to the beginning of the token is
 *         returned; otherwise, NULL is returned to indicate no more tokens.
 */
char *str_tok(char *str, const char *delim)
{
    static char *last_token = NULL;
    char *token_start = str ? str : last_token;
    char *token_end;

    if (token_start == NULL)
        return (NULL);

    /* Skip leading delimiters*/
    while (*token_start && _strchr(delim, *token_start))
        token_start++;

    /* If we've reached the end or have consecutive delimiters, return NULL.*/
    if (*token_start == '\0')
        return (NULL);

    token_end = token_start;
    while (*token_end && !_strchr(delim, *token_end))
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
