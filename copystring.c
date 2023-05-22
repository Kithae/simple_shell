#include "shell.h"
#include <stdio.h>
#include <string.h>

/**
 * *copy_str - copies a string
 * @string: pointer to string vaariable to be copied
 *
 * Return: copied string.
 */

char *copy_str(char *string)
{
	int len, n;
	char *str_copy;

	len = string_length(string);
	str_copy = malloc(len + 1);
	if (str_copy == NULL)
	{
		return (NULL);
	}

	for (n = 0; n < len; n++)
	{
		str_copy[n] = string[n];
	}
	while (n < len)
	{
		str_copy[n] = '\0';
		len++;
	}

	return (str_copy);
}
