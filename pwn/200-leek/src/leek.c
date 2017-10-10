#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

int SIZE = 1000;

void copyAndWriteMessage(char *writeMessage, FILE *stdout)
{
    char temp[100];
    strcpy(temp, writeMessage);
}

void displayName()
{
    char name[100];
    scanf("%100[^\n]", name);
    fprintf(stdout, name);
}

void challengeInit() 
{
    char selection = '0';
    char writeMessage[SIZE];
    char *prompt =  "\
                    BETA BETA BETA BETA BETA BETA \n\
                    Would you like to play a game? \n\
                    Please select an option followed by your message: \n\
                    1 - Name game \n\
                    2 - Write message \n\
                    3 - exit \n";
    
    char *message = "\nEnter an option \n";
   
    fprintf(stdout, "%s", prompt);
    
    for (;;)
    {
        fprintf(stdout,"%s", message);
        fflush(stdout);
        scanf("%c", &selection);
        switch (selection) 
        {
            case 49:
                fprintf(stdout, "\nEnter your name \n");
                fflush(stdout);
                displayName();
                fflush(stdout);
                break;

            
            case 50:
                fprintf(stdout, "\nNot implemented\n");
                scanf("%1000[^\n]", writeMessage);
                copyAndWriteMessage(writeMessage, stdout);
                fflush(stdout);
                break;
            
            case 51:
                fprintf(stdout, "So long\n");
                fflush(stdout);
                fclose(stdout);
                return;
            
            default:
                fflush(stdout);
                break;

        }
        bzero(&selection, 1); 
        bzero(writeMessage, SIZE); 
        fseek(stdin,0,SEEK_END);
    }
    fclose(stdout);
    return;
}

int main()
{
    challengeInit();
}
