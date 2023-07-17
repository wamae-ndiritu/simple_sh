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
			key = NULL;
			free(val);
			val = NULL;
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
	key = NULL;
	free(val);
	val = NULL;
	return (new_variable);
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
			free(env[i]);
			while (env[i + 1] != NULL)
			{
				env[i] = env[i + 1];
				i++;
			}
			env[i] = NULL;
			free(env_cpy);
			free(variable);
			return (0);
		}
		free(env_cpy);
		free(variable);
		i++;
	}
	return (-1);
}
