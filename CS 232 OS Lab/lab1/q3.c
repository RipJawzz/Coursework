#include <stdio.h>
#include <ctype.h>
#include <stdlib.h>
int main()
{
    char c;
    while (1){
        c = getchar();
        if(c==EOF)
          break;
        if (isupper(c)){
            c = tolower(c);
        }
        else if (islower(c)){
            c = toupper(c);
        }
        putchar(c);
    }
    exit(0);
}
