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
char *_setenv(const char *name, const char *value, int overwrite)
{
	char *key = NULL, *val = NULL;
	char **env, **new_env;
	char *new_variable = NULL;
	int len, var_count = 0, i, j;

	env = get_environ();
	key = _strdup(name);
	val = _strdup(value);
	len = _strlen(key) + _strlen(val) + 2;
	new_variable = malloc(len * sizeof(char));
	if (new_variable == NULL)
	{
		free(key);
		free(val);
		return (NULL);
	}
	_strcpy(new_variable, key);
	_strcat(new_variable, "=");
	_strcat(new_variable, val);
	free(val);
	while(*env != NULL)
	{
		char *delim = "=\n";
		char *token;
		char *env_cpy;
		
		env_cpy = _strdup(*env);
		token = str_tok(env_cpy, delim);
		if (token != NULL && _strcmp(token, key) == 0 && overwrite)
		{
			if (overwrite)
			{
			printf("--------Variable exist, we are updating--------\n");
			*env = new_variable;
			free(env_cpy);
			env_cpy = NULL;
			free(key);
			return (new_variable);
			}
			else
			{
				/* variable exist but not allowed to overwrite */
				free(key);
				free(new_variable);
				free(env_cpy);
				return (*env);
			}
		}
		free(env_cpy);
		env_cpy = NULL;
		env++;
	}
	printf("---------------Variable does not exist, we are adding it--------\n");

	while (env[var_count] != NULL)
		var_count++;

	new_env = malloc((var_count + 2) * sizeof(char *));
	if (new_env == NULL)
	{
		free(key);
		free(new_variable);
		return (NULL);
	}

	for (i = 0; i < var_count; i++)
	{
		new_env[i] = _strdup(env[i]);
		if (new_env[i] == NULL)
		{
			for (j = 0; j < var_count; j++)
				free(new_env[j]);
			free(new_env);
			free(key);
			free(new_variable);
			return (NULL);
		}
	}


	new_env[var_count] = new_variable;
	new_env[var_count + 1] = NULL;
	environ = new_env;

	free(key);
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
