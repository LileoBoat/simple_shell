#include "shell.h"

/**
* copy_string – duplicate string
* @destintn: it ends
* @source: beginning
*
* Return: return ptr of beginning
*/
char *copy_string(char *destintn, char *source)
{
int i = 0;

if (destintn == source || source == 0)
return (destintn);
while (source[i])
{

destintn[i] = source[i];
i++;
}
destintn[i] = 0;
return (destintn);
}

/**
* duplicat_str – this will have paired string
* @str: this string to be paired
*
* Return: paired string is pointed.
*/
char *duplicat_str(const char *str)
{
int length_pointer = 0;
char *und;

if (str == NULL)
return (NULL);
while (*str++)
length_pointer++;
und = malloc(sizeof(char) * (length_pointer + 1));
if (!und)

return (NULL);
for (length_pointer++; length_pointer--;)
und[length_pointer] = *--str;
return (und);
}

/**
*_puts - outputs string places in
*@str: string outputted
*
* Return: return void
*/
void _puts(char *str)
{
int i = 0;

if (!str)
return;
while (str[i] != '\0')
{
_putchar(str[i]);
i++;
}
}

/**
* _putchar – this gives alphabet c the standard output
* @c: This value to output
*
* Return: 1gives success
* if error, -1 shows error , and errno is applied.
*/
int _putchar(char c)
{
static int i;
static char buffer[WRITE_BUF_SIZE];

if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
{
write(1, buffer, i);
i = 0;
}
if (c != BUF_FLUSH)
buffer[i++] = c;
return (1);
}
