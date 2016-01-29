#This file extracts continous chromosome sequence from fasta file
# Input parameters are length of the sequence to be extracted and the fasta file
# Output File name is sequence.txt
# usage : python extractContinousSequence <fasta file> <length of the sequence?
import sys
import os
import re
fasta = open(sys.argv[1],"r")
outputfile = open("sequence.txt","w")
firstline = fasta.readline()
lines= fasta.readlines()
complete = "".join(lines)
newcomplete = re.sub(r"\n","",complete)
length = len(newcomplete)
count =0
startpoint = 0 
reqlength = int(sys.argv[2])
for i in range(0,length):
	if(newcomplete[i]=='N'):
		startpoint = i
		count =0
	else:
	 	count = count +1
	if(count==reqlength):
		break

x1 = startpoint + 1 + reqlength
if (x1>length):
	x1 = length
print startpoint	
outputfile.write(newcomplete[startpoint+1:x1].lower())	
