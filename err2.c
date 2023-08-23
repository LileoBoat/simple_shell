#include "shell.h"

/**
 * stringtoint - it changes  string into equivalent integer
 * @sh_cke: It displays the string that is intended to be modified.
 * Return: Returns 0 if number is not present, the num is converted
 *  but -1 if there is an error.
 */
int stringtoint(char *sh_cke)
{
	int i = 0;
	unsigned long int outcome = 0;

	if (*sh_cke == '+')
		sh_cke++; /* TBD: what is the reason to make the function man rturn 255? */
	for (i = 0; sh_cke[i] != '\0'; i++)
	{
		if (sh_cke[i] >= '0' && sh_cke[i] <= '9')
		{
			outcome *= 10;
			outcome += (sh_cke[i] - '0');
			if (outcome > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (outcome);
}

/**
 * report_err - Show a message indicating an error.
 * @info: parameter and structure containing return information
 * @errmsg: a string holding the defined error category
 * Return: Returns 0 if number is not present, the num is converted
 * but -1 if there is an error.
 */
void report_err(info_t *info, char *errmsg)
{
	_my_eputs(info->file_name);
	_my_eputs(": ");
	print_interger(info->count_row, STDERR_FILENO);
	_my_eputs(": ");
	_my_eputs(info->cust_avect[0]);
	_my_eputs(":: ");
	_my_eputs(errmsg);
}

/**
 * print_interger - an integer number base 10 in decimal is printed
 * using the function
 * @value: the value is been presented
 * @filedesc: the file descriptor should be written here
 *
 * Return: the number of char shown
 */
int print_interger(int value, int filedesc)
{
	int (*__putchar)(char) = _putchar;
	int i, quant = 0;
	unsigned int _abval, existing;

	if (filedesc == STDERR_FILENO)
		__putchar = _eput_char;
	if (value < 0)
	{
		_abval = -value;
		__putchar('-');
		quant++;
	}
	else
		_abval = value;
	existing = _abval;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abval / i)
		{
			__putchar('0' + existing / i);
			quant++;
		}
		existing %= i;
	}
	__putchar('0' + existing);
	quant++;

	return (quant);
}

/**
 * num_convted - modify the function, replicating the features
 * @number: num to display
 * @num_base: num_base
 * @conv_flag: argument of the conv_flag
 *
 * Return: Always return strings
 */
char *num_convted(long int number, int num_base, int conv_flag)
{
	static char *string_pointer;
	static char _buff[50];
	char pan = 0;
	char *_pointer;
	unsigned long n = number;

	if (!(conv_flag & CONVERT_UNSIGNED) && number < 0)
	{
		n = -number;
		pan = '-';
	}
	string_pointer = conv_flag & CONVERT_LOWERCASE ? "0123456789abcdef" :
				 "0123456789ABCDEF";
	_pointer = &_buff[49];
	*_pointer = '\0';

	do {
		*--_pointer = string_pointer[n % num_base];
		n /= num_base;
	} while (n != 0);

	if (pan)
		*--_pointer = pan;
	return (_pointer);
}

/**
 * del_comment - the returned value of this function is the first
 * of ‘#’ along ‘\0’.
 * @buffer: the provided value rep the memory address of string to be edited
 *
 * Return: return 0 always
 */
void del_comment(char *buffer)
{
	int i;

	for (i = 0; buffer[i] != '\0'; i++)
		if (buffer[i] == '#' && (!i || buffer[i - 1] == ' '))
		{
			buffer[i] = '\0';
			break;
		}
}
