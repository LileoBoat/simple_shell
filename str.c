#include "shell.h"

/**
* str_length – brings back size string
* @sh_cke: testing string that’s size
*
* Return: size of int string
*/
int str_length(char *sh_cke)
{
int i = 0;

if (!sh_cke)
return (0);

while (*sh_cke++)
i++;
return (i);
}

/**
* my_string_cmp - compare string of strings in lexical ordering.
* @first_str: new str

* @second_str: next str
*
* Return: return false if first_str < second_str, positive if first_str > second_str, zero if first_str ==
second_str
*/
int my_string_cmp(char *first_str, char *second_str)
{
while (*first_str && *second_str)
{
if (*first_str != *second_str)
return (*first_str - *second_str);
first_str++;
second_str++;
}
if (*first_str == *second_str)
return (0);
else
return (*first_str < *second_str ? -1 : 1);

}

/**
* _starts_with – will see that bumbble begins with h_flex
* @h_flex: this gives looking for string
* @bumbble: the substring being looked for
*

* Return: return relocation of the next h_flex or NULL
*/
char *_starts_with(const char *h_flex, const char *bumbble)
{
while (*bumbble)
if (*bumbble++ != *h_flex++)
return (NULL);
return ((char *)h_flex);
}

/**
* _str_concat - concatenates both strings
* @destintn: the destination _buff
* @source: the source _buff
*
* Return: return ptr to its destination _buff
*/
char *_str_concat(char *destintn, char *source)
{
char *und = destintn;

while (*destintn)
destintn++;
while (*source)

*destintn++ = *source++;
*destintn = *source;
return (und);
}
