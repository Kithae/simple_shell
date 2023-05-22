#include <stdio.h>
#include "shell.h"

/**
 * string_length - Returns length of a String
 * @string: pointer to string variable
 *
 * Return: Always Length of a string.
 */

int string_length(char *string)
{
	int len;

	for (; *string != '\0'; string++)
	{
		len++;
	}
	return (len);
}
