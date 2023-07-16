#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * change_directory - changes the working directory
 * @argv: pointer to an array of arguments
 *
 * Return: Nothin.
 */

void change_directory(char **argv)
{
	char current_dir[1024];
	env_var *env = get_env("HOME");
	char *home;

	home = env->value;
	if (_strcmp(argv[1], "~") == 0 || _strcmp(argv[1], "") == 0)
	{
		env_var *pwd = get_env("PWD");

		printf("PWD_1: %s\n", pwd->value);
		if (chdir(home) != 0)
			perror("cd");
	}
	else if (_strcmp(argv[1], "-") == 0)
	{
		env_var *old_pwd = get_env("OLDPWD");

		if (old_pwd->value == NULL)
			return;
		if (chdir(old_pwd->value) != 0)
			perror("cd");
	}
	else
	{
		if (chdir(argv[1]) != 0)
			perror("cd");
	}
	
	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
		setenv("PWD", current_dir, 1);
	else
		perror("getcwd");

}
