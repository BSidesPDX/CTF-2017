#include <stdio.h>
#include <string.h>
#include <stdlib.h>

//run xor.py and get the ord string
int ords[] = {};


void decode(char *chr)
{
    *chr = (char)(*chr ^ 0x41);
}

void secret()
{
   char str[16];
   int i = 0;
   if (fgets(str, 16, stdin) != NULL)
   {
        if (strlen(str) != 15)
           exit(0);
        for (i=0;i<strlen(str);i++)
        {
            decode(&str[i]);    
        }
   }
    
   for (i=0; i<strlen(str);i++)
    {
        if (ords[i] != str[i])
           exit(0);
    }
    printf("Yo ho, Yo ho, A Pirates Life For ME!\n");
}

int main()
{
    secret();
}
