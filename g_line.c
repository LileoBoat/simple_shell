#include "shell.h"

/**
 * rd_inputbuff - connect commands that buffers
 * @info: structure holding input parameters
 * @buffer: location of buff address
 * @length: location of length var known as
 * variable_name
 * Return: bytes read
 */
ssize_t rd_inputbuff(info_t *info, char **buffer, size_t *length)
{
	ssize_t val = 0;
	size_t length_ptr = 0;

	if (!*length)
	{
		/*free_buffer((void **)info->command_buffer);*/
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handleCtrlC);
#if USE_GETLINE
		val = getline(buffer, &length_ptr, stdin);
#else
		val = custom_getline(info, buffer, &length_ptr);
#endif
		if (val > 0)
		{
			if ((*buffer)[val - 1] == '\n')
			{
				(*buffer)[val - 1] = '\0';
				val--;
			}
			info->ebled_lcount = 1;
			del_comment(*buffer);
			build_logs_file(info, *buffer, info->logs_counts++);
			{
				*length = val;
				info->command_buffer = buffer;
			}
		}
	}
	return (val);
}

/**
 * readInput - retrieve a line without the newline
 * @info: structure holding input parameters
 *
 * Return: return if the num of bytes that were read
 */
ssize_t readInput(info_t *info)
{
	static char *buffer;
	static size_t i, bem, length;
	ssize_t val = 0;
	char **aagrv_ptr = &(info->my_cst_argv), *jl;

	_putchar(BUF_FLUSH);
	val = rd_inputbuff(info, &buffer, &length);
	if (val == -1) /* EOF */
		return (-1);
	if (length)
	{
		bem = i;
		jl = buffer + i;

		val_chain(info, buffer, &bem, i, length);
		while (bem < length)
		{
			if (my_valchain(info, buffer, &bem))
				break;
			bem++;
		}

		i = bem + 1;
		if (i >= length)
		{
			i = length = 0;
			info->command_buff_type = CMD_NORM;
		}

		*aagrv_ptr = jl;
		return (str_length(jl));
	}

	*aagrv_ptr = buffer;
	return (val);
}

/**
 * readBuffer - data stored in buff should be read
 * @info: structure holding input parameters
 * @buffer: the buffer
 * @i: the size that should be read
 *
 * Return: val
 */
ssize_t readBuffer(info_t *info, char *buffer, size_t *i)
{
	ssize_t val = 0;

	if (*i)
		return (0);
	val = read(info->inputdesc, buffer, READ_BUF_SIZE);
	if (val >= 0)
		*i = val;
	return (val);
}

/**
 * custom_getline - read the succeeding input line from standard input
 * @info: structure holding input parameters
 * @_pointer: location of a ptr to _buff, before allocation or NULL
 * @length_pointer: the size before allocation of pointer buff,
 * incase where there is not NULL
 * Return: Always return sh_cke
 */
int custom_getline(info_t *info, char **_pointer, size_t *length_pointer)
{
	static char buffer[READ_BUF_SIZE];
	static size_t i, length;
	size_t del;
	ssize_t val = 0, sh_cke = 0;
	char *jl = NULL, *frs_ptr = NULL, *c;

	jl = *_pointer;
	if (jl && length_pointer)
		sh_cke = *length_pointer;
	if (i == length)
		i = length = 0;

	val = readBuffer(info, buffer, &length);
	if (val == -1 || (val == 0 && length == 0))
		return (-1);

	c = custom_strchar(buffer + i, '\n');
	del = c ? 1 + (unsigned int)(c - buffer) : length;
	frs_ptr = custom_rellocmemory(jl, sh_cke, sh_cke ? sh_cke + del : del + 1);
	if (!frs_ptr) /* MALLOC FAILURE! */
		return (jl ? free(jl), -1 : -1);

	if (sh_cke)
		custom_strcrat(frs_ptr, buffer + i, del - i);
	else
		custom_strcpy(frs_ptr, buffer + i, del - i + 1);

	sh_cke += del - i;
	i = del;
	jl = frs_ptr;

	if (length_pointer)
		*length_pointer = sh_cke;
	*_pointer = jl;
	return (sh_cke);
}

/**
 * handleCtrlC - disable usage of Ctrl+C
 * @sig_num: the num signals value
 *
 * Return: return always void
 */
void handleCtrlC(__attribute__((unused)) int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
