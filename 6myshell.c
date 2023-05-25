#include "main.h"

/**
 * _cmd_ - a function that handles commands in the path
 * @ags: info parameter
 * Return: 0 or 127
 */
int _cmd_(info *ags)
{
	int a;
	char *path = ags->path;

	if (_quit_(ags) || c_dir(ags))
		return (ags->status);
	if (ags->line[0] == '/')
	{
		if (access(ags->line, X_OK) == 0)
		{
			if (!_env(ags))
				return (_xeve(ags, ags->line));
			return (0);
		}
	_print("%s: %i: %s: not found\n", ags->s_name, ags->count, ags->line);
	}
	else
	{
		for (a = 0; a < ags->n_path; a++)
		{
			char buffer[500] = "";

			_stringcat(buffer, path);
			_stringcat(buffer, "/");
			_stringcat(buffer, ags->line);
			if (access(buffer, X_OK) == 0)
			{
				if (!_env(ags))
					return (_xeve(ags, buffer));
				return (0);
			}
			path += _stringlen(path) + 1;
		}
	_print("%s: %i: %s: not found\n", ags->s_name, ags->count, ags->line);
	}
	ags->status = 127;
	return (127);
}

/**
* _xeve - a function that executes the above commands
* @ags: info parameter
* @buff: input
* Return: a status.
*/
int _xeve(info *ags, char *buff)
{
	int a;
	char **arg_v, *line = ags->line;
	pid_t id = fork();

	if (!id)
	{
		if (reverse_c(ags->line, "pwd"))
		{
			arg_v = malloc(16);
			if (arg_v == NULL)
				exit(255);
			arg_v[0] = ags->line;
			arg_v[1] = NULL;
		}
		else
		{
			arg_v = malloc(8 * (ags->n_tkn + 1));
			if (arg_v == NULL)
				exit(255);
			for (a = 0; a < ags->n_tkn; a++)
			{
				arg_v[a] = line;
				line += _stringlen(line) + 1;
			}
			arg_v[a] = NULL;
		}
		execve(buff, arg_v, NULL);
		free(arg_v);
		exit(ags->status);
	}
	wait(&(ags->status));
	ags->status = WEXITSTATUS(ags->status);
	return (ags->status);
}

/**
 * _quit_ - a function that handles shell exit status.
 * @ags: info parameter
 * Return: 0 else, 1
*/
int _quit_(info *ags)
{
int length;

if (!_scmp(ags->line, "exit"))
{
	if (ags->n_tkn > 1)
	{
	length = _stringlen(ags->line) + 1;
	ags->status = _atoi(ags->line + length);
	}
	if (ags->status != -1)
	{
		if (ags->line)
			free(ags->line);
		if (ags->path)
			free(ags->path);
		if (ags->pwd)
			free(*(ags->pwd));
		if (ags->prev_pwd)
			free(ags->prev_pwd);
		exit(ags->status);
	}
	_print("%s: %i: exit: Illegal number: %s\n",
	ags->s_name, ags->count, ags->line + length);
	ags->status = 2;
	return (1);
}
	return (0);
}

/**
* cmd_c - a function that handles signals
* @signal: a signal
*/
void cmd_c(int signal)
{
	if (signal == SIGINT)
	{
		write(1, "\n=> ", 4);
	}
}

/**
* main - a function that defines the program starting point
* @argc: number of argument to the program
* @argv: an argument array
* @envp: environmental variables array
* Return: 0;
*/
int main(int argc, char **argv, char **envp)
{
	info ags;
	int  arw = 1, sm = 0;

	ags.line = NULL, ags.path = NULL;
	ags.envp = envp;
	ags.pwd = NULL;
	ags.prev_pwd = NULL;
	ags.path = _stringdup(&ags, _read_env(envp, "PATH", 4));
	ags.pwd = handle_PWD(&ags);
	if (ags.pwd)
		ags.prev_pwd = _stringdup(&ags, &((*ags.pwd)[4]));
	ags.s_name = argv[0];
	ags.count = 0;
	ags.status = 0;
	ags.file = 0;
	ags.pid = (int)getpid();
	ags.n_path = tkn(ags.path, ":");
	if (argc > 1)
	{
		ags.file = open(argv[1], O_RDONLY);
		if (ags.file == -1)
		{
			_print("%s: 0: cannot open %s: No such file\n", argv[0], argv[1]);
			exit(2);
		}
	}
while (1)
{
	if (isatty(STDIN_FILENO) && arw && !ags.file)
		write(1, "=> ", 3);
	signal(SIGINT, cmd_c);
	ags.count++;
	arw = input(&ags, arw, &sm);
	if (check_input(&ags))
		continue;
	ags.n_tkn = tkn(ags.line, " ");
	if (_cmd_(&ags) == 255)
		free_quit(&ags);
}
return (0);
}
