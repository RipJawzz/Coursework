#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>
void handler(int signum){
    if(signum==SIGTERM){
        fprintf(stderr, "%s\n", "I have been killed\n");
        exit(1);
    }
}

int main(int argc,char *argv[]){
    signal(SIGTERM,handler);
    int maxBufferSize=-2;
    if(strlen(argv[1])==1){
        if(argv[1][0]=='*'){
            maxBufferSize=-1;
        }
    }
    if(maxBufferSize!=-1){
        maxBufferSize = atoi(argv[1]);
        if(maxBufferSize==0){
            exit(2);
        }
    }
    int maxLength = 1000,index=0,input;;
    char s[maxLength];

    while((input=getchar())!=EOF){
        s[index] = input;
        index++;
    }
    s[index] = '\0';
    int count = 0;
    if(maxBufferSize==-1){
        printf("%s\n",s);
    }
    else{
        char temp[maxBufferSize];
        for(int x=0;x<maxBufferSize;x++){
            temp[x] = s[x];
        }
        temp[maxBufferSize] = '\0';
        printf("%s\n",temp);
    }
    for(int x=0;x<index;x++){
        if(!isalpha(s[x])){
            count++;
        }
    }
    fprintf(stderr,"Number of non-alphabetic characters : %d\n",count );
    exit(0);
}
