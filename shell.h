#ifndef _SHELL_H_
#define _SHELL_H_

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <sys/stat.h>
#include <limits.h>
#include <fcntl.h>
#include <errno.h>

/* for read/write buffers */
#define READ_BUF_SIZE 1024
#define WRITE_BUF_SIZE 1024
#define BUF_FLUSH -1

/* for command chaining */
#define CMD_NORM 0
#define CMD_OR 1

#define CMD_AND 2
#define CMD_CHAIN 3

/* for num_convted() */
#define CONVERT_LOWERCASE 1
#define CONVERT_UNSIGNED 2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE ".simple_shell_history"
#define HIST_MAX 4096

extern char **environ;

/**
* struct liststr - singly linked list
* @number: the number field
* @str: a string
* @next: points to the next point
*/
typedef struct liststr
{

int number;
char *str;
struct liststr *next;
} list_t;

/**
*struct passinfo - has pseudo-arguements allowing functions,
*giving prototype for function pointer structures
*@my_cst_argv: string gotten in the getline holder arguements
*@cust_avect: an array of strings generated from my_cst_argv
*@evec_path: a string evec_path for the existing command
*@argument_count: the argument quant
*@count_row: quantity of error
*@e_number: error code exit()sh_cke
*@ebled_lcount: conditioned quantity this line of var_val
*@file_name: the command filename
*@my_environ: linked list localized in a reprint environ
*@environ: usage change of duplicate environ LL my_environ
*@logs: the logs point
*@alias: the alias
*@custom_envchged: shows environ if uttered
*@stat: will bring back execution of the end stat
*@command_buffer: checks pointer command_buffer.
*@command_buff_type: CMD_type ||, &&, ;

*@inputdesc: the filedesc from gotten in line var_val
*@logs_counts: logs amount of line
*/
typedef struct passinfo
{
char *my_cst_argv;
char **cust_avect;
char *evec_path;
int argument_count;
unsigned int count_row;
int e_number;
int ebled_lcount;
char *file_name;
list_t *my_environ;
list_t *logs;
list_t *alias;
char **environ;
int custom_envchged;
int stat;

char **command_buffer; /* pointer to cmd ; chain _buff, for memory mangement */
int command_buff_type; /* CMD_type ||, &&, ; */
int inputdesc;
int logs_counts;

} info_t;

#define INFO_INIT \
{ \
NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \

0, 0, 0 \

}

/**
*struct builtin - contains a string that is internally defined, with related funct
*@type: the signal of the builtin command
*@func: the function
*/
typedef struct builtin
{
char *type;
int (*func)(info_t *);
} builtin_table;

/* source_s_loop.c */
int sh_loop(info_t *, char **);
int searh_fnct(info_t *);
void searh_cmmd(info_t *);
void ffork_command(info_t *);

/* source_pars.c */
int cust_commad(info_t *, char *);
char *dob_cha(char *, int, int);
char *dev_paths(info_t *, char *, char *);

/* s_loop.c */
int loophsh(char **);

/* source_err.c */
void _my_eputs(char *);
int _eput_char(char);
int my_putfd(char c, int filedesc);
int my_putfdesc(char *str, int filedesc);

/* source_str.c */
int str_length(char *);
int my_string_cmp(char *, char *);
char *_starts_with(const char *, const char *);
char *_str_concat(char *, char *);

/* source_str1.c */
char *copy_string(char *, char *);
char *duplicat_str(const char *);

void _puts(char *);
int _putchar(char);

/* source_exit.c */
char *custom_strcpy(char *, char *, int);
char *custom_strcrat(char *, char *, int);
char *custom_strchar(char *, char);

/* source_token.c */
char **_mystringtow(char *, char *);
char **_mysec_str(char *, char);

/* source_rellcation.c */
char *cust_mem_set(char *, char, unsigned int);
void allocate_custom_free(char **);
void *custom_rellocmemory(void *, unsigned int, unsigned int);

/* source_memor.c */
int free_buffer(void **);

/* source_atio.c */
int deter(info_t *);
int _mydelim(char, char *);
int my_alpha(int);

int _myatoi(char *);

/* source_err2.c */
int stringtoint(char *);
void report_err(info_t *, char *);
int print_interger(int, int);
char *num_convted(long int, int, int);
void del_comment(char *);

/* source_buil.c */
int exit_now(info_t *);
int custom_cd(info_t *);
int _support(info_t *);

/* source_buil2.c */
int _mylogs(info_t *);
int my_aliasid(info_t *);

/*source_g_line.c */
ssize_t readInput(info_t *);
int custom_getline(info_t *, char **, size_t *);
void handleCtrlC(int);

/* source_g_info.c */

void ri_struct(info_t *);
void my_setinfo(info_t *, char **);
void rel_mem(info_t *, int);

/* source_env.c */
char *_getenvr(info_t *, const char *);
int _customenv(info_t *);
int _configenv(info_t *);
int unset_env_vir(info_t *);
int build_env_list(info_t *);

/* source_g_env.c */
char **get_env_var(info_t *);
int unset_variable_env(info_t *, char *);
int _set_env(info_t *, char *, char *);

/* source_hist.c */
char *my_log_file(info_t *info);
int my_doc_log(info_t *info);
int access_logs(info_t *info);
int build_logs_file(info_t *info, char *buffer, int ln_count);
int order_list_logs(info_t *info);

/* source_lissts2.c */

list_t *add_point(list_t **, const char *, int);
list_t *append_point(list_t **, const char *, int);
size_t display_list_str(const list_t *);
int del_env_node_index(list_t **, unsigned int);
void allocate_free_list(list_t **);

/* source_lisst.c */
size_t lists_lens(const list_t *);
char **convert_ls_to_strings(list_t *);
size_t display_lists(const list_t *);
list_t *node_prefix(list_t *, char *, char);
ssize_t points_index(list_t *, list_t *);

/* source_var.c */
int my_valchain(info_t *, char *, size_t *);
void val_chain(info_t *, char *, size_t *, size_t, size_t);
int apply_repalias(info_t *);
int perform_repvars(info_t *);
int repl_s(char **, char *);

#endif
