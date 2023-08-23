#include "shell.h"

/**
* sh_loop – this loops in the actual shell
* @info: info structure for both parameters and return
* @arg_v: the main vector arg
*
* Return: succes for 0, 1 for failed code,
*/
int sh_loop(info_t *info, char **arg_v)
{
ssize_t val = 0;
int bt_r = 0;

while (val != -1 && bt_r != -2)
{

ri_struct(info);
if (deter(info))
_puts("$ ");
_eput_char(BUF_FLUSH);
val = readInput(info);
if (val != -1)
{
my_setinfo(info, arg_v);
bt_r = searh_fnct(info);
if (bt_r == -1)
searh_cmmd(info);

}
else if (deter(info))
_putchar('\n');
rel_mem(info, 0);
}
my_doc_log(info);
rel_mem(info, 1);
if (!deter(info) && info->stat)
exit(info->stat);
if (bt_r == -2)
{
if (info->e_number == -1)
exit(info->stat);

exit(info->e_number);
}
return (bt_r);
}

/**
* searh_fnct – searches for a builtin cmds
* @info: surroundings and gives back information structure
*
* Return: return -1 if the builtin is missing
* 0 for succes builtin ,
* 1 for gotten but failed,
* -2 gives builtin for exit()
*/
int searh_fnct(info_t *info)
{
int i, stand_func = -1;
builtin_table stand_tab[] = {
{"exit", exit_now},
{"my_environ", _customenv},
{"help", _support},
{"logs", _mylogs},
{"setenv", _configenv},
{"unsetenv", unset_env_vir},

{"cd", custom_cd},
{"alias", my_aliasid},
{NULL, NULL}};

for (i = 0; stand_tab[i].type; i++)
if (my_string_cmp(info->cust_avect[0], stand_tab[i].type) == 0)
{
info->count_row++;
stand_func = stand_tab[i].func(info);
break;
}
return (stand_func);
}

/**
* searh_cmmd – searches for comm PATH
* @info: surroundings and gives back information structure
*
* Return: void
*/
void searh_cmmd(info_t *info)
{
char *evec_path = NULL;
int i, del;

info->evec_path = info->cust_avect[0];
if (info->ebled_lcount == 1)
{
info->count_row++;
info->ebled_lcount = 0;
}
for (i = 0, del = 0; info->my_cst_argv[i]; i++)
if (!_mydelim(info->my_cst_argv[i], " \t\n"))
del++;

if (!del)
return;

evec_path = dev_paths(info, _getenvr(info, "PATH="), info->cust_avect[0]);
if (evec_path)
{
info->evec_path = evec_path;
ffork_command(info);
}
else
{
if ((deter(info) || _getenvr(info, "PATH=") || info->cust_avect[0][0] == '/') &&

cust_commad(info, info->cust_avect[0]))
ffork_command(info);
else if (*(info->my_cst_argv) != '\n')

{
info->stat = 127;
report_err(info, "not seen\n");
}
}
}

/**
* ffork_command - forks executed thread commad
* @info: info structure for both parameters and return
*
* Return: void
*/
void ffork_command(info_t *info)
{
pid_t chid_pid;

chid_pid = fork();
if (chid_pid == -1)
{
perror("Invalid:");
return;
}
if (chid_pid == 0)

{
if (execve(info->evec_path, info->cust_avect, get_env_var(info)) == -1)
{
rel_mem(info, 1);
if (errno == EACCES)
exit(126);
exit(1);
}
}
else
{
wait(&(info->stat));
if (WIFEXITED(info->stat))
{
info->stat = WEXITSTATUS(info->stat);
if (info->stat == 126)
report_err(info, "Access declined\n");

}
}
}
