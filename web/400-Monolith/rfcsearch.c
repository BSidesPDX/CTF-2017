#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>

char* error404 = "<html><body><center><h1>404 File Not Found</h1></center></body></html>";
char* error431 = "<html><body><center><h1>431 Bad Strategy</h1></center></body></html>";
char* error500 = "<html><body><center><h1>500 Caught You</h1></center></body></html>";
char* cssData = "body { font-family: helvetica; color: #335533;}";
char* mainBody = "<html><head><link rel=\"stylesheet\" type=\"text/css\" href=\"rfc.css\"></head>"
                 "<body><center><h1>RFC Search Tool</h1></body>";
char *respFormat = "HTTP/1.0 200 OK\r\nContent-Type: %s\r\nContent-Length: %d\r\n\r\n%s";

int defang(char *postData){
   char *cp = postData;
   char c;
   while ((c = cp[0]) != 0){
      cp++;
      if ('a' <= c && 'z' >= c) continue;
      if ('A' <= c && 'Z' >= c) continue;
      if ('0' <= c && '9' >= c) continue;
      if (c == ' ' || c == '.' || c == '[' || c == ']' || c == '^' || c == '*') continue;
      cp[-1] = '.';
   }
}

int defangLite(char *json){
   char *cp = json;
   char c;
   while ((c = cp[0]) != 0){
      cp++;
      if (' ' <= c && '~' >= c) continue;
      cp[-1] = '.';
   }
}

void append(char **dest, size_t *len, char *src){
    if (strlen(src)+strlen(*dest) > *len){
        *dest = realloc(*dest,(*len)*2);
        *len *= 2;
    }
    strcat(*dest,src);
}

int processCgi(int sockfd, char *request){
    char *cgi = strstr(request, "GET /cgi-bin/")+13;
    char *cgiEnd = strstr(cgi, "?");
    char *queryStringEnd = strstr(cgi, " ");
    char *body;
    char *queryString = cgiEnd+1;
    char buffer[8192];
    if (cgiEnd == 0 || cgi == 0 || queryStringEnd == 0){
        printf("cgi failed.\n");
        return -1;
    }
    queryStringEnd[0] = 0;
    cgiEnd[0] = 0;
    printf("cgi: \"%s\" defang: \"%s\"\n",cgi,queryString);
    defang(queryString);
    if (strcmp(cgi,"search") == 0){
        FILE *fp;
        char *line = NULL;
        size_t len = 0;
        size_t outlen = 0;
        ssize_t read;
        printf("handling search\n");
        sprintf(buffer,"grep -i \"%s\" index.txt",queryString);
        printf("buffer: %s\n",buffer);
        fp = popen(buffer, "r");
        if (fp == NULL){ 
            printf("popen failed\n");
            return -1;
        }
        outlen = 2048;
        body = malloc(outlen);
        body[0] = 0;
        append(&body,&outlen,"{\"results\":[");
   		while ((read = getline(&line, &len, fp)) != -1) {
        	append(&body,&outlen,"\"");
            defangLite(line);
        	append(&body,&outlen,line);
            append(&body,&outlen,"\",");
            if (strlen(body) > 6969) break;
   		}
        printf("body: %s\n",body);
    	if (ferror(fp)) {
        	return -1;
    	}
    	free(line);
    	fclose(fp);
        append(&body,&outlen,"\"\"]}");
        snprintf(buffer,8192,respFormat,"application/json",strlen(body),body);
        free(body);
    } else if (strcmp(cgi,"retrieve") == 0){
        body = "{'result':'Not Found'}";
        snprintf(buffer,8192,respFormat,"application/json",strlen(body),body);
    } else {
        return -1;
    }
    send(sockfd,buffer,strlen(buffer),0);
    return 0;
}

int handleClient(int sockfd){
    char *body;
    char buffer[2048];
    char *recvPtr = buffer;
    int len;
    buffer[0] = 0;
    alarm(5);
    body = error404;
    while(strstr(buffer,"\r\n\r\n") == 0){
        len = recv(sockfd,recvPtr,2047-strlen(recvPtr),0);
        if (len <= 0){
            body = error431;
            goto processStatic;
        }
        recvPtr += len;
        if ((unsigned long)recvPtr - (unsigned long)buffer > 1024){
            body = error431;
            goto processStatic;
        }
    }
    if (strstr(buffer,"GET / HTTP") != 0){
        body = mainBody;
    }
    if (strstr(buffer,"GET /rfc.css HTTP") != 0){
        body = cssData;
    }
    if (strstr(buffer, "GET /cgi-bin/") != 0){
        if (0 != processCgi(sockfd, buffer)){
            body = error500;
            goto processStatic;
        }
    } else {
processStatic:
        printf("request (%d bytes)\n %s",(int)strlen(buffer),buffer);
        sprintf(buffer,respFormat,"text/html",strlen(body),body);
        send(sockfd,buffer,strlen(buffer),0);
    }
    return 0;
}

int main( int argc, char *argv[] ) {
    int sockfd, newsockfd, portno;
    int rv;
    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;
    if (signal(SIGCHLD, SIG_IGN) == SIG_ERR) {
        exit(1);
    }
    sockfd = socket(AF_INET, SOCK_STREAM, 0);
    if (sockfd < 0) {
        perror("ERROR opening socket");
        exit(1);
    }
    bzero((char *) &serv_addr, sizeof(serv_addr));
    portno = 5001;
    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(portno);
    if (setsockopt(sockfd, SOL_SOCKET, SO_REUSEADDR, &(int){ 1 }, sizeof(int)) < 0)
        perror("setsockopt(SO_REUSEADDR) failed");
    if (bind(sockfd, (struct sockaddr *) &serv_addr, sizeof(serv_addr)) < 0) {
        perror("ERROR on binding");
        exit(1);
    }
    listen(sockfd,100);
    clilen = sizeof(cli_addr);
    while (1) {
        int pid;
        newsockfd = accept(sockfd, (struct sockaddr *)&cli_addr, &clilen);
        if (newsockfd < 0) {
            printf("ERROR on accept errno: %d",errno);
            exit(1);
        }
        pid = fork();
        if (pid == 0) {
            printf("forked.\n");
            close(sockfd);
            rv = handleClient(newsockfd);
            printf("handled. result: %d\n",rv);
            close(newsockfd);
            break;
        } else {
            close(newsockfd);
        }
    }
    return 0;
}
