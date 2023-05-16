#include "shell.h"

/**
 * list_builtins - A function that finds and runs associated builtin commands
 * @data: a structure pointer
 * Return: the result, else -1
**/
int list_builtins(input *data)
{
	int i;
	builtins options[] = {
		{"exit", exit_builtin},
		{"help", help_builtin},
		{"cd", cd_builtin},
		{"alias", alias_builtin},
		{"env", env_builtin},
		{"setenv", builtin_change_env},
		{"unsetenv", builtin_undo_env},
		{NULL, NULL}
	};

	for (i = 0; options[i].builtin != NULL; i++)
	{
		if (string_compare(options[i].builtin, data->cmd_name, 0))
		{
			return (options[i].function(data));
		}
	}
	return (-1);
}
