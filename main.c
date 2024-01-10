#include "shell.h"


/**
 * main - function that calls other functions
 * @argc: the number of arguments passed to the terminal
 * @argv: array of pointers holding the commands
 * @env: environmental variable
 * Return: 0
 */
int main(__attribute__ ((unused)) int argc, char **argv, char **env)
{
	int space = 0;

	env = environ;
	for (;;)
	{
		char *result = NULL, **split_string;
		size_t count;
		size_t bufsize = 0;
		(void)argv;

		if (isatty(STDIN_FILENO))
			printf("(hsh) ");
		count = getline(&result, &bufsize, stdin);
		if ((int)count == -1)
		{
			free(result);
			bufsize = 0;
			exit(0);
		}
		else if (count <= 1 || count <= 0)
		{
			free(result);
			bufsize = 0;
			continue;
		}
		else
		{
			space = remove_spaces(result);
			if (space)
			{
				split_string = split_command(result);
				clean_getline_memory(result, bufsize);
				discharge_command(split_string, split_string[0], env);
			}
			else
				clean_getline_memory(result, bufsize);
		}
	}
	return (0);
}

/**
 * remove_spaces - cleanses the input data
 * @string: string / data to be cleansed
 * Return: 1 on success
 */
int remove_spaces(char *string)
{
	int i = 0;

	while (string[i] == ' ' || string[i] == '\n')
		i++;
	if (string[i] == '\0')
		return (0);
	memmove(string, string + i, strlen(string) - i + 1);
	return (1);
}


/**
 * free_buffer - frees the memory used to store
 * getline string and also resets bufsize to 0
 *
 * @dt: memory holding getline data
 * @size: size of the buffer
 *
 */

void free_buffer(char *dt, size_t size)
{
	size_t *i = &size;

	free(dt);
	*i = 0;
}

/**
 * split_command - split the string into tokens
 *
 * @string: string/command to be split
 *
 * Return: array of split string tokens
 */

char **split_command(char *string)
{
	int i = 0, j = 0, len = 0;
	char **split_cmd = NULL, *delimiter = " \t\n", *token, *new_token;

	new_token = strdup(string);
	if (!new_token)
	{
		perror("malloc");
		return (0);
	}
	len = count_commands(string, delimiter);
	split_cmd = malloc((len + 1) * sizeof(char *));
	if (split_cmd == NULL)
	{
		perror("malloc");
		return (NULL);
	}
	token = strtok(new_token, delimiter);
	while (token)
	{
		split_cmd[i] = strdup(token);
		if (split_cmd[i] == NULL)
		{
			perror("malloc");
			while (j < i)
			{
				free(split_cmd[j]);
				j++;
			}
			free(split_cmd[i]);
		}
		i++;
		token = strtok(NULL, delimiter);
	}
	split_cmd[i] = NULL;
	free(new_token);
	return (split_cmd);
}
