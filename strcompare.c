#include "shell.h"
#include <stdio.h>
#include <string.h>

/**
 * string_compare - compares two strings.
 * @string1: pointer to string variabe.
 * @string2: pointer to string variabe.
 * @number: string counter variable.
 *
 * Return: Difference of two strings.
 */

int string_compare(char *string1, char *string2, int number)
{
	int i;

	for (i = 0; i < number; i++)
	{
		if (string1[i] != string2[i])
		{
			return (0);
		}
	}
	return (string1[i] - string2[i]);
}
