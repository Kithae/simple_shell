#include "shell.h"

/**
* _readline - A function to scan a line from the input prompt.
* @data: a structure pointer
*
* Return: sum bytes.
*/
int _readline(input *data)
{
	char bf[BUFFER_SIZE] = {'\0'};
	static char *array_cmd[10] = {NULL};
	static char array_op[10] = {'\0'};
	ssize_t read_byte, a = 0;

	if (!array_cmd[0] || (array_op[0] == '&' && errno != 0) ||
		(array_op[0] == '|' && errno == 0))
	{
		for (a = 0; array_cmd[a]; a++)
		{
			free(array_cmd[a]);
			array_cmd[a] = NULL;
		}

		read_byte = read(data->file_descriptor, &bf, BUFFER_SIZE - 1);
		if (read_byte == 0)
			return (-1);

		a = 0;
		do {
			array_cmd[a] = copy_str(_stringtok(a ? NULL : bf, "\n;"));
			a = logic_opers(array_cmd, a, array_op);
		} while (array_cmd[a++]);
	}

	data->input_line = array_cmd[0];
	for (a = 0; array_cmd[a]; a++)
	{
		array_cmd[a] = array_cmd[a + 1];
		array_op[a] = array_op[a + 1];
	}

	return (string_length(data->input_line));
}


/**
* logic_opers - a function to scan for special operators.
* i.e. && and || operators
* @array_cmd: an array.
* @i: an array index
* @array_op: a logical operators array
* Return: the last command index.
*/
int logic_opers(char *array_cmd[], int i, char array_op[])
{
	char *temp = NULL;
	int a;

	for (a = 0; array_cmd[i] != NULL  && array_cmd[i][a]; a++)
	{
		if (array_cmd[i][a] == '&' && array_cmd[i][a + 1] == '&')
		{
			temp = array_cmd[i];
			array_cmd[i][a] = '\0';
			array_cmd[i] = copy_str(array_cmd[i]);
			array_cmd[i + 1] = copy_str(temp + a + 2);
			i++;
			array_op[i] = '&';
			free(temp);
			a = 0;
		}
		if (array_cmd[i][a] == '|' && array_cmd[i][a + 1] == '|')
		{
			temp = array_cmd[i];
			array_cmd[i][a] = '\0';
			array_cmd[i] = copy_str(array_cmd[i]);
			array_cmd[i + 1] = copy_str(temp + a + 2);
			i++;
			array_op[i] = '|';
			free(temp);
			a = 0;
		}
	}
	return (i);
}
