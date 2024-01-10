#include "shell.h"

/**
 * clean_getline_memory - frees the memory used to store a
 * string by getline
 *
 * @string: the buffer used to store the string
 * @size: the number of characters that was read
 *
 */

void clean_getline_memory(char *string, size_t size)
{
	free(string);
	if (size)
		size = 0;
}
