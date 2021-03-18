#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdlib.h>
#include <string.h>

void term(int signum)
{
	if (signum != SIGTERM)
	{
		exit(-1);
	}
	FILE *file_ptr;
	if (!(file_ptr = fopen("sigworks", "w")) )
	{
		printf("Error while creating file :%s\n", "sigworks");
		exit(-1);
	}
	fprintf(file_ptr, "That sig works !\n");
	fclose(file_ptr);
	// exit(0);

}

void exit_prgrm(int signum)
{
	// exit(-1);
	// sleep(10);
	printf("CTRL-C signal !\n");
	exit(-1);
}

void	create_file()
{
	sleep(10);
	FILE *file_ptr;
	if (!(file_ptr = fopen("Thatworeeeeks", "w")) )
	{
		sleep(10);
		printf("Error while creating file :%s\n", "Thatworks");
		exit(-1);
	}
	sleep(10);
	fprintf(file_ptr, "That perfectly works !\n");
	fclose(file_ptr);
}

int main(void)
{
	
	signal(SIGTERM, term);
	
	signal(SIGINT, exit_prgrm);
	// signal(SIGKILL, exit_prgrm);
	// struct sigaction action;
	// memset(&action, 0, sizeof(action));
	// action.sa_handler = term;
	// sigaction(SIGTERM, &action, NULL);

	create_file();
	return (0);
}