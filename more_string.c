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

/**
 * _strchr - Locate the first occurrence of a character in a string.
 * @s: The input string to search in.
 * @c: The character to search for.
 *
 * Return: If the character is found, a pointer to the first occurrence is
 *         returned; otherwise, NULL is returned.
 */
char *_strchr(const char *s, int c)
{
	while (*s != '\0')
	{
		if (*s == c)
		{
			return (char *)s;
		}
		s++;
	}

	/* Check if the terminating null character matches the character we are looking for */
	if (c == '\0')
	{
		return (char *)s;
	}

	return NULL;
}
