# it is a diploid genome, the first argument is the file containing cnv info, the length and the copy number, the second argument is the haploid ref genome, output is a raw file 
# I think thats it 
import random
import sys
f=open(sys.argv[1],'r')
g=open(sys.argv[2],'r')
output=open("Sample.seq",'w')	# will contain the output sequence
output1=open("CNV_Details",'w')				# will contain the introduced cnv details
s=g.read()
glen=len(s)	
lines=f.readlines()
cnum=[]	# contains copy number info
clen=[]	# contains cnv length info 
for line in lines:
	lis=line.split(' ')
	clen.append(int(lis[0]))
	cnum.append(int(lis[1]))
#print clen
#print cnum
ncnv=len(clen)    # number of cnvs
segmentlen=int(glen/ncnv)
print segmentlen	
segstp=[]	
for i in range(0,ncnv):
	segstp.append(i*segmentlen)        # this is the array containing the cuts in the haploid to divide it in equal parts
print segstp
left=[]	#left part of the haploid	
right=[] # right part of the haploid	
for i in range(0,ncnv-1):
	left.append(s[segstp[i]:segstp[i+1]])
	right.append(s[segstp[i]:segstp[i+1]])
right.append(s[segstp[ncnv-1]:])	
left.append(s[segstp[ncnv-1]:])	
#print len(right),len(left)
y=""	
for i in range(0,ncnv):
	
	x=random.randint(0,segmentlen-clen[i]-2)		# start point of the cnv in the genome, 
	if(cnum[i]==1):
		left[i]=left[i][:x]+left[i][x+clen[i]:]	
	elif(cnum[i]==0):
		left[i]=left[i][:x]+left[i][x+clen[i]:]	
		right[i]=right[i][:x]+right[i][x+clen[i]:]	
	else:
	 	left[i]=left[i][:x]+(cnum[i]-2)*left[i][x:x+clen[i]]+left[i][x:]
	y=y+str(x+segstp[i]) + " " + str(clen[i]) + " " + str(cnum[i])+"\n"
g1=""	# final output string
for i in range(0,ncnv):
	g1=g1+left[i]
	
for i in range(0,ncnv):
	g1=g1+right[i]
output.write(g1)	
output1.write(y) 
output.close()
output1.close()	
f.close()
g.close()
