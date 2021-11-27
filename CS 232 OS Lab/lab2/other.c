#include<stdio.h>
#include<errno.h>
#include<stdlib.h>
#include<string.h>
#include<fcntl.h>
#include<sys/wait.h>
#include<sys/types.h>
#include<dirent.h>
#include<unistd.h>
#define MAG "\x1B[35m"
#define YEL "\x1B[33m"
#define WHT "\x1B[37m"
char** BreakCommand(char* str){
        char **tokens=(char**)malloc(64*sizeof(char*));
        char* token;

        int j=0;
        while((token=strtok_r(str," ",&str))){
                tokens[j]=(char*)malloc(64*sizeof(char));
                strcpy(tokens[j++],token);
        }
        return tokens;
}
char*** PipingCommands(char** input,int* n){
        char*** pipeTokens =(char***)malloc(3*sizeof(char**));
        for(int i=0;i<3;i++){
                pipeTokens[i]=(char**)malloc(1000*sizeof(char*));
        }
        char* line=(char*)malloc(1000*sizeof(char*));
        int index=0,k=0,i=0,size=0;

        while(input[k]!=NULL){
                size++;
                k++;
        }

        for(int j=0;j<size;j++){
      if((strcmp(input[j],"|"))==0 ||  (strcmp(input[j],";")==0))
           {
                   ++(*n);
                   i=0;

           }else{

                   pipeTokens[*n][i]=(char*)malloc(100*sizeof(char));
                   strcpy(pipeTokens[*n][i++],input[j]);
           }

        }
        ++(*n);

        return pipeTokens;
}
void CreateProcess(int in,int out,char** pipeTokens){
        if(!fork()){
        dup2(in,0);
        close(in);

        dup2(out,1);
        close(out);
        execvp(pipeTokens[0],pipeTokens);
        }
}
void CreatePipe(char*** pipeTokens,int n){
        int fd[2],in=0;
        for(int i=0;i<n-1;i++){
                pipe(fd);
                CreateProcess(in,fd[1],pipeTokens[i]);
                close(fd[1]);
                in=fd[0];

        }
        dup2(in,0);
        execvp(pipeTokens[n-1][0],pipeTokens[n-1]);

}
void MultipleCommands(char*** pipeTokens,int n){
  int fd[2];
  for(int i=0;i<n;i++){
    int frk=fork();
    if(frk==0){
      execvp(pipeTokens[i][0],pipeTokens[i]);
    }else{
      wait(NULL);
    }
  }
}
void handler(int sig){
        int keepRunning=1;
        //fflush(stdout);
}
int main(int argc,char** argv){
        char* input=(char*)malloc(1000*sizeof(char));
        char* str;
        int k;
        char *token;
        char** tokens;


        char *filepath;
        int fd,n,i=0,j=0;
        signal(SIGINT,handler);
        if(argc==2){
                fd=open(argv[1],O_RDONLY);
                if(fd<0){
                        fprintf(stderr,"File doesn't exist");
                        exit(1);
                }
        }
        int keepRunning=1;
        while(keepRunning){

                DIR* dr=NULL;
                int k=0,flag=0;
                struct dirent *de=NULL;
                filepath=getcwd(filepath,1000);

                if(argc==2){
                        n=read(fd,input,1000);
                }else{
                   printf("%sDa hood:~%s$%s",MAG,filepath,WHT);
                   scanf("%[^\n]",input);
                   getchar();
        }

                str=input;

                tokens=BreakCommand(str);

                while(tokens[k]!=NULL){
                        if(strcmp(tokens[k],"|")==0){
                                flag=1;
                                break;
                        }else if(strcmp(tokens[k],";")==0){
                          flag=2;
                          break;
                        }
                        k++;
                }
     char*** pipeTokens;
                if(tokens[0]==NULL){
                        continue;
                }
                else if(flag==1){

                        int n=0;
                        pipeTokens= PipingCommands(tokens,&n);
                        CreatePipe(pipeTokens,n);

                }
                else if(flag==2){
                  int m=0;
                  pipeTokens=PipingCommands(tokens,&m);
                  MultipleCommands(pipeTokens,m);
                }
                else if(strcmp(tokens[0],"source")==0)
          {

                  int f = fork();
                   if(f<0)
                           fprintf(stderr,"Error in forking");
                   else  if(f==0)
                   {
                      int fd = open(tokens[1],O_RDONLY);
                     close(0);
                     dup(fd);
                     execl("driver","driver",NULL);
                   }
                   else
                           wait(NULL);
          }
                else if((strcmp(tokens[0],"exit"))==0){
                      break;
                      exit(0);
                }
                else if((strcmp(tokens[0],"pwd"))==0){
                       printf("%s\n",filepath);
 }else if((strcmp(tokens[0],"cd"))==0){
                        int res=chdir(tokens[1]);
                        if((res!=0)){
                                switch(res){
                                case EACCES:
                                        fprintf(stderr,"search permission is denied");
                                             break;
                                case EIO:fprintf(stderr,"an I/O error occured");
                                         break;
                                case ENOENT:fprintf(stderr,"file doesn't exist");
                                             break;

                                 default:fprintf(stderr,"couldn't find directory");

                                }
                        }

                }else if((strcmp(tokens[0],"echo")==0)){
                    int c;
                     while((c=getchar())!='\n'){
                             putchar(c);
                     }

                }
  else if((strcmp(tokens[0],"cat")==0)){
                        int f,f_out,n,j=0;
                        char buffer[1000];
                        while(tokens[j]!=NULL){
                                j++;
                        }

                        if(j==2){
                                f=open(tokens[1],O_RDONLY);
                                if(f==-1)fprintf(stderr,"file not found");
                                else{
                                        n=read(f,buffer,1000);
                                        write(1,buffer,n);
                                }
                        }
                        else if(((strcmp(tokens[1],"<"))==0)&& j==3){
                            f=open(tokens[2],O_RDONLY);
                            if(f==-1){
                                    fprintf(stderr,"file not found");
                            }else{
                                    n=read(f,buffer,1000);
                                    write(1,buffer,n);
                            }
  }else if(((strcmp(tokens[2],">"))==0)&&( j==4)){

                     if(f==-1){
                             fprintf(stderr,"file not found");
                     }else{

                             f_out=open(tokens[3],O_WRONLY);
                             if(f_out<0)fprintf(stderr,"destination file is not present");
                             n=read(f,buffer,1000);
                             write(f_out,buffer,n);
                     }
                    }
                     else if((strcmp(tokens[1],">")==0)&&j==3){
                            int n=read(0,buffer,1000);
                            f_out=open(tokens[2],O_WRONLY,O_CREAT);
                            write(f_out,buffer,n);
   }else if((strcmp(tokens[1],"<")==0) && (strcmp(tokens[3],">")==0) && j==5){
                            f=open(tokens[2],O_RDONLY);
                            if(f==-1){
                                    fprintf(stderr,"file not found");
                            }else{
                                    f_out=open(tokens[4],O_WRONLY);
                                    if(f_out<0)fprintf(stderr,"destination file is not present");
                                    n=read(f,buffer,1000);
                                    write(f_out,buffer,n);
                            }
                    }else{

                            printf("\n");
                    }



                    printf("\n");
                }
       else{
                        int n=0;
                        while(tokens[n]) n++;
                        int fk =fork();
                        if(fk<0){
                                fprintf(stderr,"command can't be executed");
                        }else if(fk>0){
                                if(strcmp(tokens[n-1],"&")==0){
                                        continue;
                                }else{
                                        wait(NULL);
                                }
                        }else if(fk==0){
                               if(strcmp(tokens[n-1],"&")==0){
                                       tokens[n-1]=NULL;
                               }
                               execvp(tokens[0],tokens);
                        }
                }


        }
        return 0;
}
