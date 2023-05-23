#include "shell.h"
/**
 * string_length - a function that shows the string length.
 * @string: a string pointer.
 * Return: string length.
 */
int string_length(char *string)
{
	int l = 0;

	if (string == NULL)
		return (0);
	while (string[l++] != '\0')
	{
	}
	return (--l);
}
/**
 * copy_str - a string duplicator function.
 * @string: a string
 * Return: an array pointer
 */
char *copy_str(char *string)
{
	char *sum;
	int len, a;

	if (string == NULL)
		return (NULL);
	len = string_length(string) + 1;
	sum = malloc(sizeof(char) * len);
	if (sum == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (a = 0; a < len ; a++)
	{
		sum[a] = string[a];
	}
	return (sum);
}
/**
 * string_compare - a function for comparing two strings
 * @string1: 1st string
 * @string2: 2nd string
 * @number: total characters
 * Return: 1 else, 0
 */
int string_compare(char *string1, char *string2, int number)
{
	int a;

	if (string1 == NULL && string2 == NULL)
		return (1);
	if (string1 == NULL || string2 == NULL)
		return (0);
	if (number == 0)
	{
		if (string_length(string1) != string_length(string2))
			return (0);
		for (a = 0; string1[a]; a++)
		{
			if (string1[a] != string2[a])
				return (0);
		}
		return (1);
	}
	else
	{
		for (a = 0; a < number ; a++)
		{
			if (string1[a] != string2[a])
				return (0);
		}
		return (1);
	}
}
/**
 * concat_str - A function for concatenating two strings.
 * @string1: 1st string
 * @string2: 2nd string
 *
 * Return: an array pointer
 */
char *concat_str(char *string1, char *string2)
{
	char *sum;
	int len1 = 0, len2 = 0;

	if (string1 == NULL)
		string1 = "";
	len1 = string_length(string1);
	if (string2 == NULL)
		string2 = "";
	len2 = string_length(string2);
	sum = malloc(sizeof(char) * (len1 + len2 + 1));
	if (sum == NULL)
	{
		errno = ENOMEM;
		perror("Error");
		return (NULL);
	}
	for (len1 = 0; string1[len1] != '\0'; len1++)
		sum[len1] = string1[len1];
	free(string1);
	for (len2 = 0; string2[len2] != '\0'; len2++)
	{
		sum[len1] = string2[len2];
		len1++;
	}
	sum[len1] = '\0';
	return (sum);
}
/**
 * string_reverse - a function for reversing strings.
 *
 * @string: a pointer.
 * Return: void.
 */
void string_reverse(char *string)
{
	int a = 0, len = string_length(string) - 1;
	char b;

	while (a < len)
	{
		b = string[a];
		string[a++] = string[len];
		string[len--] = b;
	}
}
