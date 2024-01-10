#include "shell.h"

/**
 * builtin_cmd_check - checks if a command is a builtin
 *
 * @array: commands passed
 * @envs: environmental variables
 *
 * Return: 1 on success or 0 on failure
 */
int builtin_cmd_check(char **array, char **envs)
{
	int count = 0;


	if (strcmp(array[0], "env") == 0)
	{
		while (envs[count])
		{
			if (envs[count])
				printf("%s\n", envs[count]);
			count++;
		}
		cleanup_command(array);
		return (1);
	}
	else if (strcmp(array[0], "exit") == 0)
	{
		cleanup_command(array);
		exit(0);
	}
	return (0);
}

