#include <stdlib.h>
#include <unistd.h>
#include "main.h"
/**
 * _setenv - initializes a new environment variable, or modify existing one
 * @args: argument passed
 * Return: 0 onsuccess, -1 on failure
 */
void _setenv(char **args)
{
	int result;
	char *variable = args[0];
	char *value = args[1];

	if (args[0] == NULL || args[1] == NULL)
	{
		write(STDERR_FILENO, "Missing arguments for setenv\n", 28);
		return;
	}
	/*set the env var*/
	result = setenv(variable, value, 1);
	/*check if operation was successful*/
	if (result == -1)
	{
		/*print an error message*/
		write(STDERR_FILENO, "Error setting environment variable: ", 27);
		write(STDERR_FILENO, variable, _strlen(variable));
		write(STDERR_FILENO, "\n", 1);
	}
}
/**
 * _unsetenv - remove an env variable
 * @args: argument passed
 * Return: 0 on success -1 on failure
 */
void _unsetenv(char **args)
{
	int result;
	char *variable = args[0];

	/* Unset the environment variable. */
	result = unsetenv(variable);
	/* Check if the operation was successful. */
	if (result == -1)
	{
		/* Print an error message. */
		write(STDERR_FILENO, "Error unsetting environment variable: ", 29);
		write(STDERR_FILENO, variable, _strlen(variable));
		write(STDERR_FILENO, "\n", 1);
	}
}
