#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"
#define MSGSIZE 14 
char* msg1 = "received ping"; 
char* msg2 = "received pong"; 

int
main(int argc, char *argv[])
{
    char inbuf[MSGSIZE];
    // fork error??
    int parent_fd[2];
    int child_fd[2];
    // pipe error??
    pipe(parent_fd);
    pipe(child_fd);
    
    if(fork() == 0){
        // child process
        close(parent_fd[1]);
        read(parent_fd[0], inbuf, MSGSIZE);
        printf("%d: %s\n", getpid(), inbuf); // recived ping d
        close(parent_fd[0]);

        close(child_fd[0]);
        write(child_fd[1], msg2, MSGSIZE);
        close(child_fd[1]);

        exit();
    }else{
        // prarent process
        close(parent_fd[0]);
        write(parent_fd[1], msg1, MSGSIZE);
        close(parent_fd[1]);

        wait();

        close(child_fd[1]);
        read(child_fd[0], inbuf, MSGSIZE);
        printf("%d: %s\n", getpid(), inbuf);
        close(child_fd[0]);

        exit();
    };

    return 0;
}