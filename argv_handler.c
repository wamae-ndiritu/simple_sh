#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <signal.h>
#include <sys/wait.h>
#include "main.h"

/**
 * get_argument_count - counts the number of arguments in the array argv
 * @argv: pointer to an array of strings
 * Return: Return argument count
 */

int get_argument_count(char **argv)
{
	int ac = 0;

	while (*argv != NULL)
	{
		argv++;
		ac++;
	}
	return (ac);
}

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

custom_args *init_multiple_commands(char *lineptr)
{
	char **lines;
	custom_args *argv = NULL;

	lines = handle_separator(lineptr);
	if (lines == NULL)
		return (NULL);

	while (*lines != NULL)
	{
		argv = init_argv(*lines);
		if (argv == NULL)
		{
			free(lines);
			free(argv->lineptr_cpy);
			free(argv->argv);
			free(argv);
			return (NULL);
		}
		return (argv);
	}
	return (argv);
}

/**
 * handle_separator - helper function to execute multiple commands separeted by ";"
 * @lineptr: pointer to the string of command entered from the terminal
 *
 * Return: Returns pointer to an array of multiple commands.
 */

char **handle_separator(char *lineptr)
{
	char *line, *lineptr_cpy = NULL;
	char **lines;
	int lines_count = 0, i = 0;

	lineptr_cpy = _strdup(lineptr);
	line = str_tok(lineptr_cpy, ";\n");
	while (line != NULL)
	{
		lines_count++;
		line = str_tok(NULL, ";\n");
	}

	lines = malloc(lines_count * sizeof(char *));
	if (lines == NULL)
	{
		free(lineptr_cpy);
		return (NULL);
	}

	line = str_tok(lineptr, ";\n");
	while (line != NULL)
	{
		lines[i] = line;
		line = str_tok(NULL, ";\n");
		i++;
	}

	lines[i] = NULL;

	free(lineptr_cpy);
	return (lines);
}
/**
 * init_argv - Initializes the arguments array and handles callbacks
 * @lineptr: The input line to process
 *
 * Return: A pointer to the custom_args struct
 */
custom_args *init_argv(char *lineptr)
{
	char *token_arg, *lineptr_cpy = NULL;
	char **argv;
	int ac, i = 0;
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
	frees->lineptr_cpy = lineptr_cpy;
	frees->argv = argv;
	return (frees);
}

