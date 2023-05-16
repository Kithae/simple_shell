#include "shell.h"
/**
 * main - A function to initialize the program variables
 * @ac: number of arguments received
 * @av: the argument values
 * @env: environmental values received
 * Return: 0.
 */
int main(int ac, char *env[], char *av[])
{
/*a custom defined structure that initializes to null*/
input data_struct = {NULL}, *data = &data_struct;
	char *query = "";

/*to initialize the program*/
	run_prog(data, ac, av, env);

/*a signal handler*/
	signal(SIGINT, ctrl_c);

/*interactive mode checks*/
	if (isatty(STDIN_FILENO) && isatty(STDOUT_FILENO) && ac == 1)
	{
		errno = 2;/*???????*/
		query = PROMPT_MSG;
	}
	errno = 0;
	process_input(query, data);
	return (0);
}

/**
 * ctrl_c - A function to print shell prompts in new lines
 * for (ctrl + c) command
 * @UNUSED: a prototype option
 */
void ctrl_c(int opr UNUSED)
{
	_print("\n");
	_print(PROMPT_MSG);
}

/**
 * run_prog - a function to run the proposed program structures
* with the information provided
 * @data: a structure pointer
 * @av: the argument values
 * @env: environmental values received
 * @ac: number of arguments received
 */
void run_prog(input *data, int ac, char *av[], char **env)
{

/*to read user input and execute the commands*/
	int a = 0;

	data->program_name = av[0];
	data->input_line = NULL;
	data->cmd_name = NULL;
	data->exec_counter = 0;

	if (ac == 1)
		data->file_descriptor = STDIN_FILENO;
	else
	{
		data->file_descriptor = open(av[1], O_RDONLY);
		if (data->file_descriptor == -1)
		{
			_printerr(data->program_name);
			_printerr(": 0: Can't open ");
			_printerr(av[1]);
			_printerr("\n");
			exit(127);
		}
	}
	data->tokens = NULL;
	data->env = malloc(sizeof(char *) * 50);
	if (env)
	{
		for (; env[a]; a++)
		{
			data->env[a] = copy_str(env[a]);
		}
	}
	data->env[a] = NULL;
	env = data->env;

	data->map_alias = malloc(sizeof(char *) * 20);
	for (a = 0; a < 20; a++)
	{
		data->map_alias[a] = NULL;
	}
}
/**
 * process_input - a function with a loop to execute the above prompt.
 * @query: the printable prompt
 * @data: a structure pointer
 */
void process_input(char *query, input *data)
{
	int status = 0, length = 0;

	while (++(data->exec_counter))
	{
		_print(query);
		status = length = _readline(data);

		if (status == EOF)
		{
			free_full_data(data);
			exit(errno);
		}
		if (length >= 1)
		{
			aug_alias(data);
			aug_variables(data);
			parse(data);
			if (data->tokens[0])
			{
				status = cmd_execute(data);
				if (status != 0)
					error_print(status, data);
			}
			free_recur_data(data);
		}
	}
}
