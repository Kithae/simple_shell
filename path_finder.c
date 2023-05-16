#include "shell.h"

int analyse_file(char *all_path);

/**
 * link_program - A function that links programs to their paths.
 * @data: a structure pointer
 * Return: 0 else, error
 */
int link_program(input *data)
{
/*finds programs specified by their PATH*/
	int a = 0, f_code = 0;
	char **folder;

	if (!data->cmd_name)
		return (2);

	if (data->cmd_name[0] == '/' || data->cmd_name[0] == '.')
		return (analyse_file(data->cmd_name));

	free(data->tokens[0]);
	data->tokens[0] = concat_str(copy_str("/"), data->cmd_name);
	if (!data->tokens[0])
		return (2);

	folder = tok_path(data);

/*check for empty directory arrays*/
	if (!folder || !folder[0])
	{
		errno = 127;
		return (127);
	}
	for (a = 0; folder[a]; a++)
	{
		folder[a] = concat_str(folder[a], data->tokens[0]);
		f_code = analyse_file(folder[a]);
		if (f_code == 0 || f_code == 126)
		{
			errno = 0;
			free(data->tokens[0]);
			data->tokens[0] = copy_str(folder[a]);
			free_pt_array(folder);
			return (f_code);
		}
	}
	free(data->tokens[0]);
	data->tokens[0] = NULL;
	free_pt_array(folder);
	return (f_code);
}

/**
 * tok_path - A function to parse these paths in their respective directories
 * @data: a structure pointer
 * Return: an array
 */
char **tok_path(input *data)
{
	int a = 0;
	int folder_tally = 2;
	char **tokens = NULL;
	char *PATH;

	PATH = list_key("PATH", data);
	if ((PATH == NULL) || PATH[0] == '\0')
	{
		return (NULL);
	}

	PATH = copy_str(PATH);

	for (a = 0; PATH[a]; a++)
	{
		if (PATH[a] == ':')
			folder_tally++;
	}

	tokens = malloc(sizeof(char *) * folder_tally);

	a = 0;
	tokens[a] = copy_str(_stringtok(PATH, ":"));
	while (tokens[a++])
	{
		tokens[a] = copy_str(_stringtok(NULL, ":"));
	}

	free(PATH);
	PATH = NULL;
	return (tokens);

}

/**
 * analyse_file - A function to confirm directories and file execution
* permissions if these are available.
* @all_path: a file name pointer
 * Return: 0 else, error.
 */
int analyse_file(char *all_path)
{
	struct stat sb;

	if (stat(all_path, &sb) != -1)
	{
		if (S_ISDIR(sb.st_mode) ||  access(all_path, X_OK))
		{
			errno = 126;
			return (126);
		}
		return (0);
	}
	errno = 127;
	return (127);
}
