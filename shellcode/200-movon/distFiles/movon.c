#include <stdio.h>
#include <unistd.h>
#include <signal.h>
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/mman.h>
#include <string.h>
#include <stdlib.h>

int main() {
    ssize_t len;
    int tfd, infd, started = 0;
    FILE *temp, *objdump;
    char cmdline[256];
    char tempfn[256];
    char *line;
    char *mem,*memptr;
    int pid;
    alarm(5);
    printf("How much to move?\n");
    fflush(stdout);
    scanf("%d",&len);
    if (0 > len || len > 32768){
        printf("No.\n");
        exit(1);
    }
    strcpy(tempfn,"/tmp/movon-XXXXXX");
    tfd = mkstemp(tempfn);
    infd = fileno(stdin);
    mem = mmap((void*)0x41000, getpagesize()*(1+len/getpagesize()), PROT_EXEC|PROT_READ|PROT_WRITE, MAP_ANON|MAP_PRIVATE, 0, 0);
    if (!mem) {
        printf("OOM\n");
        fflush(stdout);
        exit(1);
    }
    printf("%d @ %p\n",len,mem);
    memset(mem,0xc3,getpagesize()*(1+len/getpagesize())); //make it possible to ROP! (but that's the hard way)
    fflush(stdout);
    memptr = mem;
    while (len != 0) {
        int rv;
        rv = read(infd,memptr,len);
        if (rv > 0) {
            memptr += rv;
            len -= rv;
        } else {
            printf("Bad read.\n");
            fflush(stdout);
            exit(1);
        }
    }
    printf("Checking.\n");
    fflush(stdout);
    write(tfd,mem,(int)(memptr-mem));
    sprintf(cmdline,"objdump -b binary -m i386 -D %s",tempfn);
    fflush(stdout);
    objdump = popen(cmdline,"r");
    if (!objdump) {
        printf("Check failed. Unable to execute.\n");
        fflush(stdout);
        exit(1);
    }
    started = 0;
    while (!feof(objdump)){
        len = 0;
        line = NULL;
        if (line) free(line);
        if (-1 == getline(&line,&len,objdump))break;
        if (!started){
            if (strstr(line,"<.data>")) started = 1;
            continue;
        }
        if (strlen(line) < 4 || !strstr(line,"mov    ")){
            printf("%s",line);
            printf("Error ^^^ invalid instruction.\n");
            fflush(stdout);
            exit(1);
        }
    }
    if (line) free(line);
    if (!started) {
        printf("You have to move something!\n");
        exit(1);
    }
    printf("Looks like MOVs to me.\n");
    printf("Returned: %p\n",((void*(*)(void))mem)());
    printf("Bye.\n");
}
