#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include <string.h>
#include "main.h"

/**
 * execute_helper - helper function to execute function
 * @argv: pointer to struct custom_args
 * @path: pointer to structure env_var
 * @argV: pointer to command line arguments passed to main
 *
 * Return: returns the filepath.
 */

char *execute_helper(custom_args *argv, env_var *path, char *argV[])
{
	char *filepath;
	pid_t execve_process;

	filepath = argv->argv[0];
	execve_process = fork();
	if (execve_process == -1)
	{
		free_struct(path, argv);
		return (NULL);
	}
	else if (execve_process == 0)
	{
		if (execve(argv->argv[0], argv->argv, NULL) == -1)
		{
			print_err(argV[0]);
			free_struct(path, argv);
			return (NULL);
		}
	}
	else
	{
		wait(NULL);
	}
	return (filepath);
}
/**
 * execute_file - Executes the file specified in lineptr.
 * @lineptr: Pointer to the string representing the file path.
 * @argV: Pointer to the command line arguments passed to main.
 * @exit_status: stores the exit status of a process
 *
 * Return: The file path on success, or NULL on failure.
 */
char *execute_file(char *lineptr, char *argV[], int exit_status)
{
	char *filepath = NULL;
	char **lines;
	env_var *path;
	custom_args *argv;
	void (*result)(char **);
	char *message;

	lines = handle_separator(lineptr);
	while (*lines != NULL)
	{
		argv = init_argv(*lines);
		if (argv == NULL)
		{
			free(path->key);
			free(path);
			return (NULL);
		}
		check_for_exit(argv, lineptr, exit_status);
		result = get_callback(argv->argv[0]);
		if (result == NULL)
		{
			message = execute_set_env(argv->argv);
			if (message == NULL)
			{
				free_struct(path, argv);
				return (NULL);
			}
			else if (_strcmp(message, "Not setenv or unsetenv") == 0)
			{
				path = get_env("PATH");
				filepath = find_executable(path, argv->argv[0]);
				if (filepath == NULL)
				{
					exit_status = 127;
					print_err(argV[0]);
					free_custom_args(argv);
					lines++;
					continue;
				}
				argv->argv[0] = filepath;
				filepath = execute_helper(argv, path, argV);
				if (filepath == NULL)
				{
					free_struct(path, argv);
					return (NULL);
				}
			}
			lines++;
			continue;
		}
		result(argv->argv);
		free_struct(path, argv);
		lines++;
		continue;
	}
	return (filepath);
}

/**
 * main - main entry point of the shell program
 * @ac: count of command line arguments
 * @argV: pointer to an array of arguments passed
 *
 * Return: Always 0.
 */

int main(int ac, char *argV[])
{
	char *lineptr = NULL, *memory;
	size_t n = 0;
	ssize_t num_char_read;
	int exit_status = 0;
	int interactive_mode = isatty(STDIN_FILENO);

	signal(SIGINT, signal_handler);
	while (1)
	{
		lineptr = NULL;
		if (interactive_mode && ac == 1)
			write(STDOUT_FILENO, "$ ", 2);
		num_char_read = get_line(&lineptr, &n, stdin);
		if (num_char_read == -1)
		{
			if (interactive_mode)
				write(STDOUT_FILENO, "\n", 1);
			free(lineptr);
			exit(exit_status);
		}
		else if (num_char_read == 1)
		{
			free(lineptr);
			continue;
		}
		else
		{
			lineptr[num_char_read - 1] = '\0';
			memory = execute_file(lineptr, argV, exit_status);
			if (memory == NULL)
			{
				exit_status = 1;
				free(lineptr);
				continue;
			}
			else if (memory != NULL)
				exit_status = 0;
		}
		free(memory);
		free(lineptr);
	}
	return (0);
}
