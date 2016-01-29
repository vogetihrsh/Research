# this python script extracts a part of chromosome ofa given length
import sys
import re
f = open(sys.argv[1],"r")
r =f.readlines()
sequence =""
for line in r:
	sequence= sequence + line[:-1]
seq  = re.sub('N','',sequence)
seq = seq.lower()
print seq[1000:10001000]
