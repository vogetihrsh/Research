##### raw format to fasta format ######
import sys
s=raw_input()
l=len(s)
print ">chr4"
for i in range(0,l):
	sys.stdout.write(s[i])
	
	if((i+1)%70==0):
		 sys.stdout.write("\n")
