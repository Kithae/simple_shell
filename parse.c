#include "shell.h"
/**
 * parse - A function that uses a specified delimiter to separate the string
 * @data: a structure pointer
 * Return: the string array
 */
void parse(input *data)
{
	char *dlimit = " \t";
	int a, b, tally = 2, length;

	length = string_length(data->input_line);
	if (length)
	{
		if (data->input_line[length - 1] == '\n')
			data->input_line[length - 1] = '\0';
	}
	for (a = 0; data->input_line[a]; a++)
	{
		for (b = 0; dlimit[b]; b++)
		{
			if (data->input_line[a] == dlimit[b])
				tally++;
		}
	}
	data->tokens = malloc(tally * sizeof(char *));
	if (data->tokens == NULL)
	{
		perror(data->program_name);
		exit(errno);
	}
	a = 0;
	data->tokens[a] = copy_str(_stringtok(data->input_line, dlimit));
	data->cmd_name = copy_str(data->tokens[0]);
	while (data->tokens[a++])
	{
		data->tokens[a] = copy_str(_stringtok(NULL, dlimit));
	}
}
