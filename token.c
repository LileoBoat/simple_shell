#include "shell.h"

/**
* **_mystringtow – will divide a string into alphabets . Doing delimiters unconcerned.
* @str: intake string
* @ds: delimiter of strings
* Return: return ptr string of strings, else return NULL if failed
*/

char **_mystringtow(char *str, char *ds)
{
int i, bem, del, lg, nws = 0;
char **sh_cke;

if (str == NULL || str[0] == 0)
return (NULL);
if (!ds)
ds = " ";
for (i = 0; str[i] != '\0'; i++)
if (!_mydelim(str[i], ds) && (_mydelim(str[i + 1], ds) || !str[i + 1]))
nws++;

if (nws == 0)
return (NULL);

sh_cke = malloc((1 + nws) * sizeof(char *));
if (!sh_cke)
return (NULL);
for (i = 0, bem = 0; bem < nws; bem++)
{
while (_mydelim(str[i], ds))
i++;
del = 0;
while (!_mydelim(str[i + del], ds) && str[i + del])
del++;
sh_cke[bem] = malloc((del + 1) * sizeof(char));
if (!sh_cke[bem])
{
for (del = 0; del < bem; del++)
free(sh_cke[del]);
free(sh_cke);
return (NULL);
}
for (lg = 0; lg < del; lg++)
sh_cke[bem][lg] = str[i++];
sh_cke[bem][lg] = 0;
}
sh_cke[bem] = NULL;
return (sh_cke);

}

/**
* **_mysec_str – it will divide the string into to words
* @str: this takes in string
* @ds: the delimiter
* Return: this pointer is to give a strin of strings, else return NULL if failed
*/
char **_mysec_str(char *str, char ds)
{
int i, bem, del, lg, nws = 0;
char **sh_cke;

if (str == NULL || str[0] == 0)
return (NULL);
for (i = 0; str[i] != '\0'; i++)
if ((str[i] != ds && str[i + 1] == ds) ||

(str[i] != ds && !str[i + 1]) || str[i + 1] == ds)
nws++;
if (nws == 0)
return (NULL);
sh_cke = malloc((1 + nws) * sizeof(char *));
if (!sh_cke)
return (NULL);

for (i = 0, bem = 0; bem < nws; bem++)
{
while (str[i] == ds && str[i] != ds)
i++;
del = 0;
while (str[i + del] != ds && str[i + del] && str[i + del] != ds)
del++;
sh_cke[bem] = malloc((del + 1) * sizeof(char));
if (!sh_cke[bem])
{
for (del = 0; del < bem; del++)
free(sh_cke[del]);
free(sh_cke);
return (NULL);
}
for (lg = 0; lg < del; lg++)
sh_cke[bem][lg] = str[i++];
sh_cke[bem][lg] = 0;
}
sh_cke[bem] = NULL;
return (sh_cke);
}
