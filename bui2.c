#include "shell.h"

/**
 * _mylogs - it identifies command logs with lines numbers starting from 0
 * @info: this argument holder  for agreeing function pointers prototype.
 * Return: return 0 always
 */
int _mylogs(info_t *info)
{
	display_lists(info->logs);
	return (0);
}

/**
 * discard_alias - it allocates a string as an alias
 * @info: struct for parameter holder
 * @str: the alias for the string
 *
 * Return: return 0 on success, otherwise 1 for error
 */
int discard_alias(info_t *info, char *str)
{
	char *jl, c;
	int und;

	jl = custom_strchar(str, '=');
	if (!jl)
		return (1);
	c = *jl;
	*jl = 0;
	und = del_env_node_index(&(info->alias),
													 points_index(info->alias, node_prefix(info->alias, str, -1)));
	*jl = c;
	return (und);
}

/**
 * assign_alias - it allocates the alias as a string
 * @info: struct for parameter holder
 * @str: the alias for the string
 *
 * Return: return 0 on success, otherwise 1 for error
 */
int assign_alias(info_t *info, char *str)
{
	char *jl;

	jl = custom_strchar(str, '=');
	if (!jl)
		return (1);
	if (!*++jl)
		return (discard_alias(info, str));

	discard_alias(info, str);
	return (append_point(&(info->alias), str, 0) == NULL);
}

/**
 * list_alias - list another string
 * @point: the alias point
 *
 * Return: return 0 on success, else 1 for error
 */
int list_alias(list_t *point)
{
	char *jl = NULL, *a = NULL;

	if (point)
	{
		jl = custom_strchar(point->str, '=');
		for (a = point->str; a <= jl; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(jl + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_aliasid - responsible for copying  alias built-in function(man alias)
 * @info: argument structure for keeping function prototype consistency.
 *  Return: return 0 always
 */
int my_aliasid(info_t *info)
{
	int i = 0;
	char *jl = NULL;
	list_t *point = NULL;

	if (info->argument_count == 1)
	{
		point = info->alias;
		while (point)
		{
			list_alias(point);
			point = point->next;
		}
		return (0);
	}
	for (i = 1; info->cust_avect[i]; i++)
	{
		jl = custom_strchar(info->cust_avect[i], '=');
		if (jl)
			assign_alias(info, info->cust_avect[i]);
		else
			list_alias(node_prefix(info->alias, info->cust_avect[i], '='));
	}

	return (0);
}
