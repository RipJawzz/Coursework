#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>
#include <signal.h>

void handler(int signum){
    if(signum==SIGPIPE){
        fprintf(stderr, "%s\n", "I've been killed because my pipe reader died!\n");
        exit(2);
    }
    if(signum==SIGTERM){
        fprintf(stderr, "%s\n", "I have been killed\n");
        exit(1);
    }
}

int main(){
    signal(SIGPIPE,handler);
    signal(SIGTERM,handler);
    int maxLength = 1000;
    char s[maxLength];
    int index=0;
    int input;
    while((input=getchar())!=EOF){
        s[index] = input;
        index++;
    }
    s[index] = '\0';
    char modified[index];
    for(int x=0;x<index;x++){
        if(isalpha(s[x])){
            if(isupper(s[x])){
                modified[x] = tolower(s[x]);
            }
            else{
                modified[x] =  toupper(s[x]);
            }
        }
        else{
            modified[x] = s[x];
        }
    }
    modified[index] = '\0';
    write(STDOUT_FILENO,modified,strlen(modified));
    exit(0);
}
