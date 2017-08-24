d = open('rfcs/rfc-index.txt').read()

line = ''
started = False
for l in d.split('\n'):
    if not started:
        if '0001' not in l:
            continue
        else:
            started = True
    if len(l) == 0:
        line = line.replace('  ',' ')
        line = line.replace('  ',' ')
        line = line.replace('  ',' ')
        line = line.replace('  ',' ')
        print line
        line = '' 
    line += l

