#include <stdlib.h>
#include "main.h"


/**
 * free_struct - free any structure allocated mem
 * @argv: pointer to struct custom_args
 * @var: pointer to struct env_var
 *
 * Return: Nothing.
 */

void free_struct(env_var *var, custom_args *argv)
{
	free(var->key);
	var->key = NULL;
	free(var);
	free(argv->lineptr_cpy);
	argv->lineptr_cpy = NULL;
	free(argv->argv);
	argv->argv = NULL;
	free(argv);
}


/**
 * free_env_var - free the struct env_var
 * @path: pointer to the structure being freed
 * Return: Nothing.
 */

void free_env_var(env_var *var)
{
	free(var->key);
	var->key = NULL;
	free(var);
}

/**
 * free_custom_args - free the struct custom_args
 * @argv: pointer to the structure allocated memory
 *
 * Return: Nothing.
 */

void free_custom_args(custom_args *argv)
{
	free(argv->lineptr_cpy);
	argv->lineptr_cpy = NULL;
	free(argv->argv);
	argv->argv = NULL;
	free(argv);
}
