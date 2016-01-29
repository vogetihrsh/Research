import sys
import os 
fp = open(sys.argv[1],"r")
description = fp.readline()
r = fp.readlines()
numlines = len(r)
for i in r:
	x= i[:-1]
	sys.stdout.write(x)
