#include "shell.h"

/**
 **_memset - fills memory with a constant byte
 *@a: the pointer to the memory area
 *@b: the byte to fill *s with
 *@c: the amount of bytes to be filled
 *Return: (a) a pointer to the memory area a
 */
char *_memset(char *a, char b, unsigned int c)
{
	unsigned int i;

	i = 0;
	while (i < c)
	{
		a[i] = b;
		i++;
	}
	return (a);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **t = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(t);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: pointer to previous malloc'ated block
 * @older_size: byte size of previous block
 * @newer_size: byte size of new block
 *
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int older_size, unsigned int newer_size)
{
	char *p;

	if (!ptr)
		return (malloc(newer_size));
	if (!newer_size)
		return (free(ptr), NULL);
	if (newer_size == older_size)
		return (ptr);

	p = malloc(newer_size);
	if (!p)
		return (NULL);

	older_size = older_size < newer_size ? older_size : newer_size;
	while (older_size--)
		p[older_size] = ((char *)ptr)[older_size];
	free(ptr);
	return (p);
}
