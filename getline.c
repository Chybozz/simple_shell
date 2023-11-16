#include "shell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 *
 * Return: bytes read
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t rd = 0;
	size_t len_p = 0;

	if (!*len) /* if nothing left in the buffer, fill it */
	{
		/*bfree((void **)info->cmd_buf);*/
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		rd = getline(buf, &len_p, stdin);
#else
		rd = _getline(info, buf, &len_p);
#endif
		if (!(rd <= 0))
		{
			if ((*buf)[rd - 1] == '\n')
			{
				(*buf)[rd - 1] = '\0'; /* remove trailing newline */
				rd--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*len = rd;
				info->cmd_buff = buf;
			}
		}
	}
	return (rd);
}

/**
 * get_input - gets a line minus the newline
 * @info: parameter struct
 *
 * Return: bytes read
 */
ssize_t get_input(info_t *info)
{
	static char *buf; /* the ';' command chain buffer */
	static size_t i, j, len;
	ssize_t rd = 0;
	char **buf_pr = &(info->arg), *pr;

	_putchar(BUFF_FLUSH);
	rd = input_buf(info, &buf, &len);
	if (rd == -1) /* EOF */
		return (-1);
	if (len)	/* we have commands left in the chain buffer */
	{
		j = i; /* init new iterator to current buf position */
		pr = buf + i; /* get pointer for return */

		check_chain(info, buf, &j, i, len);
		for (; j < len; j++) /* iterate to semicolon or end */
		{
			if (is_chain(info, buf, &j))
				break;
		}

		i = j + 1; /* increment past nulled ';'' */
		if (i >= len) /* reached end of buffer? */
		{
			len = 0; /* reset length */
			i = len; /* reset position */
			info->cmd_buff_type = CMD_NORM;
		}

		*buf_pr = pr; /* pass back pointer to current command position */
		return (_strlen(pr)); /* return length of current command */
	}

	*buf_pr = buf; /* else not a chain, pass back buffer from _getline() */
	return (rd); /* return length of buffer from _getline() */
}

/**
 * read_buf - reads a buffer
 * @info: parameter struct
 * @buf: buffer
 * @m: size
 *
 * Return: rd
 */
ssize_t read_buf(info_t *info, char *buf, size_t *m)
{
	ssize_t rd = 0;

	if (*m)
		return (0);
	rd = read(info->readfd, buf, READ_BUFF_SIZE);
	if (rd >= 0)
		*m = rd;
	return (rd);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: s
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUFF_SIZE];
	static size_t i, len;
	size_t f;
	ssize_t r = 0, z = 0;
	char *pr = NULL, *new_pr = NULL, *t;

	pr = *ptr;
	if (pr && length)
		z = *length;
	if (i == len)
	{
		len = 0;
		i = len;
	}

	r = read_buf(info, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);

	t = _strchr(buf + i, '\n');
	f = t ? 1 + (unsigned int)(t - buf) : len;
	new_pr = _realloc(pr, z, z ? z + f : f + 1);
	if (!new_pr) /* MALLOC FAILURE! */
		return (pr ? free(pr), -1 : -1);

	if (z)
		_strncat(new_pr, buf + i, f - i);
	else
		_strncpy(new_pr, buf + i, f - i + 1);

	z += f - i;
	i = f;
	pr = new_pr;

	if (length)
		*length = z;
	*ptr = pr;
	return (z);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUFF_FLUSH);
}
