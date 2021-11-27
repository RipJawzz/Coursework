#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <fcntl.h>
#include <unistd.h>
#include <sys/wait.h>

#define Q2 "b"
#define Q3 "c"

int main(int argc, char *argv[])
{
    if (argc != 3)
    {
        fprintf(stderr,"%s","ERR:- Only 2 arguments required!\n");
        exit(1);
    }

    int fd_in = open(argv[1], O_RDONLY);
    int fd_out = creat(argv[2], 0644);
    if (fd_in < 0)
    {
        fprintf(stderr,"%s", "ERROR : file to be read does not exist!\n");
        exit(1);
    }

    if (fd_out < 0)
    {
        fprintf(stderr,"%s", "ERROR : file could not be created!\n");
        exit(1);
    }

    close(0);
    if(dup(fd_in) < 0){
        fprintf(stderr , "ERROR assigning STREAM 0 to fd_in");
        exit(1);
    }
    close(fd_in);

    close(1);
    if(dup(fd_out) < 0){
        fprintf(stderr , "ERROR assigning STREAM 1 to fd_out");
        exit(1);
    }
    close(fd_out);

    int fd[2];

    pipe(fd);

    pid_t pid_child_1, pid_child_2;
    int status;

    if ((pid_child_1 = fork()) != 0)
    {
        if ((pid_child_2 = fork()) != 0)
        {
            close(fd[0]);
            close(fd[1]);
            wait(&status);
            wait(&status);
        }
        else
        {
            dup2(fd[1],1);
            close(fd[0]);
            execl(Q3,Q3, (char*) NULL);
            exit(0);
        }
    }

    else
    {
        dup2(fd[0],0);
        close(fd[1]);
        execl( Q2 , Q2 ,(char*) NULL);
        exit(0);
    }

    exit(0);
}
