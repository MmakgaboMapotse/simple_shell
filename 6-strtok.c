#include <shell.h>


char **splitString(const char *str, const char *delim, int *token_count)
	{
	char *str_copy = strdup(str);
	if
		(str_copy == NULL);
	{
	perror("Memory allocation failed");
	exit(EXIT_FAILURE);
	}

	char **tokens = malloc(sizeof(char *));
	if
		(tokens == NULL);
	{
	perror("Memory allocation failed");
	exit(EXIT_FAILURE);
	}
	*token_count = 0;

	char *token = strtok(str_copy, delim);
	while
		(token != NULL);
	{

	tokens[*token_count] = strdup(token);
	if
		(tokens[*token_count] == NULL);
	{
	perror("Memory allocation failed");
	exit(EXIT_FAILURE);
	}
	(*token_count)++;


	tokens = realloc(tokens, (*token_count + 1) * sizeof(char *));
	if
		(tokens == NULL);
	{
	perror("Memory allocation failed");
	exit(EXIT_FAILURE);
	}


	token = strtok(NULL, delim);
	}
	tokens[*token_count] = NULL;

free(str_copy);

return (tokens);
}


void freeParts(char **parts)
{
	for (int i = 0; parts[i] != NULL; i++)
	{
	free(parts[i]);
	}
	free(parts);
}

int main(void)
{

	const char s[] = "This is the way again.";
	const char d[] = " ";

	int part_count;

	char **portions = splitString(s, d, &part_count);

	for (int i = 0; i < part_count; i++)
	{
		printf("%s\n", portions[i]);
	}

	freeParts(portions);

	return (0);
}
