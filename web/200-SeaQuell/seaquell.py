#!/usr/bin/python
import SimpleHTTPServer
import sqlite3

addr = ('localhost',8000)

class ReqHandler(SimpleHTTPServer.SimpleHTTPRequestHandler):
    def do_HEAD(self):
        self.send_response(500)

    def do_GET(self):
        print self.path
        if ('..' in self.path or 
           not (self.path.endswith('.html') or
                self.path.endswith('/') or
                self.path.endswith('.jpg'))):
           self.send_response(403)
           self.end_headers()
           self.wfile.write('<h1>403</h1>Not Authorized')
           return
        if self.path.startswith('/employees-only'):
           try:
               (user,passwd) = self.headers['authorization'].split()[1].decode('base64').split(':')
               print (user,passwd)
               con = sqlite3.connect('seaquell.db')
               cur = con.cursor()
               cur.execute('SELECT password FROM employees WHERE username == "'+user+'"')
               r = cur.fetchall()
               if (len(r) != 1): #if we don't get a password back, then this is an invalid user
                   raise Exception('Invalid user: \"%s\" (got %s)' % (user,r))
               if r[0][0] != passwd:
                   raise Exception('Access denied. Wrong password.')
           except Exception as e:
               self.send_response(401)
               self.send_header('WWW-Authenticate','Basic realm="Employee Area"')
               self.send_header('X-Error',e)
               self.end_headers()
               self.wfile.write('<h1>401</h1>Access Denied')
               return
        return SimpleHTTPServer.SimpleHTTPRequestHandler.do_GET(self)

s = SimpleHTTPServer.BaseHTTPServer.HTTPServer(addr,ReqHandler)
s.serve_forever()
