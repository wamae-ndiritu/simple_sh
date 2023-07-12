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
 * @stream: pointer to the stream, stdin stream
 *
 * Return: returns the length of the line read, or
 *	-1 on error
 */
ssize_t get_line(char **lineptr, size_t *n, FILE *stream)
{
	static char *buf;
	ssize_t bytes_read;
	size_t pos = 0;
	size_t size, i;
	int realloc_res;

	if (*lineptr == NULL)
	{
		*lineptr = malloc(BUF_SIZE);
		if (*lineptr == NULL)
			return (-1);
		*n = BUF_SIZE;
	}
	buf = *lineptr;
	size = *n;
	bytes_read = read(fileno(stream), buf + pos, size - pos);
	if (bytes_read == -1)
		return (-1);
	else if (bytes_read == 0)
		return (-1);
	pos += bytes_read;
	realloc_res = realloc_buf(lineptr, n, pos); /* realloc buf if full */
	if (realloc_res == -1)
		return (-1);
	for (i = pos - bytes_read; i < pos; i++)
	{
		if (buf[i] == '\n' || buf[i] == ' ' || buf[i] == '\t')
		{
			buf[i] = '\0';  /*Null-terminate the line*/
			return (i + 1);     /*line_len including \n*/
		}
	}

	if (pos > 0)
	{
		buf[pos] = '\0';
		return (pos);
	}
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

