#!/usr/bin/python

import sys

from os import listdir
from os.path import isfile, join
files = [ f for f in listdir(sys.argv[1]) if isfile(join(sys.argv[1],f)) ]


for file_name in files:
	f=open(sys.argv[1]+file_name,"r")
	n=0
	output=[]
	do=0
	flag=0
	for line in f:
		n=n+1
		if n==1:
			continue
		print str(do)+" "+str(flag)
		line=line[:-1]
		line=line.split(' ')
		if line[2]=="SIL":
			leng=len(output)
			print output
			print leng
			if leng>0:
				print output[leng-1][2]
			if len(output)>0 and do==1 and output[leng-1][2]!="SIL":
				print "went"
				output[len(output)-1][2]+="$SIL"
			flag=1
		else:
			do=1
			if flag==1:
				line[2]="SIL^"+line[2]
			flag=0
		output.append(line)
	w=open(sys.argv[2]+file_name,"w")
	w.write('#\n')
	for line in output:
		w.write(line[0]+" "+line[1]+" "+line[2]+"\n")
	w.close()
	f.close()

