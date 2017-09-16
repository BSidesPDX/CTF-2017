#!/usr/bin/python3

'''
Make the flag for xordoz. Just easier in python, heh. 
'''

import sys

flagFile = open("flag", "r").readline()

print ("int ords[] = {", end='')

cnt = 0

length = len(flagFile)
for char in flagFile:
    print (ord(char) ^ 0x41, end='') 
    cnt +=1
    if cnt is not length:
        print (",", end='')

print ("};")
