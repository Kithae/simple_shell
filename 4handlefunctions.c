#include "main.h"

/**
 * handle_char - a function that prints characters.
 * @c: a character
 * Return: total length.
 */

int handle_char(char c)
{
	return (write(2, &c, 1));
}

/**
 * handle_string - a function that prints strings.
 * @s: a string
 * Return: length.
 */

int handle_string(char *s)
{
	return (write(2, s, _stringlen(s)));
}

/**
 * handle_number - a function that prints numbers
 * @n: a number
 */

void handle_number(int n)
{
	unsigned int x;

	if (n < 0)
	{
		x = -n;
		handle_char('-');
	}
	else
		x = n;

	if (x / 10)
		handle_number(x / 10);

	handle_char((x % 10) + '0');
}

/**
 * _length - a function that returns the length of a number
 * @n: a number
 * Return: length.
 */

int _length(int n)
{
	int length = 1;

	handle_number(n);
	if (n < 0)
		length++;
	while (n /= 10)
		length++;

	return (length);
}

/**
 * specifier - a function that prints arguments
 * @c: a specifier
 * @ags: an argument
 * Return: length.
 */

int specifier(char c, va_list ags)
{
	int length = 0;
	char *uzi;

	if (c == 'c')
		length += handle_char(va_arg(ags, int));
	else if (c == 's')
	{
		uzi = va_arg(ags, char *);
		length += handle_string(STRING);
	}
	else if (c == 'i' || c == 'd')
		length += _length(va_arg(ags, int));
	else if (c == '%')
		length += handle_char('%');
	else
	{
		length += handle_char('%');
		length += handle_char(c);
	}
	return (length);
}
