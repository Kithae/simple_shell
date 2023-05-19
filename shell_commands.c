#include "shell.h"

/**
 * exit_builtin - A function for exiting the programs
 * @data: a structure pointer
 * Return: 0 else, a number
 */
int exit_builtin(input *data)
{
	int a;

	if (data->tokens[1] != NULL)
	{
		for (a = 0; data->tokens[1][a]; a++)
			if ((data->tokens[1][a] < '0' || data->tokens[1][a] > '9')
				&& data->tokens[1][a] != '+')
			{
				errno = 2;
				return (2);
			}
		errno = _atoi(data->tokens[1]);
	}
	free_full_data(data);
	exit(errno);
}

/**
 * cd_builtin - A function for changing the current directory
 * @data: a structure pointer
 * Return: 0 else, a number
 */
int cd_builtin(input *data)
{
	char *dir_home = list_key("HOME", data), *dir_old = NULL;
	char old_dir[128] = {0};
	int status = 0;

	if (data->tokens[1])
	{
		if (string_compare(data->tokens[1], "-", 0))
		{
			dir_old = list_key("OLDPWD", data);
			if (dir_old)
				status = change_dir(data, dir_old);
			_print(list_key("PWD", data));
			_print("\n");

			return (status);
		}
		else
		{
			return (change_dir(data, data->tokens[1]));
		}
	}
	else
	{
		if (!dir_home)
			dir_home = getcwd(old_dir, 128);

		return (change_dir(data, dir_home));
	}
	return (0);
}

/**
 * change_dir - A function for setting a working directory
 * @data: a structure pointer
 * @new_dir: a path
 * Return: 0 else, a number
 */
int change_dir(input *data, char *new_dir)
{
	char old_dir[128] = {0};
	int err_code = 0;

	getcwd(old_dir, 128);

	if (!string_compare(old_dir, new_dir, 0))
	{
		err_code = chdir(new_dir);
		if (err_code == -1)
		{
			errno = 2;
			return (3);
		}
		key_set("PWD", new_dir, data);
	}
	key_set("OLDPWD", old_dir, data);
	return (0);
}

/**
 * help_builtin - A function to display the current shell environment
 * @data: a structure pointer
 * Return: 0 else, a number
 */
int help_builtin(input *data)
{
	int a, len = 0;
	char *msg[6] = {NULL};

	msg[0] = HELP_MSG;

	if (data->tokens[1] == NULL)
	{
		_print(msg[0] + 6);
		return (1);
	}
	if (data->tokens[2] != NULL)
	{
		errno = E2BIG;
		perror(data->cmd_name);
		return (5);
	}
	msg[1] = HELP_EXIT_MSG;
	msg[2] = HELP_ENV_MSG;
	msg[3] = HELP_SETENV_MSG;
	msg[4] = HELP_UNSETENV_MSG;
	msg[5] = HELP_CD_MSG;

	for (a = 0; msg[a]; a++)
	{
		len = string_length(data->tokens[1]);
		if (string_compare(data->tokens[1], msg[a], len))
		{
			_print(msg[a] + len + 1);
			return (1);
		}
	}
	errno = EINVAL;
	perror(data->cmd_name);
	return (0);
}

/**
 * alias_builtin - A function for removing, adding or showing aliases
* @data: a structure pointer
 * Return: 0 else, a number
 */
int alias_builtin(input *data)
{
	int a = 0;

	if (data->tokens[1] == NULL)
		return (alias_print(data, NULL));

	while (data->tokens[++a])
	{
		if (tally_characters(data->tokens[a], "="))
			op_alias(data->tokens[a], data);
		else
			alias_print(data, data->tokens[a]);
	}

	return (0);
}
