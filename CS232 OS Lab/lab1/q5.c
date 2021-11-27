#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <setjmp.h>
#include <signal.h>
#include <sys/types.h>
#include <string.h>
#include <sys/wait.h>
#include <sys/stat.h>

jmp_buf st;

void handler(int);


int main(int argc,char *argv[]){
	int maxBufferSize=-1,inputFile=-1,outputFile=-1,status,flag_numberFound = 0,flag_inputFileFound = 0;
	char temp[1000];
	for(int x=1;x<argc;x++){
		if(argv[x][0]=='-'){
			if(flag_numberFound==1){
				fprintf(stderr,"Only one numberic argument is allowed!\n");
				exit(1);
			}
			else{
				flag_numberFound=1;
				int n = strlen(argv[x]),index=0;
				for(int y=1;y<n;y++,index++){
					temp[index] = argv[x][y];
				}
				temp[n-1] = '\0';
				maxBufferSize = atoi(temp);
			}
		}
		else{
			if(flag_inputFileFound==0){
				close(0);
				inputFile = open(argv[x],O_RDONLY);
    		dup(inputFile);
    	  flag_inputFileFound++;
			}
			else if(flag_inputFileFound==1){
				close(1);
				outputFile = creat(argv[x],0644);
				dup(outputFile);
			}
			else if(flag_inputFileFound>1){
				fprintf(stderr,"maximum two files allowed!\n");
				exit(1);
			}
		}
	}
	fprintf(stderr, "%d %d %d\n",maxBufferSize,inputFile,outputFile );

	int fd[2];
	if(pipe(fd)==-1){
        fprintf(stderr,"pipe not created\n");
        exit(1);
    }
    pid_t p_child1;
    p_child1=fork();

    if(p_child1<0){
        fprintf(stderr,"Fork for child 1 failed\n");
        exit(1);
    }
    else if(p_child1>0) {
    	pid_t p_child2;
    	p_child2=fork();
    	if(p_child2<0){
    		fprintf(stderr, "%s\n", "Error on forking 2nd child");
            exit(1);
    	}
    	else if(p_child2>0){
    		close(fd[1]);
        close(fd[0]);
    		signal(SIGALRM,handler);
    		if(setjmp(st)!=0){
    			kill(p_child1,SIGTERM);
    			kill(p_child2,SIGTERM);
    			wait(NULL);
    			wait(NULL);
    		}
    		alarm(15);
    		int pid;
    		while((pid=wait(&status))>0){
    			fprintf(stderr, "child pid=%d reaped with exit status=%d\n",pid,WEXITSTATUS(status) );
    			if(pid==p_child1 && WEXITSTATUS(status)==2){
    				fprintf(stderr, "%s\n", "SIGPIPE detected, so killing child 2");
    				kill(p_child2,SIGTERM);
    				wait(NULL);
    				exit(1);
    			}
    		}
    		alarm(0);
    		exit(0);
    	}
    	else{
    		fprintf(stderr,"Child 2 pid %d\n",getpid() );
    		close(1);
        dup(fd[1]);
        execl("child2_q5_helper", "child2_q5_helper",(char *) 0);
    	}
    }
    else{
    	fprintf(stderr,"Child 1 pid %d\n",getpid() );
    	close(fd[1]);
    	close(0);
    	dup(fd[0]);
        if(maxBufferSize==-1){
        	execl("child1_q5_helper", "child1_q5_helper","*", (char *) 0);
        }
        else{
        	execl("child1_q5_helper", "child1_q5_helper",temp, (char *) 0);
        }
    }
	exit(0);
}

void handler(int signum){
	if(signum==SIGALRM){
		fprintf(stderr, "%s\n","read timeout in second child, killing both children.\n");
		longjmp(st,1);
		exit(1);
	}
}
