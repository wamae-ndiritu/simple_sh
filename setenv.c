#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "main.h"

/**
 * _setenv - initializes a new environment variable, or modify existing one
 * @name: pointer the variable whose value is to be set/updated
 * @value: pointer to the value to be set/updated
 * @overwrite: interger condition to overwrite existing variable
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
	int result;

	result = unsetenv(name);
	if (result != 0)
		perror("unsetenv");
	return (result);
}
