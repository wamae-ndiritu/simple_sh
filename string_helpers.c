#include <stdio.h>
#include "main.h"

/**
 * removeLeadingSpaces - removes leading whitespaces from a string
 * @str: pointer to string with leading spaces
 * @str1: a copied string with no leading spaces
 * Return: Returns Nothing.
 */

void removeLeadingSpaces(char *str, char *str1)
{
	int index = 0, i = 0, j;

	/* Iterate string until last leading space */
	while (*str == ' '  || *str == '\t' || *str == '\n')
	{
		index++;
	}
	
	/* Copy the content of str to str1 */
	for (j = index; str[j] != '\0'; j++)
	{
		str1[i] = str[j];
		i++;
	}
	str1[i] = '\0';
}
