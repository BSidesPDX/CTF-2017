#!/usr/bin/env python

import codecs
import urllib2

s   = open('flag', 'rb')
enc = codecs.getencoder( "rot-13" )
encoded  = enc(s.read())[0]
s.close()

url = 'https://raw.githubusercontent.com/danielmiessler/SecLists/master/Passwords/500-worst-passwords.txt'
response = urllib2.urlopen(url)
text = response.read()
text = text.split('\n')
text[130] = encoded

with open('wallOfText', 'w+') as f:
    f.writelines( list( "%s\n" % item for item in text ) )
    f.close()
