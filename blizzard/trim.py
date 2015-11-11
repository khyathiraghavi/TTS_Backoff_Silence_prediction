#!/usr/bin/python

import sys

f=open(sys.argv[1],'r')
o=open(sys.argv[2],'w')
for line in f:
	line=line[4:-2]
	line=line.split(' ')
	line = [x for x in line if x != '']
	if line[2]=='+':
		typ="VOW"
	elif line[2]=='-':
		typ="CON"
	else:
		typ="SYM"
	o.write(line[0]+"\t"+typ+"\n")
f.close()
o.close()
	

