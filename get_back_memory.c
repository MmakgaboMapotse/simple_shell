#include "shell.h"

/**
 * cleanup_struct - frees the struct memory allocation
 *
 * @path: malloced struct memory
 *
 */

void cleanup_struct(node_checker *path)
{
	if (path->bin)
		free(path->bin);
	free(path);
}


/**
 * cleanup_command - free memory of split commands
 * @command: commands to free
 *
 */
void cleanup_command(char **command)
{
	int i = 0;

	while (command[i])
	{
		if (command[i])
			free(command[i]);
		i++;
	}
	free(command);
}
