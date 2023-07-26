#include <stdlib.h>
#include "main.h"

/**
 * free_struct - free any structure allocated mem
 * @argv: pointer to struct custom_args
 * @path: pointer to struct env_var
 *
 * Return: Nothing.
 */

void free_struct(custom_args *argv, env_var *path)
{
	free(argv->lineptr_cpy);
	argv->lineptr_cpy = NULL;
	free(argv->argv);
	argv->argv = NULL;
	free(argv);
	free(path->key);
	path->key = NULL;
	free(path);
}
