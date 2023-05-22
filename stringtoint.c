#include "shell.h"

/**
 * _atoi - converts string to integers
 * @str: string pointer
 *
 * Return: coverted digits.
 */

int _atoi(char *str)
{
	int result = 0;
	int sign = 1;
	int i = 0;

	while ((str[i] == ' ') || (str[i] == '\t') || (str[i] == '\n'))
		i++;
	if (str[i] == '+' || str[i] == '-')
	{
		sign = (str[i] == '-') ? -1 : 1;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9')
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}

	return (result * sign);
}
