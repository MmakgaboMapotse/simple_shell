#include "shell.h"

/**
 * paths - function that gets the path
 *
 * Return: string
 *
 */

char *paths()
{
	char *string = getenv("PATH");

	if (!string)
	{
		perror("Error: ");
		return (NULL);
	}
	return (string);
}


/**
 * path_token - function that tokenizes the path
 *
 * @string: string to be tokenized
 *
 * Return: array of strings
 *
 */

char **path_token(char *string)
{
	char *token = NULL, **array = NULL, *delimiter = ":", *new_token;
	int stringLength, i = 0;
	int pathCheck;

	token = strdup(string);
	stringLength = get_path_count(token, delimiter);
	array = malloc(sizeof(char *) * (stringLength));
	if (!array)
	{
		perror("Error: ");
		return (NULL);
	}
	new_token = strtok(token, ":");
	while (new_token)
	{
		pathCheck = path_verification(new_token); /* check if path is valid */
		if (pathCheck)
		{
			array[i] = strdup(new_token);
			i++;
		}
		else if (!pathCheck)
		{
			free_memory_on_fail(array, i);
			break;
		}
		new_token = strtok(NULL, ":");
	}
	array[i] = NULL;
	free(token);
	return (array);
}


/**
 * free_memory_on_fail - frees the failed memory when at some point
 * it fails to allocate more memory
 *
 * @memory: double pointer to be freed
 * @i: the index that failed to malloc
 *
 */
void free_memory_on_fail(char **memory, int i)
{
	int j = 0;

	while (j < i)
	{
		free(memory[j]);
		j++;
	}
	free(memory[i]);
	free(memory);
}

/**
 * get_path_count - gets the number of directories in the
 * PATH string
 *
 * @path_string: path string gotten from getenv
 * @delim: delimiter
 *
 * Return: the number of directories
 */

int get_path_count(char *path_string, char *delim)
{
	char *path_copy = strdup(path_string);
	char *token = NULL;
	int count = 0;

	token = strtok(path_copy, delim);
	count++;

	while (token)
	{
		count++;
		token = strtok(NULL, delim);
	}

	free(path_copy);
	return (count);

}
