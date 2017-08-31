#include <stdio.h>
#include <sys/mman.h>
#include <unistd.h>
#include <string.h>

int main(){
    char *banner="armed...\n";
    char *buffer[1024] = {0x0};
    alarm(5);
    mprotect(buffer, 1024, PROT_READ|PROT_WRITE|PROT_EXEC);
    write(1,banner,strlen(banner));
    read(0,buffer,16);
    //this is correct, and gcc will usually choose r3 for the blx
    //but let's make sure buffer+1 pointer ALWAYS ends up in r3
    //so our solution works in case of recompile, or optimizing:
    //return ((int(*)(void))((unsigned)buffer|1))();
    asm("mov r3, %0\nadd r3,#1\nblx r3"::"r" (buffer):"r3");
    return 0;
}
