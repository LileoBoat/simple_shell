#include "shell.h"

/**
 * get_env_var - obtain a copy of the str array containing environ
 * @info: args structure for maintaining consistent funct prototyp
 *
 * Return: return 0 always.
 */
char **get_env_var(info_t *info)
{
	if (!info->environ || info->custom_envchged)
	{
		info->environ = convert_ls_to_strings(info->my_environ);
		info->custom_envchged = 0;
	}

	return (info->environ);
}

/**
 * unset_variable_env - clear the env variables
 * @info: potential args structure, for consistent func prototyp
 * @variable_name: strings attributed of my_environ identified as variable_name
 *  Return: return 1 for delete, return 0 otherwise
 */
int unset_variable_env(info_t *info, char *variable_name)
{
	list_t *point = info->my_environ;
	size_t i = 0;
	char *jl;

	if (!point || !variable_name)
		return (0);

	while (point)
	{
		jl = _starts_with(point->str, variable_name);
		if (jl && *jl == '=')
		{
			info->custom_envchged = del_env_node_index(&(info->my_environ), i);
			i = 0;
			point = info->my_environ;
			continue;
		}
		point = point->next;
		i++;
	}
	return (info->custom_envchged);
}

/**
 * _set_env - it initial the new env var or switch the previous one
 * @info: potential args structure, for consistent func prototyp
 * @variable_name: strings attributed of my_environ identified as variable_name
 * @var_val: string content associated with var_val property in the
 * my_environ variable identified by variable_name
 *  Return: Always 0
 */
int _set_env(info_t *info, char *variable_name, char *var_val)
{
	char *buffer = NULL;
	list_t *point;
	char *jl;

	if (!variable_name || !var_val)
		return (0);

	buffer = malloc(str_length(variable_name) + str_length(var_val) + 2);
	if (!buffer)
		return (1);
	copy_string(buffer, variable_name);
	_str_concat(buffer, "=");
	_str_concat(buffer, var_val);
	point = info->my_environ;
	while (point)
	{
		jl = _starts_with(point->str, variable_name);
		if (jl && *jl == '=')
		{
			free(point->str);
			point->str = buffer;
			info->custom_envchged = 1;
			return (0);
		}
		point = point->next;
	}
	append_point(&(info->my_environ), buffer, 0);
	free(buffer);
	info->custom_envchged = 1;
	return (0);
}
