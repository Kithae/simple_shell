#include "shell.h"
/**
 * l_to_str - a function for converting numbers to strings.
 * @number: a number.
 * @string: a buffer.
 * @base: a number converter
 *
 * Return: Nothing.
 */

void l_to_str(long number, char *string, int base)
{
	int a = 0, neg = 0;
	long c = number;
	char l[] = {"0123456789abcdef"};

	if (c == 0)
		string[a++] = '0';
	if (string[0] == '-')
		neg = 1;
	while (c)
	{
		if (c < 0)
			string[a++] = l[-(c % base)];
		else
			string[a++] = l[c % base];
		c /= base;
	}
	if (neg)
		string[a++] = '-';
	string[a] = '\0';
	string_reverse(string);
}
/**
 * _atoi - a function to now convert those strings to integers.
 *
 * @s: a pointer.
 * Return: a string int else, 0.
 */

int _atoi(char *s)
{
	int a = 1;
	unsigned int n = 0;

	while (!('0' <= *s && *s <= '9') && *s != '\0')
	{
		if (*s == '-')
			a *= -1;
		if (*s == '+')
			a *= +1;
		s++;
	}
	while ('0' <= *s && *s <= '9' && *s != '\0')
	{
		n = (n * 10) + (*s - '0');
		s++;
	}
	return (n * a);
}
/**
 * tally_characters - a function to finally count
 * character coincidences in the string.
 * @string: a pointer.
 * @character: a string
 * Return: int else, 0.
 */

int tally_characters(char *string, char *character)
{
	int a = 0, tally = 0;

	for (; string[a]; a++)
	{
		if (string[a] == character[0])
			tally++;
	}
	return (tally);
}
