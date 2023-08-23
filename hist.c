#include "shell.h"

/**
 * my_log_file - retrieves the files for logs
 * @info: structure holding input parameters
 *
 * Return: str that are allocate in memes containing log file
 */

char *my_log_file(info_t *info)
{
	char *buffer, *directory;

	directory = _getenvr(info, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (str_length(directory)
			+ str_length(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	copy_string(buffer, directory);
	_str_concat(buffer, "/");
	_str_concat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * my_doc_log - extends an file that exit, or generate a new one
 * @info: structure holding input parameters
 *
 * Return: return 1 if successful, otherwise return -1
 */
int my_doc_log(info_t *info)
{
	ssize_t filedesc;
	char *data_inf = my_log_file(info);
	list_t *point = NULL;

	if (!data_inf)
		return (-1);

	filedesc = open(data_inf, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(data_inf);
	if (filedesc == -1)
		return (-1);
	for (point = info->logs; point; point = point->next)
	{
		my_putfdesc(point->str, filedesc);
		my_putfd('\n', filedesc);
	}
	my_putfd(BUF_FLUSH, filedesc);
	close(filedesc);
	return (1);
}

/**
 * access_logs - retrieve logs inside a file
 * @info: structure holding input parameters
 *
 * Return: return logs_counts if successful, else return 0
 */
int access_logs(info_t *info)
{
	int i, final = 0, ln_count = 0;
	ssize_t filedesc, read_length, file_size = 0;
	struct stat stats_status;
	char *buffer = NULL, *data_inf = my_log_file(info);

	if (!data_inf)
		return (0);

	filedesc = open(data_inf, O_RDONLY);
	free(data_inf);
	if (filedesc == -1)
		return (0);
	if (!fstat(filedesc, &stats_status))
		file_size = stats_status.st_size;
	if (file_size < 2)
		return (0);
	buffer = malloc(sizeof(char) * (file_size + 1));
	if (!buffer)
		return (0);
	read_length = read(filedesc, buffer, file_size);
	buffer[file_size] = 0;
	if (read_length <= 0)
		return (free(buffer), 0);
	close(filedesc);
	for (i = 0; i < file_size; i++)
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_logs_file(info, buffer + final, ln_count++);
			final = i + 1;
		}
	if (final != i)
		build_logs_file(info, buffer + final, ln_count++);
	free(buffer);
	info->logs_counts = ln_count;
	while (info->logs_counts-- >= HIST_MAX)
		del_env_node_index(&(info->logs), 0);
	order_list_logs(info);
	return (info->logs_counts);
}

/**
 * build_logs_file - place a new log record into list that was linked
 * @info: agr-related structure, used to maintain consistency
 * @buffer: the _buff
 * @ln_count: the logs ln_count, logs_counts
 *
 * Return: return 0 always
 */
int build_logs_file(info_t *info, char *buffer, int ln_count)
{
	list_t *point = NULL;

	if (info->logs)
		point = info->logs;
	append_point(&point, buffer, ln_count);

	if (!info->logs)
		info->logs = point;
	return (0);
}

/**
 * order_list_logs - rearranges the logs linked to reflect the list
 * @info: agr-related structure, used to maintain consistency
 *
 * Return: fresh logs_counts
 */
int order_list_logs(info_t *info)
{
	list_t *point = info->logs;
	int i = 0;

	while (point)
	{
		point->number = i++;
		point = point->next;
	}
	return (info->logs_counts = i);
}
