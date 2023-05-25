#include "main.h"

/**
 * c_dir - a function for changing directory
 * @ags: info parameter
 * Return: 0, else 1
 */
int c_dir(info *ags)
{
	char *dest, *line = ags->line;

	if (!_scmp(line, "c_dir"))
	{
		if (ags->n_tkn == 1)
			dest = _read_env(ags->envp, "HOME", 4);
		else
		{
			line += 3;
			if (!_scmp(line, "-"))
			{
				dest = ags->prev_pwd;
				write(1, dest, _stringlen(dest));
				write(1, "\n", 1);
			}
			else
				dest = line;
		}
		if (chdir(dest) == -1)
		{
		_print("%s: %i: c_dir: an't c_dir to %s\n", ags->s_name, ags->count, dest);
		ags->status = 2;
		}
		else
		{
			free(ags->prev_pwd);
			ags->prev_pwd = _stringdup(ags, &((*(ags->pwd))[4]));
			if (!ags->prev_pwd)
				free_quit(ags);
			new_pwd(ags);
			ags->status = 0;
		}
		return (1);
	}
	return (0);
}

/**
 * new_pwd - a function for changing the working directory
 * @ags: info parameter
 */
void new_pwd(info *ags)
{
	char buffer[250];
	char *pwd = _malloc(ags, 256);

	getcwd(buffer, 250);
	pwd[0] = '\0';
	_stringcat(pwd, "PWD=");
	_stringcat(pwd, buffer);
	free(*(ags->pwd));
	*(ags->pwd) = pwd;
}

/**
 * handle_PWD - a function that gets a directory from the environment
 * @ags: info parameter
 * Return: a pointer
 */
char **handle_PWD(info *ags)
{
	int a;
	char *pwd = NULL;

	for (a = 0; ags->envp[a] != NULL; a++)
	{
		if (_stringcmp(ags->envp[a], "PWD", 3) == 0)
		{
			pwd = _stringdup(ags, ags->envp[a]);
			ags->envp[a] = pwd;
			return (&(ags->envp[a]));
		}
	}
	return (NULL);
}

/**
 * free_quit - a function that frees arguments b4 the program exits
 * @ags: info parameter
 */
void free_quit(info *ags)
{
	if (ags->line)
		free(ags->line);
	if (ags->path)
		free(ags->path);
	if (ags->pwd)
		free(*(ags->pwd));
	if (ags->prev_pwd)
		free(ags->prev_pwd);
	exit(255);
}

/**
 * _malloc - a function that handles malloc.
 * @ags: info parameter
 * @size: a malloced size
 * Return: a buffer.
 */
char *_malloc(info *ags, int size)
{
	char *buff = malloc(size);

	if (!buff)
		free_quit(ags);
	return (buff);
}
