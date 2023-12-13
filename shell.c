#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#define MAX_COMMAND_LENGTH 128
/**
 * prompt - function
 * main - function
 *
 * Return: nothing
 */
void prompt(void)
{
	printf("> ");
	fflush(stdout);
}
int main(void)
{
	char command[MAX_COMMAND_LENGTH];

	while (1)
	{
		prompt();
		if (fgets(command, MAX_COMMAND_LENGTH, stdin) == NULL)
		{
			if (feof(stdin))
			{
			printf("\n");
			break;
	}
			else
			{
				perror("Error reading input");
				break;
			}
		}
		command[strcspn(command, "\n")] = '\0';
		if (strlen(command) == 0)
		{
		continue;
		}
		if (fork() == 0)
		{
			if (execlp(command, command, NULL) == -1)
			{
				perror("Failed to execute command");
				exit(EXIT_FAILURE);
			}
		}
		else
			wait(NULL);
	}
	return (0);
}
