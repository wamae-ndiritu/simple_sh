#ifndef HEADER_FILE
#define HEADER_FILE
#include <stdio.h>
#include <stddef.h>

/* Global external variables */
extern char** my_environ;

/**
 * struct custom_args - structure to hold argc and argv[]
 * @lineptr_cpy: pointer to a mem copied using strdup
 * @argv: pointer to an array of arguments passed as strings
 *
 */

typedef struct custom_args
{
	char *lineptr_cpy;
	char **argv;
} custom_args;
/**
 * struct env_var - structure to hold environment variables
 * @key: pointer to hold the variable name
 * @value: pointer to hold the variable value
 *
 */

typedef struct env_var
{
	char *key;
	char *value;
} env_var;

/**
 * struct Command - structure to store command with it's
 *	corresponding handler function
 * @command: pointer to the command
 * @handler: function pointer to handle the command
 */

typedef struct Command
{
	char *command;
	void (*handler)(char **);
} Command;

extern char **environ;

void print_env(char **env);
env_var *get_env(char *variable);
ssize_t get_line(char **lineptr, size_t *n, FILE *stream);
custom_args *init_argv(char *lineptr, env_var *path);
char *str_tok(char *str, char *delim);
void (*get_callback(char *command))(char **);
void handle_exit(char **, char *, char *, env_var *);

char *_strcat(char *dest, const char *src);
char *_strcpy(char *dest, const char *src);
int _strlen(const char *s);
char *_strdup(const char *str);
char *_memcpy(char *dest, const char *src, unsigned int n);
int _atoi(char *s);
int _strcmp(char *s1, char *s2);
char *get_line_number(void);
void *_realloc(void *ptr, size_t size);
void print_err(char *program_name);
void _itoa(int n, char *str, int base);
void free_struct(custom_args *argv, env_var *path);
void signal_handler(int signum);
char *find_path(char *path_cpy, env_var *var, char *filename);
char *find_executable(env_var *var, char *filename);

void change_directory(char **argv);
void free_resources(env_var *path, custom_args *argv);
char *_setenv(const char *name, const char *value, int overwrit);
int _unsetenv(const char *name);

/* environ.c */
char **get_environ();

#endif
