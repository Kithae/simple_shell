#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

/**
 * _strcpy - copy string
 * @str1: varible
 * @str2: string to be copied
 *
 * Return: NULL
 */

void _strcpy(char* str1, const char* str2)
{
	int i = 0;

	while (str2[i] != '\0')
	{
		str1[i] = str2[i];
		i++;
	}
	str1[i] = '\0';
}

/**
 * envi_var - handle environmental variables
 * @token: string
 *
 * Return: NULL
 */

void envi_var(const char *token)
{
	if (token[0] == '$')
	{
		char varName[50];
		char *envValue;

		_strcpy(varName, token + 1);
		envValue = getenv(varName);

		if (envValue != NULL)
		{
			printf("%s=%s\n", varName, envValue);
		}
		else
		{
			printf("Environmental variable not found: %s\n", varName);
		}
	}
}

/**
 * execute_Cmd - Handles environmental variables
 * @argv: varaible to be checked for env
 * @envp: variable
 *
 * Return: Void
 */
void execute_Cmd(char *argv[], char *envp[])
{
	char path[100];
	char *token = argv[1];
	pid_t pid;
	char *pathname;

	envi_var(token);
	pathname = argv[2];
	sprintf(path, "%s/%s", pathname, token);
	pathname = argv[2];

	if (access(path, F_OK) == 0)
	{
		_print("Exact path: %s\n", path);
	}
	else
	{
		_print("Command not found: %s\n", token);
		return;
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork");
		return;
	}
	else if (pid == 0)
	{
		execve(path, argv + 1, envp);
		perror("execve");
		exit(1);
	}
	else
	{
		int status;

		waitpid(pid, &status, 0);
	}
}
