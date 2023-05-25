#ifndef _MAIN_H_
#define _MAIN_H_

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>

#define STRING ((uzi) ? uzi : "(null)")

/**
 * struct info - a data structure
 * @envp: environmental variables array.
 * @pwd: a directory
 * @line: input.
 * @path: a path
 * @prev_pwd: the previous working directory
 * @n_tkn: token number
 * @n_path: total tokens in a path
 * @status: a command status
 * @file: a stream
 * @count: operation count
 * @pid: shell identity
 * @s_name: a name
 */
typedef struct info
{
	char **envp;
	int n_tkn;
char **pwd;
	char *prev_pwd;
char *line;
	char *s_name;
	char *path;
	int file;
	int status;
	int pid;
int n_path;
int count;
} info;

int _length(int n);
int _scmp(char *uzi1, char *uzi2);
void handle_dots(char **line, info *ags);
char *_stringcat(char *dest, char *src);
int _print(const char *fmt, ...);
int handle_char(char c);
int handle_string(char *s);
char *_scat(char *dest, char *src, int n);
void handle_number(int n);
int specifier(char c, va_list ags);
int _stringlen(char *s);
char *_stringdup(info *ags, char *uzi);
int _stringcmp(const char *s1, const char *s2, size_t n);
char *_stringtok(char *uzi, const char *dlim);
char *_stringchr(char *s, char c);
void t_string(char *uzi, int num);
int _xeve(info *ags, char *buff);
char *h_realloc(info *agrs, char *buffer, int *buffer_size, int extra,
int max);
void *d_realloc(void *ptr, unsigned int prev, unsigned int curr_size);
int _atoi(char *s);
int _quit_(info *ags);
int input(info *ags, int arw, int *sm);
void free_quit(info *ags);
int tkn(char *line, char *dlim);
int reverse_c(char *s1, char *s2);
int _env(info *ags);
void new_pwd(info *ags);
int _cmd_(info *ags);
ssize_t _readline(info *ags);
void space(char **line, info *ags);
char *_read_env(char **envp, char *env, int length);
int check_input(info *ags);
void check_symbol(char *buffer, char **symbol, info *ags);
char **handle_PWD(info *ags);
int c_dir(info *ags);
char *_malloc(info *ags, int size);
char *mal2(char *line, info *ags, int size);

#endif
