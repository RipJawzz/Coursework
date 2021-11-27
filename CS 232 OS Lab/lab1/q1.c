#include<stdio.h>
#include<stdbool.h>
int main(int argc, char** argv)
{
    bool skip=false;
    if(argc>=2){
      for(int i=1;i<argc;i++){
        if(argv[i][0]!='-'){
          skip=true;
          printf("%s ",argv[i]);
        }
      }
    }
    if(skip)
      printf("\n");
    return 0;
}
