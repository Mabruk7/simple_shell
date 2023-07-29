#include "shell.h"

/**
 * _myhistory - displays history list, starting at 0
 * @info: Structure containing arguments. Maintaining same function prototype
 *  Return: Always 0
 */
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - sets an alias to a string
 * @info: parameter structure
 * @str: alias string
 *
 * Return: Always 0 on success, 1 on error
 */
int unset_alias(info_t *info, char *str)
{
	char *m, c;
	int ret;

	m = _strchr(str, '=');
	if (!m)
		return (1);
	c = *m;
	*m = 0;
	ret = delete_node_at_index(&(info->alias),
		get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*m = c;
	return (ret);
}

/**
 * set_alias - sets alias to a string
 * @info: parameter structure
 * @str: alias string
 *
 * Return: succesful 0, 1 on error
 */
int set_alias(info_t *info, char *str)
{
	char *m;

	m = _strchr(str, '=');
	if (!m)
		return (1);
	if (!*++m)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - makes alias string
 * @node: alias node
 *
 * Return: successful 0, on error 1
 */
int print_alias(list_t *node)
{
	char *m = NULL, *a = NULL;

	if (node)
	{
		m = _strchr(node->str, '=');
		for (a = node->str; a <= m; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - imitates the alias builtin (man alias)
 * @info: place of areguments using same function prototype
 *  Return: Always 0
 */
int _myalias(info_t *info)
{
	int k = 0;
	char *m = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	for (k = 1; info->argv[k]; k++)
	{
		m = _strchr(info->argv[k], '=');
		if (m)
			set_alias(info, info->argv[k]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
	}

	return (0);
}
