#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>

#define MAX_COMMAND_LENGTH 128
/**
 * prompt - function
 *
 * Return: nothing
 *
 */
void prompt(void)
{
	printf("> ");
	fflush(stdout);
}
/**
 *read_input - function for read
 *
 *Return: nothing
 *
 */
char *read_input(void)
{
	char *buffer = NULL;
	size_t bufsize = 0;

	if (getline(&buffer, &bufsize, stdin) == -1)
	{
		if (feof(stdin))
		{
			printf("\n");
			exit(EXIT_SUCCESS);
		}
		else
		{
		perror("Error reading input");
		exit(EXIT_FAILURE);
		}
	}
	buffer[strcspn(buffer, "\n")] = '\0';
	return (buffer);
}
/**
 *main - entry point
 *Description: 'the program's description'
 *
 *
 *Return: nothing
 */

int main(void)
{
	char *command = NULL;
	 pid_t child_pid;


	while (1)
	{
		prompt();
		command = read_input();
		if (strcmp(command, "exit") == 0)
		{
			free(command);
			printf("\n");
			break;
		}
		if (strlen(command) == 0)
		{
		free(command);
		continue;
		}
		child_pid = fork();
		if (child_pid == 0)
		{
			execve(command, &command, environ);
			perror("Failed to execute command");
			exit(EXIT_FAILURE);
		}
		else if (child_pid > 0)
		{
		wait(NULL);
		free(command);
		}
		else
		{
		perror("Error while forking");
		exit(EXIT_FAILURE);
		}
	}
	return (EXIT_SUCCESS);
}
