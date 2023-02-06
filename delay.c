#include <stdio.h>
#include <unistd.h>

int main()
{

 char c;
for(;;)   
   {
     c=getc(stdin);
     if (c == EOF) return 0;
     usleep(15152); // (1/66 rounded) Delay
     printf("%c",c);
     fflush(stdout);
   }
 return 0;
}
