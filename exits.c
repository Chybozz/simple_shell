#include "shell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination string to be copied to
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: the concatenated string
 */
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while (j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 **_strncat - concatenates two strings
 *@fstr: the first string
 *@sstr: the second string
 *@n: the amount of bytes to be maximally used
 *Return: the concatenated string
 */
char *_strncat(char *fstr, char *sstr, int n)
{
	int i, j;
	char *s = fstr;

	i = 0;
	j = 0;
	while (fstr[i] != '\0')
		i++;
	while (sstr[j] != '\0' && j < n)
	{
		fstr[i] = sstr[j];
		i++;
		j++;
	}
	if (j < n)
		fstr[i] = '\0';
	return (s);
}

/**
 **_strchr - locates a character in a string
 *@strg: the string to be parsed
 *@chr: the character to look for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *strg, char chr)
{
	do {
		if (*strg == chr)
			return (strg);
	} while (*strg++ != '\0');

	return (NULL);
}
