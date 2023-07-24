#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"


char *execute_set_env(char **argv)
{
	int result;
	char *command = argv[0];
	int ac = get_argument_count(argv);
	char *message = "Not setenv or unsetenv";

	if (_strcmp(command, "setenv") == 0)
	{
		if (ac != 3)
			return (NULL);
		result = _setenv(argv[1], argv[2], 1);
		if (result != 0)
			return (NULL);
		return (*argv);

	}
	else if (_strcmp(command, "unsetenv") == 0)
	{
		if (ac != 2)
			return (NULL);
		result = _unsetenv(argv[1]);
		if (result != 0)
			return (NULL);
		return (*argv);
	}
	return (message);
}
/**
 * free_exit_mem - frees mem on exit
 * @argv: pointer to argv
 * @lineptr: pointer to mem lineptr
 * @lineptr_cpy: lineptr copy
 * @path: path with mem
 *
 * Return: Nothing.
 */

void free_exit_mem(char **argv, char *lineptr,
		char *lineptr_cpy, env_var *path)
{
	free(argv);
	free(path->key);
	path->key = NULL;
	free(path);
	free(lineptr_cpy);
	lineptr_cpy = NULL;
	free(lineptr);
	lineptr = NULL;
}

/**
 * handle_exit - handle the case to exit shell
 * @argv: double pointer to arguments
 * @lineptr: line pointer
 * @lineptr_cpy: line pointer copy
 * @path: environmentvariable
 *
 * Return: Nothing.
 */
void handle_exit(char **argv, char *lineptr, char *lineptr_cpy, env_var *path)
{
	int status;
	int ac = 0, i = 0;
	char *msg;

	while (argv[i] != NULL)
	{
		ac++;
		i++;
	}
	if (ac == 1)
	{
		free_exit_mem(argv, lineptr, lineptr_cpy, path);
		exit(EXIT_SUCCESS);
	}
	else if (ac == 2)
	{
		status = _atoi(argv[1]);
		if (status != 0)
		{
			free_exit_mem(argv, lineptr, lineptr_cpy, path);
			exit(status);
		}
		else
		{
			msg = "Illegal argument to exit\n";
			write(STDOUT_FILENO, msg, _strlen(msg));
			free_exit_mem(argv, lineptr, lineptr_cpy, path);
			exit(2);
		}
	}
}
