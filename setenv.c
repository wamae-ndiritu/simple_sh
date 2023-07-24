#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * _setenv - initializes a new environment variable, or modify existing one
 * @name: pointer the variable whose value is to be set/updated
 * @value: pointer to the value to be set/updated
 * @overwrite: interger condition to overwrite existing variable
 * @env: pointer to the environ (external variable)
 * Return: 0 onsuccess, -1 on failure
 */
int _setenv(const char *name, const char *value, int overwrite)
{
	int result;

	result = setenv(name, value, overwrite);
	if (result != 0)
		perror("setenv");
	return (result);
}

/**
 * _unsetenv - remove an env variable
 * @name: pointer to the variable to unset
 * Return: 0 on success -1 on failure
 */

int _unsetenv(const char *name)
{
	char *variable;
	char **env = environ;
	int i = 0;

	variable = _strdup(name);
	while (env[i] != NULL)
	{
		char *delim = "=\n";
		char *token;
		char *env_cpy = _strdup(env[i]);

		token = str_tok(env_cpy, delim);
		if (token != NULL && _strcmp(token, variable) == 0)
		{
			while (env[i + 1] != NULL)
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
			free(env_cpy);
			return (0);
		}
		free(env_cpy);
		free(variable);
		i++;
	}
	return (-1);
}
