#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
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
	int status;

	filepath = argv->argv[0];
	execve_process = fork();
	if (execve_process == -1)
	{
		free_struct(argv, path);
		return (NULL);
	}
	else if (execve_process == 0)
	{
		if (execve(argv->argv[0], argv->argv, NULL) == -1)
		{
			print_err(argV[0]);
			free_struct(argv, path);
			exit(1);
		}
	}
	else
	{
		waitpid(execve_process, &status, 0);
		if (WIFEXITED(status) && WEXITSTATUS(status) != 0)
			*argV[2] = 1;

		free_struct(argv, path);
	}
	return (filepath);
}

/**
 * execute_file - Executes the file specified in lineptr.
 * @lineptr: Pointer to the string representing the file path.
 * @argV: Pointer to the command line arguments passed to main.
 *
 * Return: The file path on success, or NULL on failure.
 */
char *execute_file(char *lineptr, char *argV[])
{
	char *filepath = NULL;
	env_var *path;
	custom_args *argv;
	void (*result)(char **);

	path = get_env("PATH");
	if (path == NULL)
		return (NULL);
	argv = init_argv(lineptr, path);
	if (argv == NULL)
	{
		free_resources(path, argv);
		return (NULL);
	}
	if (_strcmp(argv->argv[0], "setenv") == 0)
	{
		char *res;

		res = _setenv(argv->argv[1], argv->argv[2], 1);
		if (res == NULL)
			return (NULL);
		free(res);
		free_resources(path, argv);
		return (filepath);
	}
	else if (_strcmp(argv->argv[0], "unsetenv") == 0)
	{
		int res;
		res = _unsetenv(argv->argv[1]);
		if (res != 0)
			perror("unsetenv");
		free_resources(path, argv);
		return (filepath);
	}
	result = get_callback(argv->argv[0]);
	if (result == NULL)
	{
		filepath = find_executable(path, argv->argv[0]);
		if (filepath == NULL)
		{
			print_err(argV[0]);
			free_resources(path, argv);
			return (NULL);
		}
		argv->argv[0] = filepath;
		filepath = execute_helper(argv, path, argV);
		if (filepath == NULL)
		{
			free_resources(path, argv);
			return (NULL);
		}
		return (filepath);
	}
	result(argv->argv);
	free_resources(path, argv);
	return (filepath);
}

/**
 * execute_command - Execute a single command and return the exit status.
 * @command: Pointer to the string representing the command.
 * @argV: Pointer to the command line arguments passed to main.
 *
 * Return: The exit status of the command.
 */
int execute_command(char *command, char *argV[]) 
{
	int exit_status = 0;
	char *commands_delimiters = "&&||";

	/* Tokenize the command using "&&" and "||" as delimiters */
	char *subcommand = str_tok(command, commands_delimiters);
	int logical_op = 0; /* 0: no operator, 1: &&, 2: || */

	while (subcommand != NULL) 
	{
		char *rest = subcommand + _strlen(subcommand) + 1;
		char *memory = NULL;

		if (*rest == '&' && *(rest + 1) == '&') 
		{
			logical_op = 1; /* && operator */
		} 
		else if (*rest == '|' && *(rest + 1) == '|') 
		{
			logical_op = 2; /* || operator */
		} 
		else 
		{
			logical_op = 0; /* no operator */
		}

		/* Execute the current subcommand */
		memory = execute_file(subcommand, argV);
		if (memory == NULL) 
		{
			exit_status = 1;
			if (logical_op == 1)
			{
				break;/*if operator && and comand fails, stop execution*/
			}
		} 
		else 
		{
			free(memory);
		}

		/* Check for logical operators */
		if (logical_op == 1 && exit_status == 0) 
		{ /* && operator */
			subcommand = str_tok(NULL, commands_delimiters);
		} 
		else if (logical_op == 2 && exit_status != 0) 
		{ /* || operator */
			subcommand = str_tok(NULL, commands_delimiters);
		} 
		else 
		{
			break; /* No logical operator or exit status doesn't match, break the loop. */
		}
	}

	return (exit_status);
}

/**
 * free_resources - Frees the allocated resources.
 * @path: Pointer to the env_var structure.
 * @argv: Pointer to the custom_args structure.
 */
void free_resources(env_var *path, custom_args *argv)
{
	free(path->key);
	free(path);
	free(argv->lineptr_cpy);
	free(argv->argv);
	free(argv);
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
	char *lineptr;/*memory;*/
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
			exit_status = execute_command(lineptr, argV);
		}
		free(lineptr);
	}
	return (0);
}

