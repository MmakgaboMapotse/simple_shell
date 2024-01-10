#include "shell.h"

/**
 * path_verification - verify if the path exists
 * @command: path to verify
 * Return: 1 if the command is in the path, 0 if not
 */

int path_verification(char *command)
{
	int retrnValue;
	struct stat st;

	retrnValue = stat(command, &st);
	if (retrnValue == 0)
		return (1);
	return (0);
}
