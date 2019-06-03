#include <stdio.h> 
#include <stdlib.h> 
#include <unistd.h> 
#include <sys/types.h> 
#include <sys/wait.h> 

void fun() 
{ 
    int i, stat; 
    pid_t pid[10]; 
    for (i=0; i<10; i++) 
    { 
        if ((pid[i] = fork()) == 0) 
        { 
            printf("The process id of %d is %d\n",i, getpid());
            exit(i + 0);
        } 
    } 
  
    // using waitpid to exit a child process
    for (i=0; i<10; i++) 
    { 
        pid_t cpid = waitpid(pid[i], &stat, 0); 
        if (WIFEXITED(stat)) 
            printf("Child %d terminated with status: %d\n",cpid, WEXITSTATUS(stat)); 
    } 
} 
  
// Driver code 
int main() 
{ 
    fun(); 
    return 0; 
} 