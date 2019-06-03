#include<stdio.h> 
#include<unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include<stdlib.h>
#include <errno.h>



unsigned int snooze(unsigned int secs);

unsigned int snooze(unsigned int secs)
{
	unsigned int rest = sleep(secs);
	printf("User pressed ctrl + c: \n Slept for %d of %d secs.\n", secs-rest, secs);
	return rest;
}

void handler(int sig)
{
	return;
}


int main(int argc, char *argv[])
{
	if (argc != 2) {
		printf("Need at least 1 argv.\n");
		exit(0);
	}
	
	if (signal(SIGINT, handler) == SIG_ERR)
		printf("Signal error\n");
	
	snooze(atoi(argv[1]));
	
	return 0;
}