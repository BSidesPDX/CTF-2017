#include<stdio.h>
#include<unistd.h>
#include<string.h>
#include<sys/mman.h>

char *intro = "This is (r-x) at %p:\n"
"  pop r8\n"
"  pop r9\n"
"  ret\n"
"  pop r10\n"
"  ret\n"
"  xchg rdi,r8\n"
"  ret\n"
"  xchg rsi,r8\n"
"  ret\n"
"  xor rax,rax\n"
"  ret\n"
"  add rax,0xf05050f\n"
"  xor rax,r8\n"
"  ret\n"
"  mov rdx,r8\n"
"  ret\n"
"  call rdi\n"
"The rest is up to you...\n";

char *shellcode = "\x41\x58\x41\x59\xc3\x41\x5a\xc3\x49\x87\xf8\xc3"
"\x49\x87\xf0\xc3\x48\x31\xc0\xc3\x48\x05\x0f\x05\x05\x0f\x4c\x31"
"\xc0\xc3\x4c\x89\xc2\xc3\xff\xd7";

int main() {
    void *ropdata = mmap(0,0x1000,PROT_READ|PROT_WRITE,MAP_PRIVATE|MAP_ANONYMOUS,-1,0);
    int r = 0;
    char stack[0];
    char *wptr = stack;
    if (!ropdata){
        printf("Alloc failed.\n");
        fflush(stdout);
    }
    memset(ropdata,0xc3,0x1000);
    memcpy(ropdata,shellcode,strlen(shellcode));
    mprotect(ropdata,0x1000,PROT_READ|PROT_EXEC);
    printf(intro,ropdata);
    fflush(stdout);
    do {
        wptr += r;
        r = read(0,wptr,1024);
    }while(r > 0);
    return 0;
}
