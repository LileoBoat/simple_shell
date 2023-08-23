#include "shell.h"

/**
 **custom_strcpy - it makes duplicate of a str
 *@destintn: the target string for the duplication
 *@source: starting src string
 *@n: it’s the value  of chars to reprint
 *Return: merged str
 */
char *custom_strcpy(char *destintn, char *source, int n)
{
	int i, bem;
	char *sh_cke = destintn;

	i = 0;
	while (source[i] != '\0' && i < n - 1)
	{
		destintn[i] = source[i];
		i++;
	}
	if (i < n)
	{
		bem = i;
		while (bem < n)
		{
			destintn[bem] = '\0';
			bem++;
		}
	}
	return (sh_cke);
}

/**
 **custom_strcrat - merge both strings
 *@destintn: starting str
 *@source: next str
 *@n: highest amount of byte that will be used
 *Return: merged str
 */
char *custom_strcrat(char *destintn, char *source, int n)
{
	int i, bem;
	char *sh_cke = destintn;

	i = 0;
	bem = 0;
	while (destintn[i] != '\0')
		i++;
	while (source[bem] != '\0' && bem < n)
	{
		destintn[i] = source[bem];
		i++;
		bem++;
	}
	if (bem < n)
		destintn[i] = '\0';
	return (sh_cke);
}

/**
 **custom_strchar - to search for the char position in str
 *@sh_cke: str intended for parsing
 *@c: the char to search
 *Return: the memory area sh_cke is accessed through the ptr.
 */
char *custom_strchar(char *sh_cke, char c)
{
	do {
		if (*sh_cke == c)
			return (sh_cke);
	} while (*sh_cke++ != '\0');

	return (NULL);
}
