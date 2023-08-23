#include "shell.h"

/**
* my_valchain - this will examine the existing char in _buff to a chained delim
* @info: this is the environment structure
* @buffer: char _buff
* @jl: this addresss the existing location in buffer
*
* Return: return 1 if chained delimiter, else return 0
*/
int my_valchain(info_t *info, char *buffer, size_t *jl)
{
size_t bem = *jl;

if (buffer[bem] == '|' && buffer[bem + 1] == '|')
{
buffer[bem] = 0;
bem++;
info->command_buff_type = CMD_OR;
}
else if (buffer[bem] == '&' && buffer[bem + 1] == '&')
{
buffer[bem] = 0;

bem++;
info->command_buff_type = CMD_AND;
}
else if (buffer[bem] == ';')
{
buffer[bem] = 0;
info->command_buff_type = CMD_CHAIN;
}
else
return (0);
*jl = bem;
return (1);
}

/**
* val_chain - this is going to test if we can agend swapping concerning last stat
* @info: this is the environment structure
* @buffer: this is the char _buff
* @jl: this will be working on the existing location in buffer
* @i: this will be the initial location in buffer
* @length: determines the buffer size
*
* Return: Void
*/

void val_chain(info_t *info, char *buffer, size_t *jl, size_t i, size_t length)
{
size_t bem = *jl;

if (info->command_buff_type == CMD_AND)
{
if (info->stat)
{
buffer[i] = 0;
bem = length;
}
}
if (info->command_buff_type == CMD_OR)
{
if (!info->stat)
{
buffer[i] = 0;
bem = length;
}
}

*jl = bem;
}

/**
* apply_repalias – it brings back an aliases that has a token in string
* @info: structure holding input parameters
*
* Return: return 1 if changed, else return 0
*/
int apply_repalias(info_t *info)
{
int i;
list_t *point;
char *jl;

for (i = 0; i < 10; i++)
{
point = node_prefix(info->alias, info->cust_avect[0], '=');
if (!point)
return (0);
free(info->cust_avect[0]);
jl = custom_strchar(point->str, '=');
if (!jl)
return (0);
jl = duplicat_str(jl + 1);
if (!jl)
return (0);

info->cust_avect[0] = jl;
}
return (1);
}

/**
* perform_repvars – will bring back the vars that has tokens in string
* @info: this shows the structure of the environment
*
* Return: return 1 , 0 else
*/
int perform_repvars(info_t *info)
{
int i = 0;
list_t *point;

for (i = 0; info->cust_avect[i]; i++)
{
if (info->cust_avect[i][0] != '$' || !info->cust_avect[i][1])
continue;

if (!my_string_cmp(info->cust_avect[i], "$?"))
{
repl_s(&(info->cust_avect[i]),

duplicat_str(num_convted(info->stat, 10, 0)));

continue;
}
if (!my_string_cmp(info->cust_avect[i], "$$"))
{
repl_s(&(info->cust_avect[i]),

duplicat_str(num_convted(getpid(), 10, 0)));

continue;
}
point = node_prefix(info->my_environ, &info->cust_avect[i][1], '=');
if (point)
{
repl_s(&(info->cust_avect[i]),

duplicat_str(custom_strchar(point->str, '=') + 1));

continue;
}
repl_s(&info->cust_avect[i], duplicat_str(""));
}
return (0);
}

/**
* repl_s – it will be returning strings
* @pre: it will work on the initial string

* @nxt: nxt str
*
* Return: re enter if 1, else 0
*/
int repl_s(char **pre, char *nxt)
{
free(*pre);
*pre = nxt;
return (1);
}
