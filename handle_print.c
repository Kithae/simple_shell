#include "shell.h"

/**
 * _print - a function that displays character arrays
 * in our specified standard output
 * @string: a pointer
 * Return: total bytes written, else -1
 */

int _print(char *string)
{

/*we use the write system call to output the string contents*/
/* to file descriptor 1*/
return (write(STDOUT_FILENO, string, string_length(string)));
}
/**
* _printerr - a function for displaying errors for the above (if any)
* @string: a pointer
* Return: total bytes written, else -1
*/
int _printerr(char *string)
{
/* we use the write system call to output the string contents*/
/* to file descriptor 2 */
return (write(STDERR_FILENO, string, string_length(string)));
}

/**
* error_print - a function for displaying errors as an array (if any)
* @data: a structure pointer
* @errorcode: the error
* Return: total bytes written, else -1
*/
int error_print(int errorcode, input *data)
{
char no_string[10] = {'\0'};

l_to_str((long) data->exec_counter, no_string, 10);

/* a loop to determine if error code is 2 or 3*/
if (errorcode == 2 || errorcode == 3)
{
_printerr(data->program_name);
_printerr(": ");
_printerr(no_string);
_printerr(": ");
_printerr(data->tokens[0]);
if (errorcode == 2)
_printerr(": Illegal number: ");
else
_printerr(": can't cd to ");
_printerr(data->tokens[1]);
_printerr("\n");
}
else if (errorcode == 127)
{
_printerr(data->program_name);
_printerr(": ");
_printerr(no_string);
_printerr(": ");
_printerr(data->cmd_name);
_printerr(": not found\n");
}
else if (errorcode == 126)
{
_printerr(data->program_name);
_printerr(": ");
_printerr(no_string);
_printerr(": ");
_printerr(data->cmd_name);
_printerr(": Permission denied\n");
}
return (0);
}
