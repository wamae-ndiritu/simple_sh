#include <stdlib.h>
#include <unistd.h>
#include "main.h"
/**
 * _setenv - initializes a new environment variable, or modify existing one
 * @name: pointer the variable whose value is to be set/updated
 * @value: pointer to the value to be set/updated
 * @overwrite: interger condition to overwrite existing variable
 * Return: 0 onsuccess, -1 on failure
 */
char *_setenv(const char *name, const char *value, int overwrite)
{
	char *key, *val;
	char **env = environ;
	char *new_variable = NULL;
	int len, i = 0;

	key = _strdup(name);
	val = _strdup(value);
	len = _strlen(key) + _strlen(val) + 2;
	new_variable = malloc(len * sizeof(char));
	_strcpy(new_variable, key);
	_strcat(new_variable, "=");
	_strcat(new_variable, val);

	if (new_variable == NULL)
		return (NULL);
	while(env[i] != NULL)
	{
		char *delim = "=\n";
		char *token;
		char *env_cpy;
		
		env_cpy = _strdup(env[i]);
		token = str_tok(env_cpy, delim);
		if (_strcmp(token, key) == 0 && overwrite)
		{
			printf("--------Variable exist, we are updating--------\n");
			env[i] = new_variable;
			free(env_cpy);
			env_cpy = NULL;
			free(key);
			free(val);
			return (new_variable);
		}
		free(env_cpy);
		env_cpy = NULL;
		i++;
	}
	printf("---------------Variable does not exist, we are adding it--------\n");
	env[i] = new_variable;
	env[i + 1] = NULL;
	free(key);
	free(val);
	return (new_variable);
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
