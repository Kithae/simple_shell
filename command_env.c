#include "shell.h"

/**
 * env_builtin - A function to display the current shell environment
 * @data: a structure pointer
 * Return: 0 else, a number
**/
int env_builtin(input *data)
{
	int a;
	char c[50] = {'\0'};
	char *v_copy = NULL;

	if (data->tokens[1] == NULL)
		environ_print(data);
	else
	{
		for (a = 0; data->tokens[1][a]; a++)
		{
			if (data->tokens[1][a] == '=')
			{
				v_copy = copy_str(list_key(c, data));
				if (v_copy != NULL)
					key_set(c, data->tokens[1] + a + 1, data);

				environ_print(data);
				if (list_key(c, data) == NULL)
				{
					_print(data->tokens[1]);
					_print("\n");
				}
				else
				{
					key_set(c, v_copy, data);
					free(v_copy);
				}
				return (0);
			}
			c[a] = data->tokens[1][a];
		}
		errno = 2;
		perror(data->cmd_name);
		errno = 127;
	}
	return (0);
}

/**
 * builtin_change_env - A function that sets a new environment.
 * @data: a structure pointer
 * Return: 0 else, a number
**/
int builtin_change_env(input *data)
{
	if (data->tokens[1] == NULL || data->tokens[2] == NULL)
		return (0);
	if (data->tokens[3] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}

	key_set(data->tokens[1], data->tokens[2], data);

	return (0);
}

/**
 * builtin_undo_env - A function that unsets a new environment.
 * @data: a structure pointer
 * Return: 0
 */
int builtin_undo_env(input *data)
{
	if (data->tokens[1] == NULL)
		return (0);
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	remove_key(data->tokens[1], data);

	return (0);
}
