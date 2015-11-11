#!/usr/bin/python

import sys
import os
from os import listdir
from os.path import isfile, join
directory=sys.argv[1]
syllables_file=sys.argv[2]
phoneset_file=sys.argv[3]

temp=directory.split('/')
if temp[len(temp)-1]=='' :
	temp=temp[:-1]
d=temp[len(temp)-1]
temp=temp[:-1]
if d[len(d)-1]=='/':
	d=d[:-1]
d=d+"_backoff/"
new_dir=""
for t in temp:
	new_dir+=t+"/"
new_dir+=d
print new_dir
if not os.path.exists(new_dir):
	command="mkdir "+new_dir
	os.system(command)
if directory[len(directory)-1]!="/":
	directory+="/"
files = [ f for f in listdir(directory) if isfile(join(directory,f)) ]
for file_name in files:
	path=directory+file_name
	command="./backoff "+path+" "+syllables_file+" "+phoneset_file+" "+new_dir+file_name+" > temp"
	os.system(command)
os.system("rm temp")


