#include "shell.h"


/**
 * command_not_found - executes when a command is not found
 * @arg: command
 * @argv: array of commands
 */
void command_not_found(char *arg, char **argv)
{
	fprintf(stderr, "%s: 1: %s: not found\n", arg, argv[0]);
	cleanup_command(argv);
	exit(127);
}
