#include "shell.h"
/**
* cmd_execute - A function for executing a command wholly
* (including its path variables).
* @data: a structure pointer
* Return: 0 else, -1
*/
int cmd_execute(input *data)
{
/* the 2 integer variables store the return values */
/* pid_t variable stores the child process id below */
int a = 0, status;
pid_t chp;
/* we call list_builtins function to check for builtin cmds */
a = list_builtins(data);
if (a != -1)
return (a);

/* we call link_program function to check for existing PATH variables */
a = link_program(data);
if (a)
{
return (a);
}
else
{
/* we create the child process using ‘fork()’ */
chp = fork();
if (chp == -1)
{
perror(data->cmd_name);
exit(EXIT_FAILURE);
}
if (chp == 0)
{
a = execve(data->tokens[0], data->tokens, data->env);
if (a == -1)
perror(data->cmd_name), exit(EXIT_FAILURE);
}
else
{
wait(&status);
if (WIFEXITED(status))
errno = WEXITSTATUS(status);
else if (WIFSIGNALED(status))
errno = 128 + WTERMSIG(status);
}
}
return (0);
}
