#include "shell.h"
/**
 * free_recur_data - a function to first free the loop fields
 * @data: a structure pointer
 * Return: Nothing
 */
void free_recur_data(input *data)
{
	if (data->tokens)
		free_pt_array(data->tokens);
	if (data->input_line)
		free(data->input_line);
	if (data->cmd_name)
		free(data->cmd_name);
	data->input_line = NULL;
	data->cmd_name = NULL;
	data->tokens = NULL;
}
/**
 * free_full_data - Then a function to free all the data fields
 * @data: a structure pointer
 * Return: Nothing
 */
void free_full_data(input *data)
{
	if (data->file_descriptor != 0)
	{
		if (close(data->file_descriptor))
			perror(data->program_name);
	}
	free_recur_data(data);
	free_pt_array(data->env);
	free_pt_array(data->map_alias);
}
/**
 * free_pt_array - finally a function to free the arrays and their pointers
* @array: array of pointers
 * Return: nothing
 */
void free_pt_array(char **array)
{
	int a;

	if (array != NULL)
	{
		for (a = 0; array[a]; a++)
			free(array[a]);
		free(array);
		array = NULL;
	}
}
