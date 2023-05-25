#include "main.h"

#define D(i) (*d)[i]
/**
* input - a function that checks for arrows.
* @ags: info parameter
* @arw: 1
* @sm:  can be 0 or 1
* Return: 0, else 1
*/
int input(info *ags, int arw, int *sm)
{
	ssize_t chek;

	chek = _readline(ags);
	if (chek == -1)
	{
		if (isatty(STDIN_FILENO) && arw && !ags->file)
			write(1, "\n", 1);
		close(ags->file);
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
	if (*sm)
		ags->count--;
	if (ags->line[chek - 1] == '\n')
	{
		ags->line[chek - 1] = '\0';
	}
	if (ags->line[chek - 1] == ';')
	{
		ags->line[chek - 1] = '\0';
		*sm = 1;
		return (0);
	}
	*sm = 0;
	return (1);
}

/**
 * _readline - a function that reads lines
 * @ags: info parameter
 * Return: read characters.
*/
ssize_t _readline(info *ags)
{
	size_t a = 0;
	ssize_t chek_line;
	char *buffer;
	int buffer_size = 10240;

	if (&(ags->line) == NULL)
		return (-1);
	buffer = _malloc(ags, buffer_size + 1);
	if (ags->line)
	{
		free(ags->line);
		ags->line = NULL;
	}
	while ((chek_line = read(ags->file, buffer + a, 1)) > 0)
	{
		a++;
		buffer = h_realloc(ags, buffer, &buffer_size, 2048, a);
		if (buffer[a - 1] == '\n' || buffer[a - 1] == ';')
			break;
	}
	if (chek_line < 0 || (!chek_line && !a))
	{
		free(buffer);
		return (-1);
	}
	if (chek_line != 8)
		buffer[a] = '\0';
	ags->line = buffer;
	return (a);
}

/**
 * check_input - a function that checks for special characters
* @ags: info parameter
 *
 * Return: 1
*/
int check_input(info *ags)
{
char *buffer, *symbol, *start, *hash = _stringchr(ags->line, '#');
int buffer_size = 10240;

if (hash && ((hash != ags->line && *(hash - 1) == ' ') || hash == ags->line))
	*hash = '\0';
buffer = _malloc(ags, buffer_size);
symbol = _stringchr(ags->line, '$');
start = ags->line;
buffer[0] = '\0';
while (symbol)
{
	buffer = h_realloc(ags, buffer, &buffer_size,
	1024, _stringlen(buffer) + symbol - start);
	_scat(buffer, start, symbol - start);
	check_symbol(buffer, &symbol, ags);
	start = symbol;
	symbol = _stringchr(start, '$');
}
buffer = h_realloc(ags, buffer, &buffer_size,
128, _stringlen(buffer) + _stringlen(start));
_stringcat(buffer, start);
space(&buffer, ags);
handle_dots(&buffer, ags);
free(ags->line);
ags->line = buffer;
return (buffer[0] == '\0');
}

/**
 * check_symbol - a function that handles the $ sign.
 * @buffer: an input.
 * @d: an input.
 * @ags: info parameter
*/
void check_symbol(char *buffer, char **d, info *ags)
{
	char num[10], *env;
	int a = 0;

	(*d)++;
	if (D(0) == '$' || D(0) == '?')
	{
		if (D(0) == '$')
			t_string(num, ags->pid);
		else
			t_string(num, ags->status);
		_stringcat(buffer, num);
		(*d)++;
	}
	else
	{
		while (D(a) && D(a) != ' ' && D(a) != '#' && D(a) != '$' && D(a) != '/')
			a++;
		if (!a)
			_stringcat(buffer, "$");
		else
		{
			env = _read_env(ags->envp, *d, a);
			if (env)
				_stringcat(buffer, env);
			*d += a;
		}
	}
}

/**
 * space - a function that checks for extra spaces
 * @line: input
 * @ags: info parameter
*/
void space(char **line, info *ags)
{
	int a = 0, b = 0;
	char *buffer = malloc(_stringlen(*line) + 1);

	if (buffer == NULL)
	{
		free(*line);
		free_quit(ags);
	}
	while ((*line)[a] && (*line)[a] == ' ')
		a++;
	while ((*line)[a])
	{
		if ((*line)[a] == ' ')
		{
			buffer[b] = ' ';
			b++;
			while ((*line)[a] == ' ')
				a++;
		}
		else
		{
			buffer[b] = (*line)[a];
			a++;
			b++;
		}
	}
	if (b && buffer[b - 1] == ' ')
		b--;
	buffer[b] = '\0';
	free(*line);
	*line = buffer;
}
