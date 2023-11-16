#include "shell.h"

/**
 * interactive - returns true if shell is interactive mode
 * @info: struct address
 *
 * Return: 1 if interactive mode, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @chr: the char to check
 * @delim: the delimeter string
 * Return: 1 if true, 0 if false
 */
int is_delim(char chr, char *delim)
{
	while (*delim)
		if (*delim++ == chr)
			return (1);
	return (0);
}

/**
 *_isalpha - checks for alphabetic character
 *@chr: The character to input
 *Return: 1 if c is alphabetic, 0 otherwise
 */

int _isalpha(int chr)
{
	if ((chr >= 'a' && chr <= 'z') || (chr >= 'A' && chr <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_atoi - converts a string to an integer
 *@stc: the string to be converted
 *Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *stc)
{
	int i, sign = 1, flag = 0, output;
	unsigned int rst = 0;

	i = 0;
	while (stc[i] != '\0' && flag != 2)
	{
		if (stc[i] == '-')
			sign *= -1;

		if (stc[i] >= '0' && stc[i] <= '9')
		{
			flag = 1;
			rst *= 10;
			rst += (stc[i] - '0');
		}
		else if (flag == 1)
		{
			flag = 2;
		}
		i++;
	}

	if (sign == -1)
		output = -rst;
	else
		output = rst;

	return (output);
}
