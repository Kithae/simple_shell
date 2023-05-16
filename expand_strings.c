#include "shell.h"

/**
 * aug_variables - a function to expand (augment) the given variables
 * @data: a structure pointer
 *
 * Return: nothing, else error.
 */
void aug_variables(input *data)
{
	int a, b;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;
	bf_add(line, data->input_line);
	for (a = 0; line[a]; a++)
		if (line[a] == '#')
			line[a--] = '\0';
		else if (line[a] == '$' && line[a + 1] == '?')
		{
			line[a] = '\0';
			l_to_str(errno, expansion, 10);
			bf_add(line, expansion);
			bf_add(line, data->input_line + a + 2);
		}
		else if (line[a] == '$' && line[a + 1] == '$')
		{
			line[a] = '\0';
			l_to_str(getpid(), expansion, 10);
			bf_add(line, expansion);
			bf_add(line, data->input_line + a + 2);
		}
		else if (line[a] == '$' && (line[a + 1] == ' ' || line[a + 1] == '\0'))
			continue;
		else if (line[a] == '$')
		{
			for (b = 1; line[a + b] && line[a + b] != ' '; b++)
				expansion[b - 1] = line[a + b];
			temp = list_key(expansion, data);
			line[a] = '\0', expansion[0] = '\0';
			bf_add(expansion, line + a + b);
			temp ? bf_add(line, temp) : 1;
			bf_add(line, expansion);
		}
	if (!string_compare(data->input_line, line, 0))
	{
		free(data->input_line);
		data->input_line = copy_str(line);
	}
}

/**
 * aug_alias - a function to expand the aliases as well
 * @data: a structure pointer
 *
 * Return: nothing else, error.
 */
void aug_alias(input *data)
{
	int a, b, was_expanded = 0;
	char line[BUFFER_SIZE] = {0}, expansion[BUFFER_SIZE] = {'\0'}, *temp;

	if (data->input_line == NULL)
		return;

	bf_add(line, data->input_line);

	for (a = 0; line[a]; a++)
	{
		for (b = 0; line[a + b] && line[a + b] != ' '; b++)
			expansion[b] = line[a + b];
		expansion[b] = '\0';

		temp = read_alias(data, expansion);
		if (temp)
		{
			expansion[0] = '\0';
			bf_add(expansion, line + a + b);
			line[a] = '\0';
			bf_add(line, temp);
			line[string_length(line)] = '\0';
			bf_add(line, expansion);
			was_expanded = 1;
		}
		break;
	}
	if (was_expanded)
	{
		free(data->input_line);
		data->input_line = copy_str(line);
	}
}

/**
 * bf_add - a function for appending strings at the buffer end
 * @buffer: a buffer
 * @str: a string
 * Return: nothing else, error.
 */
int bf_add(char *buffer, char *str)
{
	int len, a;

	len = string_length(buffer);
	for (a = 0; str[a]; a++)
	{
		buffer[len + a] = str[a];
	}
	buffer[len + a] = '\0';
	return (len + a);
}
