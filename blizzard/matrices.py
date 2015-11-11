#!/usr/bin/python

import sys

from os import listdir
from os.path import isfile, join
files = [ f for f in listdir(sys.argv[1]) if isfile(join(sys.argv[1],f)) ]

f=open(sys.argv[2],'r')
syllables=[]
for line in f:
	line=line[:-1]
	syllables.append(line)
f.close()

state_trans=[0,0,0,0,0]
trans=[[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0],[0,0,0,0]]
state_em=[0,0,0,0]
em=[]

for i in range(len(syllables)):
	em.append([0,0,0,0])	

for file_name in files:
	print file_name
	f=open(sys.argv[1]+file_name,"r")
	n=0
	prev=-1
	for line in f:
		n=n+1
		if n==1:	
			continue
		line=line[:-1]
		line=line.split(' ')
		print line
		if line[2]!="SIL":
			if "^" in line[2] and "$" not in line[2]:
				syl=line[2].split('^')
				state=1
				op=syllables.index(syl[1])
			elif "$" in line[2] and "^" not in line[2]:
				syl=line[2].split('$')
				state=2
				op=syllables.index(syl[0])
			elif "$" in line[2] and "^" in line[2]:
				syl=line[2].split('^')
				syl=syl[1]
				syl=syl.split('$')
				syl=syl[0]
				state=3
				op=syllables.index(syl)
			else:
				state=0
				op=syllables.index(line[2])
			print prev
			print state
			state_trans[prev+1]+=1
			trans[prev+1][state]+=1
			state_em[state]+=1
			em[op][state]+=1
			prev=state

for i in range(5):
	for j in range(4):
		if state_trans[i]!=0:
			trans[i][j]=float(trans[i][j])/float(state_trans[i])
		print trans[i][j],
	print
for i in range(4):
	for j in range(len(syllables)):
		if state_em[i]!=0:
			em[j][i]=float(em[j][i])/float(state_em[i])
		print em[j][i],
	print

f=open('trans_telugu','w')
for i in range(5):
	temp=""
	for j in range(4):
		temp+=str(trans[i][j])+" "	
	temp+="\n"
	f.write(temp)
f.close()
f=open('em_telugu','w')
for i in range(len(syllables)):
	temp=""
	for j in range(4):
		temp+=str(em[i][j])+" "	
	temp+="\n"
	f.write(temp)
f.close()

