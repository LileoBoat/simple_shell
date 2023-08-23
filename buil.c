#include "shell.h"

/**
 * exit_now - this ends the shell
 * @info: this is the parameter holder that keeps  consistent
 * function prototypes
 *  Return: ends with a unique exit code (0) if info.cust_avect[0] != "exit"
 */
int exit_now(info_t *info)
{
	int exitstatus;

	if (info->cust_avect[1]) /* if exit argument exists */
	{
		exitstatus = stringtoint(info->cust_avect[1]);
		if (exitstatus == -1)
		{
			info->stat = 2;
			report_err(info, "Invalid value: ");
			_my_eputs(info->cust_avect[1]);
			_eput_char('\n');
			return (1);
		}
		info->e_number = stringtoint(info->cust_avect[1]);
		return (-2);
	}
	info->e_number = -1;
	return (-2);
}

/**
 * custom_cd - it changes process'sh_cke current directory
 * @info: this is the argument structure to repair function prototype.
 *  Return: Always return 0
 */
int custom_cd(info_t *info)
{
	char *sh_cke, *directory, _buff[1024];
	int cd_result;

	sh_cke = getcwd(_buff, 1024);
	if (!sh_cke)
		_puts("TBD: -Error msg in getcwd-:\n");
	if (!info->cust_avect[1])
	{
		directory = _getenvr(info, "HOME=");
		if (!directory)
			cd_result = /* TBD: what do you want? */
					chdir((directory = _getenvr(info, "PWD=")) ? directory : "/");
		else
			cd_result = chdir(directory);
	}
	else if (my_string_cmp(info->cust_avect[1], "-") == 0)
	{
		if (!_getenvr(info, "OLDPWD="))
		{
			_puts(sh_cke);
			_putchar('\n');
			return (1);
		}
		_puts(_getenvr(info, "OLDPWD=")), _putchar('\n');
		cd_result = /* TBD: what do you want? */
				chdir((directory = _getenvr(info, "OLDPWD=")) ? directory : "/");
	}
	else
		cd_result = chdir(info->cust_avect[1]);
	if (cd_result == -1)
	{
		report_err(info, "unable to chage directory to ");
		_my_eputs(info->cust_avect[1]), _eput_char('\n');
	}
	else
	{
		_set_env(info, "OLDPWD", _getenvr(info, "PWD="));
		_set_env(info, "PWD", getcwd(_buff, 1024));
	}
	return (0);
}

/**
 * _support - this will put the process'sh_cke current directory
 * @info: argument hold it  for agreeing function prototype.
 *  Return: always return 0
 */
int _support(info_t *info)
{
	char **arrayArgs;

	arrayArgs = info->cust_avect;
	_puts("Help call is working. Function pending \n");
	if (0)
		_puts(*arrayArgs);
	return (0);
}
