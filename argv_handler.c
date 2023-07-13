#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include "main.h"
/**
 * count_args - Counts the number of arguments in a line
 * @lineptr: The input line to process
 *
 * Return: The number of arguments
 */
int count_args(char *lineptr)
{
	int ac = 0;
	char *token_arg;

	token_arg = str_tok(lineptr, " \n");
	while (token_arg != NULL)
	{
		token_arg = str_tok(NULL, " \n");
		ac++;
	}

	return (ac);
}
/**
 * init_argv - Initializes the arguments array and handles callbacks
 * @lineptr: The input line to process
 * @path: path with mem
 *
 * Return: A pointer to the custom_args struct
 */
custom_args *init_argv(char *lineptr, env_var *path)
{
	void (*result)(char **);
	char *token_arg, *lineptr_cpy = NULL;
	char **argv; /**env = environ;*/
	int ac = 0, i = 0;
	custom_args *frees;

	frees = malloc(sizeof(custom_args));
	if (frees == NULL)
		return (NULL);

	lineptr_cpy = _strdup(lineptr);
	ac = count_args(lineptr);
	argv = malloc(sizeof(char *) * (ac + 1));
	if (argv == NULL)
	{
		free(lineptr_cpy);
		free(frees);
		return (NULL);
	}
	token_arg = str_tok(lineptr_cpy, " \n");
	while (token_arg != NULL)
	{
		argv[i] = token_arg;
		token_arg = str_tok(NULL, " \n");
		i++;
	}
	argv[i] = NULL;
	if (argv[0] != NULL && _strcmp(argv[0], "exit") == 0)
	{
		free(frees);
		handle_exit(argv, lineptr, lineptr_cpy, path);
	}

	result = get_callback(argv[0]);
	if (result != NULL)
		result(argv);
	frees->lineptr_cpy = lineptr_cpy;
	frees->argv = argv;
	return (frees);
}

