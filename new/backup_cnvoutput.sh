#### first argument is the segmented binwise values with start and stop and the second argument is the ouput file ####
### input is a file containing start stop positions and the binwise corrected values ######
##### bashscript first finds the average and then writes the output to the file  given as the second argument######
avg1=$(awk 'BEGIN{s=0}{s=s+$3}END{print s/NR}' $1)
ll=0.55
uu=1.45
lower_cutoff=$(echo $ll $avg1 | awk '{print $1*$2}' )
upper_cutoff=$(echo $uu $avg1 | awk '{print $1*$2}' )
awk -v lc="$lower_cutoff" -v hc="$upper_cutoff" -v outfile="$2" -v avg="$avg1" 'BEGIN {
	ptr=-1;
	prev=-1;
	flag=-1;
	aavg=0;
        count=0;
	prevEndPoint=-1;
	}
	{
		
		if(ptr==1 && (($3<=lc || $3>=hc) && $1-prevEndPoint<=500))
		{
			aavg=aavg+$3;
			count=count+1;
		}
		else if(ptr==1)
		{
			ptr=-1;
			epoint=prevEndPoint;
			aavg=aavg/count;
			cn=(aavg*2)/avg;
			if(count>1)
				print spoint,epoint,flag,cn>> outfile;
			flag=-1;
			aavg=0;
			count=0;
		}
		if(ptr==-1&& ($3<=lc || $3>=hc) )
		{
			ptr=1;
			spoint=$1;
			
			if($3<=lc)
				flag=0;
			else
				flag=1;
			count = count +1;
			aavg = aavg + $3;
		}
		prevEndPoint = $2;
	}
	
' $1
