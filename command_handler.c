#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"

/**
 * execute_set_env - Executes the "setenv" and "unsetenv" commands.
 * @argv: Pointer to the array of command-line arguments.
 *
 * Return: A message indicating the result of the command execution.
 */
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
 * check_for_exit - Checks if the command is "exit" and handles the exit.
 * @argv: Pointer to the custom_args structure.
 * @path: Pointer to the env_var structure.
 * @lineptr: Pointer to the line pointer.
 * @exit_status: The exit status of the shell.
 *
 * Return: Nothing.
 */
void check_for_exit(custom_args *argv, env_var *path, char *lineptr,
		int exit_status)
{
	if (_strcmp(argv->argv[0], "exit") == 0)
	{
		handle_exit(argv, path, lineptr, exit_status);
	}
}

/**
 * handle_exit - Handles the "exit" command to exit the shell.
 * @argv: Pointer to the custom_args structure.
 * @path: Pointer to the env_var structure.
 * @lineptr: Pointer to the line pointer.
 * @exit_status: The exit status of the shell.
 *
 * Return: Nothing.
 */
void handle_exit(custom_args *argv, env_var *path, char *lineptr,
		int exit_status)
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

