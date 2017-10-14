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
   int len = (sizeof(ords)/sizeof(ords[0]))+1;
   char str[len];
   int i = 0;
   if (fgets(str, len, stdin) != NULL)
   {
        if (strlen(str) != len-1)
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
