#include "main.h"
#include <stdlib.h>
/**
 * _strcat -  concatenates two strings appending the src
 * string to the dest string, overwriting the terminating null
 * byte(\0) at the end of dest and then adds a terminating
 * null byte
 *
 * @dest: the string to be appended
 * @src: the string to concatenate
 * Return: dest
 */
char *_strcat(char *dest, const char *src)
{
	char *p1 = dest;

	while (*p1 != '\0')
	{
		p1++;
	}
	while (*src != '\0')
	{
		*p1++ = *src++;
	}
	*p1 = '\0';
	return (dest);
}
/**
 * _strlen - returns the length of a string
 * @s: pointer to the string
 *
 * Return: the length of the string
 */
int _strlen(const char *s)
{
	int len = 0;

	while (*s != '\0')
	{
		len++;
		s++;
	}
	return (len);
}
/**
 * _strcpy - Copies a string from src to dest
 *
 * @dest: Pointer to the destination buffer
 * @src: Pointer to the source string
 *
 * Return: Pointer to dest
 */
char *_strcpy(char *dest, const char *src)
{
	int i = 0;

	/* Copy the string from src to dest */
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}

	/* Append the null terminator */
	dest[i] = '\0';
	return (dest);
}
/**
 * _strdup - Duplicate a string.
 * @str: The string to be duplicated.
 *
 * Return: On success, a pointer to the newly allocated duplicated string.
 *         It returns NULL if insufficient memory was available.
 */
char *_strdup(const char *str)
{
	size_t len = _strlen(str) + 1;
	char *dup = malloc(len);

	if (dup != NULL)
	{
		_memcpy(dup, str, len);
	}

	return (dup);
}
/**
 * _memcpy - copies memory area
 * @dest: destination area of copied bytes
 * @src: source of bytes
 * @n: number of copied bytes
 * Return: dest
 */

char *_memcpy(char *dest, const char *src, unsigned int n)
{
	unsigned int t;

	for (t = 0; t < n && src[t] != '\0'; t++)
		dest[t] = src[t];
	for (; t < n; t++)
		dest[t] = '\0';

	return (dest);
}
