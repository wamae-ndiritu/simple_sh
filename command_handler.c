#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include "main.h"


/**
 * free_exit_mem - frees mem on exit
 * @argv: pointer to argv
 * @lineptr: pointer to mem lineptr
 * @lineptr_cpy: lineptr copy
 * @path: path with mem
 *
 * Return: Nothing.
 */

void free_exit_mem(char **argv, char *lineptr, char *lineptr_cpy, env_var *path)
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
