#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

#define BUF_SIZE 1024

/**
 * realloc_buf - reallocates memory buffer
 * @lineptr: pointer to pointer to the read line
 * @n: pointer to size of line read
 * @pos: position of newline
 *
 * Return: returns 0 on success, -1 of error.
 */

int realloc_buf(char **lineptr, size_t *n, size_t pos)
{
	size_t size = *n;

	if (pos >= size)
	{
		char *new_buf;

		size *= 2;  /*Double the buffer size */
		new_buf = _realloc(*lineptr, size);
		if (new_buf == NULL)
			return (-1);
		*lineptr = new_buf;
		*n = size;
	}
	return (0);
}

/**
 * get_line - reads user input
 * @lineptr: pointer to pointer to the buffer to be read
 * @n: pointer to the size of buffer to be read
 * @fd: pointer to the stream, stdin stream
 *
 * Return: returns the length of the line read, or
 *	-1 on error
 */
ssize_t get_line(char **lineptr, size_t *n, int fd)
{
	static char buf[BUF_SIZE];
	size_t pos;
	static size_t buf_pos = 0;
	static size_t bytes_in_buf = 0;
	int c;

	if (*lineptr == NULL || *n == 0)
	{
		*lineptr = malloc(BUF_SIZE);
		if (*lineptr == NULL)
			return (-1);
		*n = BUF_SIZE;
	}

	pos = 0;
	while (1)
	{
		if (buf_pos == bytes_in_buf)
		{
			bytes_in_buf = read(fd, buf, BUF_SIZE);
			if (bytes_in_buf <= 0)
			{
				/* no characters were read */
				free(*lineptr);
				*lineptr = NULL;
				return (-1);
			}
			buf_pos = 0;
		}

		/* copy characters from the buffer to lineptr */
		c = buf[buf_pos++];
		(*lineptr)[pos++] = (char)c;

		if (c == '\n')
		{
			(*lineptr)[pos -1] = '\0'; /* null-terminate line */
			return (pos - 1); /* return no of characters read excluding null terminator */
		}

		/* Resize the buffer if necessary */

		if (pos >= *n - 1)
		{
			char *new_lineptr;

			*n *= 2;
			new_lineptr = realloc(*lineptr, *n);
			if (new_lineptr == NULL)
				return (-1);
			*lineptr = new_lineptr;
		}
	}

	/* never reached */
	return (-1);
}
/**
 * _realloc - Custom realloc function
 * @ptr: Pointer to the memory block to be reallocated
 * @size: Size of the new memory block
 *
 * Return: Pointer to the newly allocated memory block, or NULL on failure
 */
void *_realloc(void *ptr, size_t size)
{
	void *new_ptr;
	size_t *old_size_ptr, copy_size, old_size;

	if (size == 0)
	{
		free(ptr);
		return (NULL);
	}

	if (ptr == NULL)
		return (malloc(size));

	new_ptr = malloc(size);
	if (new_ptr != NULL)
	{
		old_size_ptr = (size_t *)ptr - 1;
		old_size = *old_size_ptr;
		copy_size = old_size < size ? old_size : size;
		_memcpy(new_ptr, ptr, copy_size);
		free(old_size_ptr);
	}

	return (new_ptr);
}

