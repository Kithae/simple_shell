#include "shell.h"

/**
 * list_key - a function for obtaining the current value
* of a specified environment variable
 * @key: a variable
 * @data: a structure pointer
 * Return: a pointer else, NULL
 */
char *list_key(char *key, input *data)
{
	int a, length_of_key = 0;

	if (key == NULL || data->env == NULL)
		return (NULL);

	length_of_key = string_length(key);

	for (a = 0; data->env[a]; a++)
	{
		if (string_compare(key, data->env[a], length_of_key) &&
		 data->env[a][length_of_key] == '=')
		{
			return (data->env[a] + length_of_key + 1);
		}
	}
	return (NULL);
}

/**
 * key_set - a function to overwrite (if necessary)
* the above environment variable value
 * or create it if does not exist.
 * @key: a variable
 * @value: a variable
 * @data: a structure pointer
 * Return: 1 or 0.
 */

int key_set(char *key, char *value, input *data)
{
	int a, length_of_key = 0, new_key = 1;

	if (key == NULL || value == NULL || data->env == NULL)
		return (1);

	length_of_key = string_length(key);

	for (a = 0; data->env[a]; a++)
	{
		if (string_compare(key, data->env[a], length_of_key) &&
		 data->env[a][length_of_key] == '=')
		{
			new_key = 0;
			free(data->env[a]);
			break;
		}
	}
	data->env[a] = concat_str(copy_str(key), "=");
	data->env[a] = concat_str(data->env[a], value);

	if (new_key)
	{
		data->env[a + 1] = NULL;
	}
	return (0);
}

/**
 * remove_key - a function to remove (if necessary) a key
* from the above environment
 * @key: a variable
 * @data: a structure pointer
 * Return: 1 or 0
 */
int remove_key(char *key, input *data)
{
	int a, length_of_key = 0;

	if (key == NULL || data->env == NULL)
		return (0);

	length_of_key = string_length(key);

	for (a = 0; data->env[a]; a++)
	{
		if (string_compare(key, data->env[a], length_of_key) &&
		 data->env[a][length_of_key] == '=')
		{
			free(data->env[a]);

			a++;
			for (; data->env[a]; a++)
			{
				data->env[a - 1] = data->env[a];
			}
			data->env[a - 1] = NULL;
			return (1);
		}
	}
	return (0);
}


/**
 * environ_print - a function to display the current / new environment
 * @data: a structure pointer
 * Return: nothing
 */
void environ_print(input *data)
{
	int b;

	for (b = 0; data->env[b]; b++)
	{
		_print(data->env[b]);
		_print("\n");
	}
}
