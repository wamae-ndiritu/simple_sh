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
 * find_path - helper function to find_executable
 * @path_cpy: pointer to copy of path
 * @var: pointer to struct var
 * @filename: pointer to the file being found
 *
 * Return: returns pointer to a filepath found.
 */

char *find_path(char *path_cpy, env_var *var, char *filename)
{
	char *filepath, *new_path;
	int str_len;

	str_len = _strlen(path_cpy) + _strlen(filename) + 2;
	new_path = str_tok(path_cpy, ":\n");
	while (new_path != NULL)
	{
		filepath = malloc(sizeof(char) * str_len);
		if (filepath == NULL)
		{
			free(path_cpy);
			return (NULL);
		}
		_strcpy(filepath, new_path);
		_strcat(filepath, "/");
		_strcat(filepath, filename);
		if (access(filepath, F_OK | X_OK) == 0)
		{
			free(path_cpy);
			return (filepath);
		}
		new_path = str_tok(NULL, ":\n");
		free(filepath);
	}
	free(path_cpy);
	free(var->key);
	free(var);
	errno = ENOENT;
	return (NULL);
}

/**
 * find_executable - finds the filepath for an executable file
 * @var: pointer to a struct conatining env variable
 * @filename: pointer to the executable filename
 *
 * Return: returns the filepath of the executable
 *
 */

char *find_executable(env_var *var, char *filename)
{
	char *path_cpy, *filepath;

	if (filename[0] == '/')
	{
		if (access(filename, F_OK | X_OK) == 0)
			return (_strdup(filename));
		else
			return (NULL);
	}
	path_cpy = _strdup(var->value);
	if (path_cpy == NULL)
	{
		free(var->key);
		free(var);
		return (NULL);
	}
	filepath = find_path(path_cpy, var, filename);
	if (filepath == NULL)
		return (NULL);
	return (filepath);
}

