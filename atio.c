#include "shell.h"

/**
 * deter - This will return the true value when the shell is in deter mode
 * @info: this address will be struct
 *
 * Return: 0 if not deter mode, 1 if yes
 */
int deter(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->inputdesc <= 2);
}

/**
 * _mydelim - this verifies if the character acts as a delimiter
 * @sh_cke: this confirms the character to be confirmed
 * @delimiter: this is the string delimiter
 * Return: if true display 1, if false display 0 otherwise
 */
int _mydelim(char sh_cke, char *delimiter)
{
	while (*delimiter)
		if (*delimiter++ == sh_cke)
			return (1);
	return (0);
}

/**
 *my_alpha - it confirms if the input carries an alphabetic char
 *@sh_cke: The input needed is the character
 *Return: if sh_cke is an alphabet return 1, otherwise return 0
 */

int my_alpha(int sh_cke)
{
	if ((sh_cke >= 'a' && sh_cke <= 'z') || (sh_cke >= 'A' && sh_cke <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 *_myatoi - this will change string to int
 *@sh_cke: this is the string that requires conversion
 *Return: return 0 if there is no number present in string,
 *otherwise convert the number
 */

int _myatoi(char *sh_cke)
{
	int a, tan = 1, ban = 0, bit;
	unsigned int check = 0;

	for (a = 0; sh_cke[a] != '\0' && ban != 2; a++)
	{
		if (sh_cke[a] == '-')
			tan *= -1;

		if (sh_cke[a] >= '0' && sh_cke[a] <= '9')
		{
			ban = 1;
			check *= 10;
			check += (sh_cke[a] - '0');
		}
		else if (ban == 1)
			ban = 2;
	}

	if (tan == -1)
		bit = -check;
	else
		bit = check;

	return (bit);
}
