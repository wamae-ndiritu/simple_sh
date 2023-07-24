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


void check_for_exit(custom_args *argv, env_var *path, char *lineptr, int exit_status)
{
	if (_strcmp(argv->argv[0], "exit") == 0)
	{
		handle_exit(argv, path, lineptr, exit_status);
	}
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
void handle_exit(custom_args *argv, env_var *path, char *lineptr, int exit_status)
{
	int status;
	int ac = 0, i = 0;
	char *msg;

	while (argv->argv[i] != NULL)
	{
		ac++;
		i++;
	}
	if (ac == 1)
	{
		free_resources(path, argv);
		free(lineptr);
		exit(exit_status);
	}
	else if (ac == 2)
	{
		status = _atoi(argv->argv[1]);
		if (status != 0)
		{
			free_resources(path, argv);
			free(lineptr);
			exit(status);
		}
		else
		{
			msg = "Illegal number to exit\n";
			write(STDOUT_FILENO, msg, _strlen(msg));
			free_resources(path, argv);
			free(lineptr);
			exit(128);
		}
	}
}
