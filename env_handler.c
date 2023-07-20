#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include "main.h"

/**
 * print_env - prints the environment variable
 * @env: holds the environ variable
 *
 * Return: Nothing.
 */

void print_env(char **env)
{
	int variable_len;

	env = environ;
	/* make sure env not null */
	if (env == NULL)
	{
		printf("Found NULL env\n");
		return;
	}
	while (*env != NULL)
	{
		if (*env != NULL)
		{
			variable_len = _strlen(*env) + 1;
			write(STDOUT_FILENO, *env, variable_len);
			write(STDOUT_FILENO, "\n", 1);
			env++;
		}
	}
}
/**
 * get_env - retrieves the value of an environment variable
 * @variable: the name of the environment variable
 * Return: environment variable
 */
env_var *get_env(char *variable)
{
	char **env = environ;
	char *token;
	char *delim = "=\n";
	char *env_cpy = NULL;
	env_var *envp;

	envp = malloc(sizeof(env_var));
	if (envp == NULL)
		return (NULL);
	while (*env != NULL)
	{
		env_cpy = _strdup(*env);
		token = str_tok(env_cpy, delim);
		if (_strcmp(token, variable) == 0)
		{
			token = str_tok(NULL, delim);
			envp->key = env_cpy;
			envp->value = token;
			return (envp);
		}
		free(env_cpy);
		env_cpy = NULL;
		env++;
	}

	free(envp);
	return (NULL);
}
