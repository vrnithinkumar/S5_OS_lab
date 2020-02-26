
/*----------------------------------------------------------*/
/* Code Purpose:For implementing pipe using fork()          */
/*                                                          */
/*          Auther: VR<vrnithinkumar@gmail.com>             */
/*----------------------------------------------------------*/

#include <sys/wait.h>
#include <unistd.h>
#include <stdio.h>

void run(char *cmd) {            // to executive Systen inbuilt functions
   char *args[2];
   args[0] = cmd;
   args[1] = NULL;

   execvp(cmd, args);
}
void Close_Pipe(int *fds)
{ 
 close(fds[0]);
 close(fds[1]);
}

int main(int argc,char *argv[]) {
	 
    int pfd[2];           //File descripter for pipe
    pipe(pfd);                //creating pipes
    char lss[]="ls";
    char sorts[]="sort";

    pid_t pid_a, pid_b;   //process ids for two process

    chdir(argv[1]);          //Moving to Given directory

if ((pid_a = fork())==0)      //true only if pid_a is 0 means in child process 
{
    dup2(pfd[1], 1);    //duping standard output (file des 1) to one end of the pipe(pfd[1])
    Close_Pipe(pfd);
    run(lss);
}

if ((pid_b = fork())==0) 
{
    dup2(pfd[0], 0);   //duping  standard input (file des 0) to another end of the pipe(pfd[0])
    Close_Pipe(pfd);
    run(sorts);
}
Close_Pipe(pfd);
waitpid(pid_a, NULL, 0); // waiting for child process to complete
waitpid(pid_b, NULL, 0); //waiting for child process to complete

    return 0;
}
