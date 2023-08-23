#include "shell.h"

/**
 * lists_lens - calculate the num of point in the list linked
 * @bob: ptr to start point
 *
 * Return: len of the lists
 */
size_t lists_lens(const list_t *bob)
{
	size_t i = 0;

	while (bob)
	{
		bob = bob->next;
		i++;
	}
	return (i);
}

/**
 * convert_ls_to_strings - provide array of str from list to string
 * @lead: ptr to start point
 *
 * Return: set of str value
 */
char **convert_ls_to_strings(list_t *lead)
{
	list_t *point = lead;
	size_t i = lists_lens(lead), bem;
	char **custom_strs;
	char *str;

	if (!lead || !i)
		return (NULL);
	custom_strs = malloc(sizeof(char *) * (i + 1));
	if (!custom_strs)
		return (NULL);
	for (i = 0; point; point = point->next, i++)
	{
		str = malloc(str_length(point->str) + 1);
		if (!str)
		{
			for (bem = 0; bem < i; bem++)
				free(custom_strs[bem]);
			free(custom_strs);
			return (NULL);
		}

		str = copy_string(str, point->str);
		custom_strs[i] = str;
	}
	custom_strs[i] = NULL;
	return (custom_strs);
}

/**
 * display_lists - display every element in a linked list
 * @bob: ptr to start point
 *
 * Return: len of the lists
 */
size_t display_lists(const list_t *bob)
{
	size_t i = 0;

	while (bob)
	{
		_puts(num_convted(bob->number, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(bob->str ? bob->str : "(nil)");
		_puts("\n");
		bob = bob->next;
		i++;
	}
	return (i);
}

/**
 * node_prefix - retrieve a ptr to the string that has affix as prefix
 * @point: ptr to the first element
 * @affix: str to compare
 * @c: char right after the affix to be matched
 *
 * Return: return a matched point. or return to null
 */
list_t *node_prefix(list_t *point, char *affix, char c)
{
	char *jl = NULL;

	while (point)
	{
		jl = _starts_with(point->str, affix);
		if (jl && ((c == -1) || (*jl == c)))
			return (point);
		point = point->next;
	}
	return (NULL);
}

/**
 * points_index - retrieve the point’s index
 * @lead: ptr to the first element
 * @point: ptr point
 *
 * Return: return index of the point, else -1
 */
ssize_t points_index(list_t *lead, list_t *point)
{
	size_t i = 0;

	while (lead)
	{
		if (lead == point)
			return (i);
		lead = lead->next;
		i++;
	}
	return (-1);
}
