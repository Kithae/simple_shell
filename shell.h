#ifndef SHELL_H
#define SHELL_H

#include <stdio.h>
#include <sys/wait.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <stdlib.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <stddef.h>
#include <sys/types.h>
#include "handlers.h"

/**
 * struct info- the programs structure
 * @program_name: a name
 * @input_line: a pointer
 * @cmd_name: pointer to the first command typed by the user
 * @exec_counter: total commands executed
 * @file_descriptor: an input descriptor
 * @tokens: a pointer array
 * @env: environmental values received
 * @map_alias: a pointer array.
 */
typedef struct info
{
	char *program_name;
	char **map_alias;
	char *input_line;
	char *cmd_name;
	char **tokens;
	int exec_counter;
	int file_descriptor;
	char **env;
} input;

/**
 * struct builtins - a structure
 * @builtin: a name
 * @function: a function
 */
typedef struct builtins
{
	char *builtin;
	int (*function)(input *data);
} builtins;


void run_prog(input *data, int arc, char *av[], char **env);
int _readline(input *data);
void process_input(char *query, input *data);
void aug_alias(input *data);
void ctrl_c(int opr UNUSED);
int bf_add(char *buffer, char *str);
int logic_opers(char *array_cmd[], int i, char array_op[]);
void aug_variables(input *data);
int link_program(input *data);
int cmd_execute(input *data);
void parse(input *data);
char **tok_path(input *data);
char *_stringtok(char *line, char *delim);
int list_builtins(input *data);
int exit_builtin(input *data);
int change_dir(input *data, char *new_dir);
void free_pt_array(char **folder);
void free_recur_data(input *data);
void free_full_data(input *data);
int cd_builtin(input *data);
int env_builtin(input *data);
int builtin_undo_env(input *data);
int help_builtin(input *data);
int alias_builtin(input *data);
int builtin_change_env(input *data);
char *list_key(char *name, input *data);
void environ_print(input *data);
int _print(char *string);
int key_set(char *key, char *value, input *data);
int error_print(int errorcode, input *data);
int remove_key(char *key, input *data);
int string_compare(char *string1, char *string2, int number);
int _printerr(char *string);
char *copy_str(char *string);
int string_length(char *string);
char *concat_str(char *string1, char *string2);
void l_to_str(long number, char *string, int base);
void string_reverse(char *string);
int _atoi(char *s);
int alias_print(input *data, char *alias);
int tally_characters(char *string, char *character);
char *read_alias(input *data, char *alias);
int op_alias(char *alias_string, input *data);


#endif
