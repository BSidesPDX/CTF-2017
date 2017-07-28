#define _GNU_SOURCE  
#include <stdio.h>
#include <stdlib.h>
#include <netdb.h>
#include <netinet/in.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/sendfile.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

char* error404 = "<html><body><center><h1>404 File Not Found</h1></center></body></html>";
char* error431 = "<html><body><center><h1>431 Bad Strategy</h1></center></body></html>";
char* error500 = "<html><body><center><h1>500 Caught You</h1></center></body></html>";
char* cssData = "body { font-family: helvetica; color: #335533;}\n"
                ".search {border: 2px solid #335533; border-radius: 5px; padding: 10px}";
char* mainBody = "<html><head><link rel=\"stylesheet\" type=\"text/css\" href=\"rfc.css\">"
"<script src=\"https://ajax.googleapis.com/ajax/libs/jquery/3.2.1/jquery.min.js\"></script>"
                 "<script>function onSearch(){"
                 "$.getJSON(\"/cgi-bin/search?term=\"+$(\"#term\").val(),function(data){"
                 "r = data.results;"
                 "out = \"Search Results: \"+(r.length-1)+\" records.<BR><BR><TABLE>\";"
                 "for (var i=0; i < r.length; i++){ "
                 "rfc = Math.round(r[i].split(' ')[0]);"
                 "if (rfc == 0) { continue; }"
                 "out += \"<tr><td valign=top><button onClick='onDL(\\\"rfc\"+rfc+\"\\\")'>View</button>"
                 "</td><td style='max-width:300px'>\"+r[i]+\"</td></tr>\"; }"
                 "out += \"</TABLE>\";"
                 "$(\"#results\").html(out);"
                 "});}\n"
                 "function onDL(rfc){"
                 "$.get(\"/cgi-bin/retrieve?rfc=\"+rfc+\"&type=txt\",function(data){"
                 "$(\"#results\").html(\"<pre>\"+data+\"</pre>\");"
                 "});}</script></head>"
                 "<body><center><h1>RFC Search Tool</h1>"
                 "<table width=0><tr><td>"
                 "<div class=\"search\">Search: <input id=\"term\" type='text' />"
                 "<button onClick=\"onSearch()\">Go!</button></div>"
                 "<br><br>"
                 "<div class=\"search\" id=\"results\">No results.</div>"
                 "</td></tr></table></form></center></body></html>";
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
    char *queryStringEnd;
    char *body;
    char *queryString = cgiEnd+1;
    char buffer[8192];
    if (cgiEnd == 0 || cgi == 0){
        printf("cgi failed.\n");
        return -1;
    }
    queryStringEnd = strstr(cgi, " ");
    if (queryStringEnd){
        queryStringEnd[0] = 0;
    }
    cgiEnd[0] = 0;
    printf("cgi: \"%s\" query: \"%s\"\n",cgi,queryString);
    if (strcmp(cgi,"search") == 0){
        FILE *fp;
        char *line = NULL;
        size_t len = 0;
        size_t outlen = 0;
        ssize_t read;
        queryString = strstr(queryString,"term=")+5;
        defang(queryString);
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
    	if (ferror(fp)) {
        	return -1;
    	}
    	free(line);
    	fclose(fp);
        append(&body,&outlen,"\"\"]}");
        snprintf(buffer,8192,respFormat,"application/json",strlen(body),body);
        free(body);
        send(sockfd,buffer,strlen(buffer),0);
    } else if (strcmp(cgi,"retrieve") == 0){
        char *queryArg;
        char *rfcFilePtr;
        struct {
            char rfcFile[256];
            int ret;
            struct stat s;
            int file;
        } fdat;
        memset(fdat.rfcFile,0,256);
        queryArg = strstr(queryString,"rfc=")+4;
        strcpy((fdat.rfcFile),"rfc/");
        rfcFilePtr = (fdat.rfcFile)+4;
        for (int i=0; i < 256 && queryArg[i] != '&'; i++){
            *rfcFilePtr = queryArg[i];
            rfcFilePtr++;
        }
        strcat(rfcFilePtr,".txt");
        memset(&(fdat.s),0,sizeof(struct stat));
        fdat.ret = 0;
        fdat.ret = stat(fdat.rfcFile,&(fdat.s));
        snprintf(buffer,8192,respFormat,"text/plain",fdat.s.st_size,"");
        fdat.file = open(fdat.rfcFile,O_RDONLY);
        printf("fid: %d, file: %s, ret: %d, size: %d\n",fdat.file,fdat.rfcFile,fdat.ret,(int)fdat.s.st_size);
        send(sockfd,buffer,strlen(buffer),0);
        sendfile(sockfd,fdat.file,NULL,fdat.s.st_size);
        close(fdat.file);
    } else {
        return -1;
    }
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
    memset(buffer,0,2048);
    while(memmem(buffer,2048,"\r\n\r\n",4) == 0){
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
