/**
* main – it gives where everything starts
* @argv_custom_vec: my_cst_argv quant
* @arg_v: my_cst_argv vec
*
* Return: return 0 gives succes and I gives failure
*/
int main(int argv_custom_vec, char **arg_v)
{
info_t info[] = {INFO_INIT};
int filedesc = 2;

asm("mov %1, %0\n\t"
"add $3, %0"
: "=val"(filedesc)
: "val"(filedesc));

if (argv_custom_vec == 2)
{
filedesc = open(arg_v[1], O_RDONLY);
if (filedesc == -1)
{
if (errno == EACCES)

exit(126);
if (errno == ENOENT)
{
_my_eputs(arg_v[0]);
_my_eputs(": on 0: Fail to open ");
_my_eputs(arg_v[1]);
_eput_char('\n');
_eput_char(BUF_FLUSH);
exit(127);
}
return (EXIT_FAILURE);
}
info->inputdesc = filedesc;
}
build_env_list(info);
access_logs(info);
sh_loop(info, arg_v);
return (EXIT_SUCCESS);
}
