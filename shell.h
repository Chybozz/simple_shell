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

/* read/write buffers */
#define READ_BUFF_SIZE 1024
#define WRITE_BUFF_SIZE 1024
#define BUFF_FLUSH -1

/* command chaining */
#define CMD_NORM	0
#define CMD_OR		1
#define CMD_AND		2
#define CMD_CHAIN	3

/* convert_number() */
#define CONVERT_LOWERCASE	1
#define CONVERT_UNSIGNED	2

/* 1 if using system getline() */
#define USE_GETLINE 0
#define USE_STRTOK 0

#define HIST_FILE	".simple_shell_history"
#define HIST_MAX	4096

extern char **environ;


/**
 * struct liststr - singly linked list
 * @num: the number field
 * @str: a string
 * @next: points to the next node
 */
typedef struct liststr
{
	int num;
	char *str;
	struct liststr *next;
} list_t;

/**
 *struct passinfo - contains pseudo-arguements to pass into a function,
 *		allowing uniform prototype for function pointer struct
 *@arg: a string generated from getline containing arguements
 *@argv: an array of strings generated from arg
 *@path: a string path for the current command
 *@argc: the argument count
 *@line_count: the error count
 *@err_num: the error code for exit()s
 *@linecount_flag: if on count this line of input
 *@fname: the program filename
 *@env: linked list local copy of environ
 *@environ: custom modified copy of environ from LL env
 *@history: the history node
 *@alias: the alias node
 *@env_changed: on if environ was changed
 *@status: the return status of the last exec'd command
 *@cmd_buff: address of pointer to cmd_buff, on if chaining
 *@cmd_buff_type: CMD_type ||, &&, ;
 *@readfd: the fd from which to read line input
 *@histcount: the history line number count
 */
typedef struct passinfo
{
	char *arg;
	char **argv;
	char *path;
	int argc;
	unsigned int line_count;
	int err_num;
	int linecount_flag;
	char *fname;
	list_t *env;
	list_t *history;
	list_t *alias;
	char **environ;
	int env_changed;
	int status;

	char **cmd_buff; /* pointer to cmd ; chain buffer, for memory mangement */
	int cmd_buff_type; /* CMD_type ||, &&, ; */
	int readfd;
	int histcount;
} info_t;

#define INFO_INIT \
{NULL, NULL, NULL, 0, 0, 0, 0, NULL, NULL, NULL, NULL, NULL, 0, 0, NULL, \
	0, 0, 0}

/**
 *struct builtin - contains a builtin string and related function
 *@type: the builtin command flag
 *@func: the function
 */
typedef struct builtin
{
	char *type;
	int (*func)(info_t *);
} builtin_table;

/* Functions Prototypes */

/* toem_shloop.c */
int hsh(info_t *info, char **av);
int find_builtin(info_t *info);
void find_cmd(info_t *info);
void fork_cmd(info_t *info);

/* toem_parser.c */
int isfile_cmd(info_t *info, char *path);
char *dup_chars(char *pathstr, int sta, int stp);
char *find_path(info_t *info, char *pathstr, char *cmd);

/* loophsh.c */
int loophsh(char **);

/* toem_errors.c */
void _eputs(char *str);
int _eputchar(char chr);
int _putfd(char chr, int fd);
int _putsfd(char *str, int fd);

/* toem_string.c */
int _strlen(char *s_len);
int _strcmp(char *s1, char *s2);
char *starts_with(const char *haystack, const char *needle);
char *_strcat(char *dest, char *src);

/* toem_string1.c */
char *_strcpy(char *dest, char *src);
char *_strdup(const char *str);
void _puts(char *str);
int _putchar(char c);

/* toem_exits.c */
char *_strncpy(char *dest, char *src, int n);
char *_strncat(char *fstr, char *sstr, int n);
char *_strchr(char *strg, char chr);

/* toem_tokenizer.c */
char **strtow(char *str, char *del);
char **strtow2(char *str, char del);

/* toem_realloc.c */
char *_memset(char *a, char b, unsigned int c);
void ffree(char **pp);
void *_realloc(void *ptr, unsigned int older_size, unsigned int newer_size);

/* toem_memory.c */
int ptr_free(void **ptr);

/* toem_atoi.c */
int interactive(info_t *nfo);
int is_delim(char chr, char *delim);
int _isalpha(int chr);
int _atoi(char *stc);

/* toem_errors1.c */
int _erratoi(char *strg);
void print_error(info_t *info, char *estr);
int print_d(int input, intfd);
char *convert_number(long int num, int base, int flags);
void remove_comments(char *buf);

/* toem_builtin.c */
int _myexit(info_t *info);
int _mycd(info_t *info);
int _myhelp(info_t *info);

/* toem_builtin1.c */
int _myhistory(info_t *info);
int _myalias(info_t *info);

/*toem_getline.c */
ssize_t get_input(info_t *info);
int _getline(info_t *info, char **ptr, size_t *length);
void sigintHandler(int sig_num);

/* toem_getinfo.c */
void clear_info(info_t *info);
void set_info(info_t *info, char **av);
void free_info(info_t *info, int all);

/* toem_environ.c */
char *_getenv(info_t *info, const char *nm);
int _myenv(info_t *info);
int _mysetenv(info_t *info);
int _myunsetenv(info_t *info);
int populate_env_list(info_t *info);

/* toem_getenv.c */
char **get_environ(info_t *info);
int _unsetenv(info_t *info, char *var);
int _setenv(info_t *info, char *var, char *val);

/* toem_history.c */
char *get_history_file(info_t *info);
int write_history(info_t *info);
int read_history(info_t *info);
int build_history_list(info_t *info, char *buf, int linecount);
int renumber_history(info_t *info);

/* toem_lists.c */
list_t *add_node(list_t **head, const char *str, int val);
list_t *add_node_end(list_t **head, const char *str, int val);
size_t print_list_str(const list_t *k);
int delete_node_at_index(list_t **head, unsigned int index);
void free_list(list_t **head_ptr);

/* toem_lists1.c */
size_t list_len(const list_t *k);
char **list_to_strings(list_t *head);
size_t print_list(const list_t *k);
list_t *node_starts_with(list_t *node, char *prefix, char c);
ssize_t get_node_index(list_t *head, list_t *node);

/* toem_vars.c */
int is_chain(info_t *info, char *buff, size_t *s);
void check_chain(info_t *info, char *buff, size_t *s, size_t i, size_t len);
int sub_alias(info_t *info);
int sub_vars(info_t *info);
int sub_string(char **older, char *newer);

#endif
