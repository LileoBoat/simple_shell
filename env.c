#include "shell.h"

/**
 * _customenv - this will show the current domain
 * @info: argument holder for agreeing function prototypes
 * Return: return 0 always
 */
int _customenv(info_t *info)
{
	display_list_str(info->my_environ);
	return (0);
}

/**
 * _getenvr - It retrieves the value of a variable from the environment.
 * @info: data structure for saving possible arguments, used for preservation
 * @id_name: the surrounding variable recognition.
 *
 * Return: retrieves the worth of the surrounding variable
 */
char *_getenvr(info_t *info, const char *id_name)
{
	list_t *point = info->my_environ;
	char *jl;

	while (point)
	{
		jl = _starts_with(point->str, id_name);
		if (jl && *jl)
			return (jl);
		point = point->next;
	}
	return (NULL);
}

/**
 * _configenv - this will make or update the variable environ.
 * @info: this is the argument structure for preserving function
 * environment prototype.
 *  Return: return 0 always.
 */
int _configenv(info_t *info)
{
	if (info->argument_count != 3)
	{
		_my_eputs("Invalid argument quant\n");
		return (1);
	}
	if (_set_env(info, info->cust_avect[1], info->cust_avect[2]))
		return (0);
	return (1);
}

/**
 * unset_env_vir - removes the variable from the surrounding
 * @info: this argument structure for  agreeing prototype function.
 *  Return: return 0 always.
 */
int unset_env_vir(info_t *info)
{
	int i;

	if (info->argument_count == 1)
	{
		_my_eputs("Inadequate arguments.\n");
		return (1);
	}
	for (i = 1; i <= info->argument_count; i++)
		unset_variable_env(info, info->cust_avect[i]);

	return (0);
}

/**
 * build_env_list - this will make a linked list of environment variables
 * @info: argument structure for preserving consistent prototype function.
 * Return: return 0 always.
 */
int build_env_list(info_t *info)
{
	list_t *point = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		append_point(&point, environ[i], 0);
	info->my_environ = point;
	return (0);
}
