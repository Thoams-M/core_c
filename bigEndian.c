#include <stdio.h>
 
int main(void)
{
   short v = 0x0123;
   char *p = (char *) &v;
 
   if(*p == 0x01)
      printf("Big Endian !!");
   else
      printf("Little Endian !!");
 
   return 0;
}
