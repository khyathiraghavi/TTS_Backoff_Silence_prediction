#!/usr/bin/python

import sys
from os import listdir
from os.path import isfile, join

files = [ f for f in listdir(sys.argv[1]) if isfile(join(sys.argv[1],f)) ]

name=sys.argv[1]
if name[len(name)-1]=="/":
	name=name[:-1]
name=name.split("/")
name=name[len(name)-1]

w=open(name,'w')

for file_name in files:
	f=open(sys.argv[1]+file_name,"r")
	flag=1
	for line in f:
		if "*" in line:
			flag=0
			break
	if flag==1:	
		w.write(file_name+"\n")
