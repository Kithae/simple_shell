#include "main.h"

/**
 * _print - a function for printing.
 * @fmt: the format.
 *
 * Return: total chars.
 */

int _print(const char *fmt, ...)
{
	unsigned int a, length = 0;
	va_list ags;

	if (fmt == NULL)
		return (-1);
	va_start(ags, fmt);
	for (a = 0; fmt[a]; a++)
	{
		if (fmt[a] != '%')
		{
			length += handle_char(fmt[a]);
			continue;
		}
		if ((int)a++ == _stringlen((char *)fmt) - 1)
			return (-1);
		length += specifier(fmt[a], ags);
	}
	va_end(ags);
	return (length);
}

/**
 * handle_dots - a function for handling dots.
 * @line: input.
 * @ags: info parameter.
 */

void handle_dots(char **line, info *ags)
{
	int a = 0, length;
	char *line_c = *line, *buffer;

	if (line_c[0] == '.')
	{
		buffer = mal2(*line, ags, 512);
		buffer[0] = '\0';
		_stringcat(buffer, &((*(ags->pwd))[4]));
		length = _stringlen(buffer);
		while (line_c[a] && line_c[a] != ' ')
		{
			if (line_c[a] == '.' && line_c[a + 1] == '.')
			{
				while (buffer[length - 1] != '/')
					buffer[(length--) - 1] = '\0';
				buffer[(length--) - 1] = '\0';
				a++;
			}
			else if (line_c[a] != '/' && line_c[a] != '.')
			{
				buffer[length++] = '/';
				while (line_c[a] && line_c[a] != '/' && line_c[a] != ' ')
					buffer[length++] = line_c[a++];
				a--;
			}
			a++;
		}
		buffer[length] = '\0';
		if (access(buffer, X_OK) == 0)
		{
			_stringcat(buffer, &line_c[a]);
			free(*line);
			*line = buffer;
		}
	}
}

/**
 * mal2 - a function for handling malloc2.
 * @line: input.
 * @ags: info parameter.
 * @size: a size.
 * * Return: a buffer.
 */

char *mal2(char *line, info *ags, int size)
{
	char *buffer = malloc(size);

	if (!buffer)
	{
		free(line);
		free_quit(ags);
	}
	return (buffer);
}

/**
 * tkn - a function for returning total tokens.
 * @line: input.
* @dlim: a delimiter.
* Return: total split tokens.
*/
int tkn(char *line, char *dlim)
{
	int n_tkn = 0;
	char *string_tkn = _stringtok(line, dlim);

	while (string_tkn)
	{
		string_tkn = _stringtok(NULL, dlim);
		n_tkn++;
	}
	return (n_tkn);
}
