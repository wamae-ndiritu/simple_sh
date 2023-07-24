#include <stdio.h>
#include "main.h"

/**
 * get_callback - selects the prefered function to be
 *	called based on the the built in command
 * @command: pointer to the command
 *
 * Return: returns a function pointer of any type.
 */


void (*get_callback(char *command))(char **)
{
	Command commandList[] = {
		{"env", print_env},
		{"cd", change_directory},
		{NULL, NULL}
	};
	int i = 0;

	while (commandList[i].command != NULL)
	{
		if (_strcmp(commandList[i].command, command) == 0)
			return (commandList[i].handler);
		i++;
	}
	return (NULL);
}
