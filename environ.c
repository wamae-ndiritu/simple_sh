#include "main.h"

extern char **environ;

/**
 * get_environ - gets the content of environ (external variable)
 * Return: Returns the environ
 */

char **get_environ()
{
	return (environ);
}

