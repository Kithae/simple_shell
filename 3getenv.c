#include "main.h"

/**
 * d_realloc - a function that changes the buffer size.
 * @ptr: a buffer.
 * @prev: the previous buffer size.
 * @curr_size: the current buffer size.
 * Return: a buffer.
*/

void *d_realloc(void *ptr, unsigned int prev, unsigned int curr_size)
{
	char *buffer;
	unsigned int a;

	if (curr_size == prev)
		return (ptr);
	if (curr_size == 0 && ptr != NULL)
	{
		free(ptr);
		return (NULL);
	}
	buffer = malloc(curr_size);
	if (buffer == NULL)
	{
		if (ptr)
			free(ptr);
		return (NULL);
	}
	if (ptr == NULL)
		return (buffer);
	for (a = 0; a < prev && a < curr_size; a++)
	{
		buffer[a] = ((char *) ptr)[a];
	}

	free(ptr);
	return (buffer);
}

/**
 * _atoi - a function that converts strings to integers.
 * @uzi: the string.
 * Return: total numbers
 */

int _atoi(char *uzi)
{
	int a = (_stringlen(uzi) - 1), b, num = 0, power = 1;

	for (b = 0; b <= a; b++)
	{
		if (uzi[a - b] > 47 && uzi[a - b] < 58)
		{
			num += (uzi[a - b] - 48) * power;
			power *= 10;
		}
		else
			return (-1);
	}
	return (num);
}

/**
 * _read_env - a function that gets defined environmental variable.
 * @envp: environmental variables array.
 * @env: the variable.
 * @length: a variable length.
 * Return: a variable, else NULL.
*/

char *_read_env(char **envp, char *env, int length)
{
	int a;

	for (a = 0; envp[a] != NULL; a++)
	{
		if (_stringcmp(envp[a], env, length) == 0)
			return (&envp[a][length + 1]);
	}
	return (NULL);
}

/**
 * _env - a function that checks for environmental variables in an input.
 * @ags: info parameter
 * Return: 1 else, 0
*/
int _env(info *ags)
{
	int a;

	if (reverse_c(ags->line, "env"))
	{
		for (a = 0; ags->envp[a] != NULL; a++)
		{
			write(1, ags->envp[a], _stringlen(ags->envp[a]));
			write(1, "\n", 1);
		}
		ags->status = 0;
		return (1);
	}
	return (0);
}

/**
 * h_realloc - a function that handles realloc.
 * @ags: info parameter
 * @buffer: a buffer
 * @buffer_size: a size.
 * @extra: additional size if needed.
 * @max: a number
 * Return: a buffer
 */
char *h_realloc(info *ags, char *buffer, int *buffer_size,
int extra, int max)
{
	if (*buffer_size <= max)
	{
		buffer = d_realloc(buffer, *buffer_size, *buffer_size + extra);
			if (buffer == NULL)
			{
				free_quit(ags);
			}
		*buffer_size += extra;
	}
	return (buffer);
}
