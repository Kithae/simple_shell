#include "shell.h"
#include <stdio.h>

/**
 * findTokenEnd - find the end of string
 * @str: string to scan through
 * @delimiter: strings to ignore
 *
 * Return: End of string
 */

char *findTokenEnd(char *str, const char *delimiter)
{
	int delimiterLength = strlen(delimiter);
	char *tokenEnd = str;
	int isDelimiter = 0;
	int i;

	while (*tokenEnd != '\0')
	{
		for (i = 0; i < delimiterLength; i++)
		{
			if (*tokenEnd == delimiter[i])
			{
				isDelimiter = 1;
				break;
			}
		}
		if (isDelimiter)
		{
			break;
		}
		tokenEnd++;
	}
	return (tokenEnd);
}

/**
 * _stringtok - tokenize string
 * @str: pointer to string
 * @delimiter: pointer to strings for skip
 *
 * Return: tokens
 */

char *_stringtok(char *line, char *delim)
{
	static char *tokenStart = NULL;
	static char *next_Token = NULL;
	static char *tokenEnd;

	if (line != NULL)
	{
		tokenStart = line;
		next_Token = line;
	}
	if (tokenStart == NULL)
	{
		return (NULL);
	}

	tokenEnd = findTokenEnd(tokenStart, delim);
	if (*tokenEnd == '\0')
	{
		next_Token = NULL;
		return (next_Token);
	}
	else
	{
		*tokenEnd = '\0';
		next_Token = tokenEnd + 1;
	}
	return (tokenStart);
}
