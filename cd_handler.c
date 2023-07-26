#include "main.h"
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

/**
 * get_argv_count - get the number of arguments in argv
 * @argv: pointer to an array of arguments passed
 * Return: returns the argument count
 */
int get_argv_count(char **argv)
{
	int i = 0, ac = 0;

	while (argv[i] != NULL)
	{
		ac++;
		i++;
	}
	return (ac);
}

/**
 * change_directory_helper - function to free resources in change_directory
 * @old_pwd: Pointer to the env_var structure containing old PWD value.
 */
void change_directory_helper(env_var *old_pwd)
{
	if (old_pwd->value == NULL)
		return;
	write(1, old_pwd->value, _strlen(old_pwd->value));
	write(1, "\n", 2);
	if (chdir(old_pwd->value) != 0)
		perror("cd");
	free(old_pwd->key);
	old_pwd->key = NULL;
	free(old_pwd);
}

/**
 * change_directory - changes the working directory
 * @argv: pointer to an array of arguments
 *
 * Return: Nothing.
 */
void change_directory(char **argv)
{
	char current_dir[1024];
	env_var *old_pwd = get_env("PWD"), *env = get_env("HOME");
	char *home;
	int ac;

	home = env->value;
	ac = get_argv_count(argv);
	if (ac == 1)
	{
		if (chdir(home) != 0)
			perror("cd");
	}
	else if (_strcmp(argv[1], "~") == 0 || _strcmp(argv[1], "") == 0)
	{
		if (chdir(home) != 0)
			perror("cd");
	}
	else if (_strcmp(argv[1], "-") == 0)
	{
		env_var *old_pwd = get_env("OLDPWD");

		change_directory_helper(old_pwd);
	}
	else
	{
		if (chdir(argv[1]) != 0)
			perror("cd");
	}

	if (getcwd(current_dir, sizeof(current_dir)) != NULL)
	{
		setenv("PWD", current_dir, 1);
		setenv("OLDPWD", old_pwd->value, 1);
	}
	else
		perror("getcwd");
	free(env->key);
	free(env);
	free(old_pwd->key);
	free(old_pwd);
}
