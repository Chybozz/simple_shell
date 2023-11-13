#include "shell.h"

/**
 * is_chain - test if current char in buffer is a chain delimeter
 * @info: the parameter struct
 * @buff: the char buffer
 * @s: address of current position in buff
 *
 * Return: 1 if chain delimeter, 0 if not
 */
int is_chain(info_t *info, char *buff, size_t *s)
{
	size_t j = *s;

	if (buff[j] == '|' && buff[j + 1] == '|')
	{
		buff[j] = 0;
		j++;
		info->cmd_buff_type = CMD_OR;
	}
	else if (buff[j] == '&' && buff[j + 1] == '&')
	{
		buff[j] = 0;
		j++;
		info->cmd_buff_type = CMD_AND;
	}
	else if (buff[j] == ';') /* found end of this command */
	{
		buff[j] = 0; /* replace semicolon with null */
		info->cmd_buff_type = CMD_CHAIN;
	}
	else
		return (0);
	*s = j;
	return (1);
}

/**
 * check_chain - checks we should continue chaining based on last status
 * @info: the parameter struct
 * @buff: the char buffer
 * @s: address of current position in buf
 * @i: starting position in buff
 * @len: length of buff
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buff, size_t *s, size_t i, size_t len)
{
	size_t j = *s;

	if (info->cmd_buff_type == CMD_AND)
	{
		if (info->status)
		{
			buff[i] = 0;
			j = len;
		}
	}
	if (info->cmd_buff_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			j = len;
		}
	}

	*s = j;
}

/**
 * sub_alias - replaces an aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 if not
 */
int sub_alias(info_t *info)
{
	int i;
	list_t *node;
	char *p;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		p = _strchr(node->str, '=');
		if (!p)
			return (0);
		p = _strdup(p + 1);
		if (!p)
			return (0);
		info->argv[0] = p;
	}
	return (1);
}

/**
 * sub_vars - replaces vars in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 if not
 */
int sub_vars(info_t *info)
{
	int i;
	list_t *node;

	i = 0;

	while (info->argv[i])
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			sub_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			sub_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			sub_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		sub_string(&info->argv[i], _strdup(""));
		i++;
	}
	return (0);
}

/**
 * sub_string - replaces string
 * @older: address of old string
 * @newer: new string
 *
 * Return: 1 if replaced, 0 if not
 */
int sub_string(char **older, char *newer)
{
	free(*older);
	*older = newer;
	return (1);
}
