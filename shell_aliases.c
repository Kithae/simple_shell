#include "shell.h"

/**
 * alias_print - A function for removing, adding or showing aliases
 * @data: a structure pointer
 * @alias: a name
 * Return: 0 else, a number
 */
int alias_print(input *data, char *alias)
{
	int a, b, alias_len;
	char buffer[250] = {'\0'};

	if (data->map_alias)
	{
		alias_len = string_length(alias);
		for (a = 0; data->map_alias[a]; a++)
		{
			if (!alias || (string_compare(data->map_alias[a], alias, alias_len)
				&&	data->map_alias[a][alias_len] == '='))
			{
				for (b = 0; data->map_alias[a][b]; b++)
				{
					buffer[b] = data->map_alias[a][b];
					if (data->map_alias[a][b] == '=')
						break;
				}
				buffer[b + 1] = '\0';
				bf_add(buffer, "'");
				bf_add(buffer, data->map_alias[a] + b + 1);
				bf_add(buffer, "'\n");
				_print(buffer);
			}
		}
	}

	return (0);
}

/**
 * read_alias - another function to help the first one.
 * @data: a structure pointer
 * @name: an alias name.
 * Return: 0 else, a number
 */
char *read_alias(input *data, char *name)
{
	int a, alias_len;

	if (name == NULL || data->map_alias == NULL)
		return (NULL);

	alias_len = string_length(name);

	for (a = 0; data->map_alias[a]; a++)
	{
		if (string_compare(name, data->map_alias[a], alias_len) &&
			data->map_alias[a][alias_len] == '=')
		{
			return (data->map_alias[a] + alias_len + 1);
		}
	}
	return (NULL);

}

/**
 * op_alias - A function for overriding these aliases
 * @alias_string: a name string
 * @data: a structure pointer
 * Return: 0 else, a number
 */
int op_alias(char *alias_string, input *data)
{
	int a, b;
	char buffer[250] = {'0'}, *temp = NULL;

	if (alias_string == NULL ||  data->map_alias == NULL)
		return (1);
	for (a = 0; alias_string[a]; a++)
		if (alias_string[a] != '=')
			buffer[a] = alias_string[a];
		else
		{
			temp = read_alias(data, alias_string + a + 1);
			break;
		}

	for (b = 0; data->map_alias[b]; b++)
		if (string_compare(buffer, data->map_alias[b], a) &&
			data->map_alias[b][a] == '=')
		{
			free(data->map_alias[b]);
			break;
		}

	if (temp)
	{
		bf_add(buffer, "=");
		bf_add(buffer, temp);
		data->map_alias[b] = copy_str(buffer);
	}
	else
		data->map_alias[b] = copy_str(alias_string);
	return (0);
}
