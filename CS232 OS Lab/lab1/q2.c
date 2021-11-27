#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int main()
{
    char c;
    int count = 0;
    while (1){
      c = getchar();
      if(c==EOF)
        break;
      if (!isalpha(c)){
        count++;
      }
      putchar(c);
    }
    fprintf(stderr,"%d\n", count);
    exit(0);
}
