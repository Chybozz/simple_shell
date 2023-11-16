#include "shell.h"

/**
 * add_node - adds a node to the start of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @vals: node index used by history
 *
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int vals)
{
	list_t *newer_head;

	if (!head)
		return (NULL);
	newer_head = malloc(sizeof(list_t));
	if (!newer_head)
		return (NULL);
	_memset((void *)newer_head, 0, sizeof(list_t));
	newer_head->vals = vals;
	if (str)
	{
		newer_head->str = _strdup(str);
		if (!newer_head->str)
		{
			free(newer_head);
			return (NULL);
		}
	}
	newer_head->next = *head;
	*head = newer_head;
	return (newer_head);
}

/**
 * add_node_end - adds a node to the end of the list
 * @head: address of pointer to head node
 * @str: str field of node
 * @val: node index used by history
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int vals)
{
	list_t *newer_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	newer_node = malloc(sizeof(list_t));
	if (!newer_node)
		return (NULL);
	_memset((void *)newer_node, 0, sizeof(list_t));
	newer_node->vals = vals;
	if (str)
	{
		newer_node->str = _strdup(str);
		if (!newer_node->str)
		{
			free(newer_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = newer_node;
	}
	else
		*head = newer_node;
	return (newer_node);
}

/**
 * print_list_str - prints only the str element of a list_t linked list
 * @k: pointer to first node
 *
 * Return: size of list
 */
size_t print_list_str(const list_t *k)
{
	size_t i = 0;

	while (k)
	{
		_puts(k->str ? k->str : "(nil)");
		_puts("\n");
		k = k->next;
		i++;
	}
	return (i);
}

/**
 * delete_node_at_index - deletes node at given index
 * @head: address of pointer to first node
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *previous_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	node = *head;
	while (node != NULL)
	{
		if (i == index)
		{
			previous_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		i++;
		previous_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - frees all nodes of a list
 * @head_ptr: address of pointer to head node
 *
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *nxt_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node != NULL)
	{
		nxt_node = node->next;
		free(node->str);
		free(node);
		node = nxt_node;
	}
	*head_ptr = NULL;
}
