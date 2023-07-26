#include <stdio.h>
#include <unistd.h>
#include <signal.h>

/**
 * signal_handler - blocks CTR - C
 * @signum: integer to the signal
 *
 * Return: Nothing.
 */

void signal_handler(int signum)
{
	(void)signum;
	write(1, "\n$ ", 3);
}

