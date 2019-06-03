#include <stdio.h> 
#include <stdlib.h> 
#include <signal.h>

void fun() {
    pid_t pid;
    
    /* Child sleeps until SIGKILL signal received, then dies */
    if ((pid = fork()) == 0) {
        pause(); /* Wait for a signal to arrive */
        printf("control should never reach here!\n");
        exit(0);
    }

    /* Parent sends a SIGKILL signal to a child */
    kill(pid, SIGKILL);
    printf("child killed\n");
    exit(0);
}

int main() {
    fun();
    return 0;
}