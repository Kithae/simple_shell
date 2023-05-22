#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "shell.h"

/**
 * parseInput - seperate input into tokens
 * @input: pointer to string for parsing
 *
 * Return: NULL
 */

char* read_line()
{
	char *input = NULL;
	size_t buf = 0;

	if(getline(&input, &buf, stdin) == -1)
	{
		return NULL;
	}
return input;
}

/**
 *
 *
 *
 *
 *
 *
 */

char parseInput(char *input)
{
	char *input_copy = NULL;
	const char *delimiter = (" " "\n" "\t");
	char *token;
	int i;
	int num_token = 0;
	char **argv;
	
	input = read_line();
	input_copy = malloc(sizeof(char) * (size_t)input);
	if (input_copy == NULL)
	{
		perror("memory allocation error");
		return (-1);
	}
	input_copy = copy_str(input);
	token = strtok(input_copy, delimiter);
	while (token != NULL)
	{
		num_token++;
		token = strtok(NULL, delimiter);
	}
	num_token++;
	argv = malloc(sizeof(char *) * num_token);
	token = strtok(input_copy, delimiter);
	for (i = 0; token != NULL; i++)
	{
		argv[i] = malloc(sizeof(char) * string_length(token));
		argv[i] = copy_str(token);
		token = strtok(NULL, delimiter);
	}
	argv[i] = NULL;

	return (*argv[i]);
}
