#include "main.h"

/**
 * _stringlen - a function that determines string length.
 * @s: a string.
 * Return: the length.
 */

int _stringlen(char *s)
{
	int a = 0;

	while (s[a] != 0)
	{
		a++;
	}

	return (a);
}

/**
 * _stringcat - a function that concatenates strings.
 * @dest: a string.
 * @src: a string.
 * Return: a pointer.
 */

char *_stringcat(char *dest, char *src)
{
	int dest_len = _stringlen(dest), a = 0;

	while (src[a] != '\0')
	{
		dest[dest_len + a] = src[a];
		a++;
	}
	dest[dest_len + a] = '\0';
	return (dest);
}

/**
 *_scmp - a function that compares strings.
 *@uzi1: 1st string.
 *@uzi2: 2nd string.
 * Return: 0.
 */

int _scmp(char *uzi1, char *uzi2)
{
	int a = 0;

	while (uzi1[a] != 0 || uzi2[a] != 0)
	{
		if (uzi1[a] != uzi2[a])
			return (uzi1[a] - uzi2[a]);
		a++;
	}
	return (0);
}

/**
 * t_string - a function that changes numbers to strings.
 * @uzi: a buffer.
 * @num: an integer.
*/

void t_string(char *uzi, int num)
{
	int a, length = 0, n = num;

	if (!n)
	{
		uzi[0] = '0';
		uzi[1] = '\0';
		return;
	}
	while (n)
	{
		length++;
		n /= 10;
	}
	for (a = 0; a < length; a++)
	{
		uzi[length - (a + 1)] = num % 10 + '0';
		num /= 10;
	}
	uzi[length] = '\0';
}

/**
 * reverse_c - a function that compares reversed strings
 * @uzi1: 1st string.
 * @uzi2: 2nd string
 * Return: 1 else, 0
*/
int reverse_c(char *uzi1, char *uzi2)
{
	int l1 = (_stringlen(uzi1) - 1), l2 = (_stringlen(uzi2) - 1), a;

	if (l2 > l1)
		return (0);
	for (a = l2; a >= 0; a--)
	{
		if (uzi1[l1] != uzi2[a])
			return (0);
		l1--;
	}
	return (1);
}
