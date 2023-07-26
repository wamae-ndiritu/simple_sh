#include "main.h"
/**
 * _strcmp - compares two strings
 * @s1: string one
 * @s2: string two
 * Return: 0 if s1 and s2 are equal,
 * another number if not
 */
int _strcmp(char *s1, char *s2)
{
	while (*s1 && (*s1 == *s2))
	{
		s1++;
		s2++;
	}
	return (*(const unsigned char *)s1 - *(const unsigned char *)s2);

}
