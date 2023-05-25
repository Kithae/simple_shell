#include "main.h"

/**
* _stringtok - a function that splits string.
* @uzi: a string.
* @dlim: a delimiter
* Return: a token.
*/
char *_stringtok(char *uzi, const char *dlim)
{
	static char *last;
	char *tkn;

	if (uzi != NULL)
	{
		last = uzi;
	}
	else if (last == NULL)
	{
		return (NULL);
	}
	tkn = last;
	while (*last != '\0')
	{
		if (*dlim == *last)
		{
			*last = '\0';
			last++;
			return (tkn);
		}
		last++;
	}
	last = NULL;
	return (tkn);
}

/**
* _stringdup - a function that returns a pointer
 * @uzi: a string.
 * @ags: info parameter
 * Return: a pointer.
*/
char *_stringdup(info *ags, char *uzi)
{
	char *copy;
	int a, length;

	if (!uzi)
		return (NULL);
	length = _stringlen(uzi);
	copy = _malloc(ags, length + 1);
	for (a = 0; a <= length; a++)
	{
		copy[a] = uzi[a];
	}
	return (copy);
}

/**
* _stringcmp - a function that compares strings
* @uzi1: 1st  string.
 * @uzi2: 2nd string.
 * @n: bytes.
 * Return: 0.
*/
int _stringcmp(const char *uzi1, const char *uzi2, size_t n)
{
	while (n-- && (*uzi1 != '\0' || *uzi2 != '\0'))
	{
		if (*uzi1 != *uzi2)
			return (*uzi1 - *uzi2);
		uzi1++;
		uzi2++;
	}
	return (0);
}

/**
* _stringchr - a function that locates string characters.
 * @uzi: a string.
 * @c: a character.
 * Return: a pointer else, NULL.
 */
char *_stringchr(char *uzi, char c)
{
	int a = 0;

	while (a < _stringlen(uzi))
	{
		if (uzi[a] == c)
		{
			return (uzi + a);
		}
		a++;
	}
	return (NULL);
}
/**
* _scat - a function that concatenates a string.
 *@dest: a string.
 *@src: a string.
 *@n: bytes.
*Return: a string.
*/
char *_scat(char *dest, char *src, int n)
{
	int dest_length = _stringlen(dest), a = 0;

	while (a < n && src[a] != '\0')
	{
		dest[dest_length + a] = src[a];
		a++;
	}
	dest[dest_length + a] = '\0';
	return (dest);
}
