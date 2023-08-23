#include "shell.h"

/**
 *_my_eputs - shows the string of texts or inputs
 * @str: the text or input string will be revealed.
 *
 * Return: it will not retrieve anything
 */
void _my_eputs(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_eput_char(str[i]);
		i++;
	}
}

/**
 * _eput_char - it will show  a c character to the standard error.
 * @c: chars to be revealed printed
 *
 * Return: return success 1, and -1 on error with proper error handling
 */
int _eput_char(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * my_putfd - output the c character to the supplied filedesc file descriptor
 * @c: it shows the calculated chars be printed.
 * @filedesc: a file descriptor works writing on.
 *
 * Return: return success 1, and -1 on error with proper error handling
 */
int my_putfd(char c, int filedesc)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(filedesc, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 *my_putfdesc - output on string needed.
 * @str: it shows the calculated string for printing.
 * @filedesc: The selected file descriptor for writing.
 *
 * Return: quantity of characters placed.
 */
int my_putfdesc(char *str, int filedesc)
{
	int i = 0;

	if (!str)
		return (0);
	while (*str)
	{
		i += my_putfd(*str++, filedesc);
	}
	return (i);
}
