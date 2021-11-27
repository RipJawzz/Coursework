#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <stdbool.h>
#include <errno.h>
#define FIELD_SIZE 256
void shell_exit(int EXIT_CODE)
{
    exit(EXIT_CODE);
}
void shell_cd(char* path)
{
    chdir(path);
    return;
}
char* shell_pwd(char *shell_cwd)
{
    shell_cwd = getcwd(shell_cwd, FIELD_SIZE);
    return shell_cwd;
}
void shell_echo(int shell_argc, char **shell_argv)
{
    for (int i = 1; i < shell_argc; i++)
    {
        fprintf(stderr, "%s ", shell_argv[i]);
    }
    return;
}
void handle_SIGINT()
{
    fflush(stdin);
    fflush(stdout);
    fflush(stderr);
    write(1, "\n", 1);
}

int main()
{
    signal(SIGINT, handle_SIGINT);
    char *shell_user_home = "home/rip_jawzz/";
    char* shell_cwd = (char *)malloc(sizeof(char)*FIELD_SIZE);
    char* shell_OLDPWD = (char *)malloc(sizeof(char)*FIELD_SIZE);

    while (true)
    {
        shell_cwd = shell_pwd(shell_cwd);
        fprintf(stderr,"\033[0;34m\e[1m%s$ \033[0m\e[0m",shell_cwd);
        char *shell_read_buf = (char *)malloc(sizeof(char)*BUFSIZ);
        ssize_t bytes_read;
        char c;
        ssize_t j;
        while (bytes_read = read(STDIN_FILENO, shell_read_buf, BUFSIZ))
        {
            if (shell_read_buf[bytes_read-1] == '\n')
            bytes_read = 0;

            if (bytes_read == 0)
            break;

            if (bytes_read == -1)
            {
                fprintf(stderr, "\033[0;31m\e[1mERROR in reading command from STDIN | errno : %d\n\033[0m\e[0m",errno);
                exit(1);
            }
        }
        char* shell_t_buf = (char *)malloc(sizeof(char)*FIELD_SIZE);
        strcpy(shell_t_buf,shell_read_buf);
        int fd[2];
        bool toggle = true;
        char *shell_EOCmd = ";\n";
        char *shell_EOSubCmd = "|";
        char *shell_EOArg = " \t";
        char *t_str_1, *t_str_2, *t_str_3, *t_cmd_stmnt, *t_subcmd_stmnt, *t_args, *t_saveptr_1, *t_saveptr_2, *t_saveptr_3;

        for ( t_str_1 = shell_read_buf;     ;t_str_1 = NULL)
        {
            t_cmd_stmnt = strtok_r(t_str_1, shell_EOCmd, &t_saveptr_1);
            if (t_cmd_stmnt == NULL)
            break;


            for (t_str_2 = t_cmd_stmnt;      ;t_str_2=NULL)
            {
                t_subcmd_stmnt = strtok_r(t_str_2, shell_EOSubCmd, &t_saveptr_2);
                if (t_subcmd_stmnt == NULL)
                break;

                int shell_argc = 0;
                char **shell_argv = (char **)malloc(sizeof(*shell_argv)*8);
                for (int i = 0; i < 8; i++){
                    (*shell_argv) = (char *)malloc(sizeof(char)*FIELD_SIZE);
                }
                for (t_str_3 = t_subcmd_stmnt;;t_str_3=NULL)
                {
                    t_args = strtok_r(t_str_3, shell_EOArg, &t_saveptr_3);
                    if (t_args == NULL)
                    {
                        break;
                    }
                    shell_argv[shell_argc++]=t_args;
                }
                for (int i = 0; i < shell_argc; i++)
                {
                    if (!strcmp((const char*)shell_argv[i], "&"))
                    {
                        pid_t pid;
                        fprintf(stderr, "\033[0;30m\e[1mProcess running in background | pid : %d\n\033[0m\e[0m",getpid());
                        if ((pid = fork()) == 0) {
                            if(execvp(strcat("./",shell_argv[0]),shell_argv) <0)
                                fprintf(stderr, "\033[0;31m\e[1mERROR in reading command source | errno : %d\n\033[0m\e[0m",errno);
                                shell_argv = (shell_argv+i+1);
                            exit(0);
                        }
                        wait(0);
                    }
                }

                if (!strcmp((const char*)shell_argv[0], "exit"))
                {
                    toggle = false;
                    shell_exit(0);
                }
                else if (!strcmp((const char*)shell_argv[0], "cd"))
                {
                    toggle = false;
                    if (shell_argc == 1)
                    {
                        strcpy(shell_OLDPWD, shell_cwd);
                        strcpy(shell_cwd,shell_user_home);
                        shell_cd(shell_cwd);
                    }
                    else if (shell_argc != 2)
                    {
                        fprintf(stderr,"\033[0;30m\e[1margument count doesn't match\n\033[0m\e[0m");
                        break;
                    }
                    else if (!strcmp(shell_argv[1],"-"))
                    {
                        fprintf(stderr,"%s\n",shell_OLDPWD);
                        shell_cd(shell_OLDPWD);
                        strcpy(shell_OLDPWD, shell_cwd);
                    }
                    else
                    {
                        strcpy(shell_OLDPWD, shell_cwd);
                        shell_cd(shell_argv[1]);
                    }
                    break;
                }
                else if (!strcmp((const char*)shell_argv[0], "pwd"))
                {
                    toggle = false;
                    fprintf(stdout , "%s\n" ,shell_cwd);
                    break;
                }
                else if (!strcmp((const char*)shell_argv[0], "source"))
                {
                    toggle = false;
                    char t_cmd[128] = ". ./";
                    strcat(t_cmd,shell_argv[1]);
                    system(t_cmd);
                    break;
                    pid_t pid;
                    if ((pid = fork()) == 0) {
                        if(execvp(strcat("./",shell_argv[1]),shell_argv) <0)
                            fprintf(stderr, "\033[0;31m\e[1mERROR in reading command source | errno : %d\n\033[0m\e[0m",errno);
                        exit(0);
                    }
                    else
                    {
                        wait(0);
                    }
                }
                break;
                if (!strcmp((const char*)shell_argv[0],"echo"))
                {
                    shell_echo(shell_argc, shell_argv);
                }
                else
                {
                    pid_t pid;
                    int status;
                    if ((pid = fork()) < 0)
                    {
                        fprintf(stderr , "\033[0;31m\e[1mERROR creating child process to run the input command | errno : %d\n\033[0m\e[0m",errno);
                        break;
                    }
                    else if (pid == 0)
                    {
                        pipe(fd);
                        close(fd[0]);
                        dup2(fd[0],STDIN_FILENO);
                        int fd_in,fd_out;
                        for (int i = 0; i < shell_argc; i++)
                        {
                            if (!strcmp((const char*)shell_argv[i], "<"))
                            {
                                fd_in = open(shell_argv[i+1], O_RDONLY);
                                dup2(fd_in,STDIN_FILENO);
                                strcpy(shell_argv[i],"");
                                strcpy(shell_argv[i+1],"");
                            }

                            if (!strcmp((const char*)shell_argv[i], ">"))
                            {
                                fd_out = creat(shell_argv[i+1], 0644);
                                dup2(fd_out,STDOUT_FILENO);
                                strcpy(shell_argv[i],"");
                                strcpy(shell_argv[i+1],"");
                            }

                        }

                        if( execvp((const char*)shell_argv[0], shell_argv) < 0 )
                        {
                            fprintf(stderr, "shell: %s: command not found\n",shell_argv[0]);
                        }
                        close(fd_in);
                        close(fd_out);

                        exit(0);
                    }
                    else
                    {
                        wait(&status);
                    }
                }
            }
            break;
        }
        if (toggle)
        {
            system(shell_t_buf);
        }
    }
return 0;
}
