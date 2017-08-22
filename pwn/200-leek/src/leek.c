#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>

const unsigned int PORT = 2007;
int SIZE = 1000;

void copyAndWriteMessage(char *writeMessage, FILE *fp)
{
    char temp[100];
    strcpy(temp, writeMessage);
}


void challengeInit(int sfd) 
{

    char selection = '0';
    char name[100];
    char writeMessage[SIZE];
    char *prompt =  "\
                    Would you like to play a game? \n\
                    Please select an option followed by your message: \n\
                    1 - Name game \n\
                    2 - Write message \n\
                    3 - exit \n";
    
    char *message = "Enter an option \n";
   
    int fd = dup(sfd);
    FILE *fp = fdopen(fd, "w+");

    fprintf(fp, "%s", prompt);
    fflush(fp);
    
    for (;;)
    {
        fprintf(fp,"%s", message);
        fflush(fp);
        recv(sfd, &selection, 1, 0);
        
        switch (selection) 
        {
            case 49:
                fprintf(fp, "Enter your name \n");
                fflush(fp);
                recv(sfd, name, 100, 0); 
                fprintf(fp, name);
                fflush(fp);
                break;

            case 50:
                fprintf(fp, "Not implemented\n");
                recv(sfd, writeMessage, 1000, 0);
                copyAndWriteMessage(writeMessage, fp);
                fflush(fp);
                break;
            case 51:
                fprintf(fp, "So long\n");
                fflush(fp);
                fclose(fp);
                return;

            default:
                fprintf(fp, "Invalid choice!\n");
                fflush(fp);
                break;

        }
        bzero(&selection, 1); 
        bzero(name, 100);
        bzero(writeMessage, SIZE); 
    }
    fclose(fp);
    return;
}

int init_server(const unsigned int port)
{

    int fd;
    int reuse = 1;
    struct sockaddr_in sin;

    sin.sin_family = AF_INET;
    sin.sin_port = htons(port);
    sin.sin_addr.s_addr = INADDR_ANY;

    fd = socket(AF_INET, SOCK_STREAM, 0);
    if (fd == -1)
    {  
        perror("Could not create a socket");
        exit(1);
    }  

    if(setsockopt(fd, SOL_SOCKET, SO_REUSEADDR, &reuse, sizeof(reuse)))
    {
        perror("Could not set socket options");
        exit(1);
    }

    if(bind(fd, (struct sockaddr*)&sin, sizeof(sin)))
    {
        perror("Could not bind to port");
        exit(1);
    }

    if(listen(fd, 20))
    {  
        perror("Could not listen on socket");
        exit(1);
    }

    return fd; 
}


void serve_server(int fd, void (*challenge)(int))
{
    int accepted_fd;
    int child_pid;
    struct sockaddr_in socket;
    uint32_t sockaddr_len = sizeof(socket);

    for(;;)
    {
        accepted_fd = accept(fd, (struct sockaddr *)&socket, &sockaddr_len);
        if (accepted_fd != -1)
        {
            child_pid = fork();
            if(child_pid)
            {
                close(accepted_fd);
            }
            else
            {
                challenge(accepted_fd);
                close(accepted_fd);
                exit(0);
            }
        }  
    }
}


int main()
{
    int fd;
    fd = init_server(PORT);
    serve_server(fd, challengeInit);
}
