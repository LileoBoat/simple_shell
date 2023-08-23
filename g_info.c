#include "shell.h"

/**
 * ri_struct - establishes an info_t structure
 * @info: address-related structure
 */
void ri_struct(info_t *info)
{
	info->my_cst_argv = NULL;
	info->cust_avect = NULL;
	info->evec_path = NULL;
	info->argument_count = 0;
}

/**
 * my_setinfo -establishes an info_t structure
 * @info: address-related structure
 * @arg_v: agrv array
 */
void my_setinfo(info_t *info, char **arg_v)
{
	int i = 0;

	info->file_name = arg_v[0];
	if (info->my_cst_argv)
	{
		info->cust_avect = _mystringtow(info->my_cst_argv, " \t");
		if (!info->cust_avect)
		{

			info->cust_avect = malloc(sizeof(char *) * 2);
			if (info->cust_avect)
			{
				info->cust_avect[0] = duplicat_str(info->my_cst_argv);
				info->cust_avect[1] = NULL;
			}
		}
		for (i = 0; info->cust_avect && info->cust_avect[i]; i++)
			;
		info->argument_count = i;

		apply_repalias(info);
		perform_repvars(info);
	}
}

/**
 * rel_mem - clears mems used by info_t structure field
 * @info: address-related structure
 * @rel_all_resources: return true, if rel_all_resources are being
 * freed.
 */
void rel_mem(info_t *info, int rel_all_resources)
{
	allocate_custom_free(info->cust_avect);
	info->cust_avect = NULL;
	info->evec_path = NULL;
	if (rel_all_resources)
	{
		if (!info->command_buffer)
			free(info->my_cst_argv);
		if (info->my_environ)
			allocate_free_list(&(info->my_environ));
		if (info->logs)
			allocate_free_list(&(info->logs));
		if (info->alias)
			allocate_free_list(&(info->alias));
		allocate_custom_free(info->environ);
		info->environ = NULL;
		free_buffer((void **)info->command_buffer);
		if (info->inputdesc > 2)
			close(info->inputdesc);
		_putchar(BUF_FLUSH);
	}
}
