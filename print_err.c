#include <stdio.h>
#include <stdlib.h>
#include "main.h"

/**
 * print_err - prints error message to stdout
 * @program_name: pointer to the program  being executed
 * Return: Nothing.
 */

void print_err(char *program_name)
{
	char err_mess[256];

	_strcpy(err_mess, program_name);
	perror(err_mess);
}
