#include "shell.h"

/**
* cust_commad – looks for executable files for cmds

* @info: information structure
* @evec_path: pathway for the files
*
* Return: 1for true 0 for else
*/
int cust_commad(info_t *info, char *evec_path)
{
struct stat stats_status;

(void)info;
if (!evec_path || stat(evec_path, &stats_status))
return (0);

if (stats_status.st_mode & S_IFREG)
{
return (1);
}
return (0);
}

/**
* dob_cha – copies values
* @ps: PATH string
* @kick_off: setting off index

* @end_ptr: holding off index point
*
* Return: return ptr to fresh _buff
*/
char *dob_cha(char *ps, int kick_off, int end_ptr)
{
static char buffer[1024];
int i = 0, del = 0;

for (del = 0, i = kick_off; i < end_ptr; i++)
if (ps[i] != ':')
buffer[del++] = ps[i];

buffer[del] = 0;
return (buffer);
}

/**
* dev_paths - searches command where rdirection str
* @info: information structure
* @ps: showing where it it passes to string
* @commad_path: cmd_path for searching
*
* Return: all evec_ways cmd_ways if not in or in
*/

char *dev_paths(info_t *info, char *ps, char *commad_path)
{
int i = 0, rec_post = 0;
char *evec_path;

if (!ps)
return (NULL);
if ((str_length(commad_path) > 2) && _starts_with(commad_path, "./"))
{
if (cust_commad(info, commad_path))
return (commad_path);

}
while (1)
{
if (!ps[i] || ps[i] == ':')
{
evec_path = dob_cha(ps, rec_post, i);
if (!*evec_path)
_str_concat(evec_path, commad_path);
else
{
_str_concat(evec_path, "/");
_str_concat(evec_path, commad_path);
}

if (cust_commad(info, evec_path))
return (evec_path);
if (!ps[i])
break;
rec_post = i;
}
i++;
}
return (NULL);
}
