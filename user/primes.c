#include "kernel/types.h"
#include "kernel/stat.h"
#include "user/user.h"

void redict(int fd[]){
    close(0);
    close(fd[1]);
    dup(fd[0]);
    close(fd[0]);
}

void primes(){
    int p;
    int n;
    int pipe_right[2];
    pipe(pipe_right);

    read(0, &p, sizeof(int));
    printf("primes: %d\n", p);

    // 31之后还输出了一串 0 47个0？？

    if(fork()==0){
        redict(pipe_right);
        primes();
    }else{
        close(pipe_right[0]);
        while((read(0, &n, sizeof(int))) > 0){
            if(n % p){
                write(pipe_right[1], &n, sizeof(int));
            }
        }
        close(pipe_right[1]);
        // 写wait和不写的差异 ；不写wait 子进程可以不写 exit？？
        wait();
    }
    exit();
}

int
main(int argc, char *argv[])
{
    int root_fd[2];
    pipe(root_fd);

    if(fork()==0){
        redict(root_fd);
        primes();
    }else{
        close(root_fd[0]);
        for(int i = 2; i < 35; i++){
            write(root_fd[1], &i, sizeof(int));
        }
        close(root_fd[1]);
        wait();

    }
    exit();
    return 0;
}