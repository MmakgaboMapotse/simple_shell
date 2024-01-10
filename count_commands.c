#include "shell.h"


/**
 * count_commands - counts the number of tokens in a command
 * @string: command passed
 * @delim: delimiter string passed to split tokens
 * Return: number of words
 */
int count_commands(char *string, char *delim)
{
	char *token = strdup(string), *new_token;

	int count = 0;

	if (!token)
	{
		perror("malloc");
		return (0);
	}
	new_token = strtok(token, delim);
	while (new_token)
	{
		count++;
		new_token = strtok(NULL, delim);
	}

	free(token);
	return (count);
}
