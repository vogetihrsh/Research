#### first argument is the segmented binwise values with start and stop and the second argument is the ouput file ####
### input is a file containing start stop positions and the binwise corrected values ######
##### bashscript first finds the average and then writes the output to the file  given as the second argument######
avg1=$(awk 'BEGIN{s=0}{s=s+$3}END{print s/NR}' $1)
ll=0.55
uu=1.45
lower_cutoff=$(echo $ll $avg1 | awk '{print $1*$2}' )
upper_cutoff=$(echo $uu $avg1 | awk '{print $1*$2}' )
awk -v lc="$lower_cutoff" -v hc="$upper_cutoff" -v outfile="$2" -v avg="$avg1" '


function isCopyNumberZero(cAvg,cCount)
{
          average = cAvg/cCount
	  average = (average*2)/avg;
          return int(average + 0.5)
}



BEGIN {
	entryPointer=-1;
	prev=-1;
	cnvType=-1;
	curAvg=0;
        count=0;
	prevRD=-1;
	diff=0;
	prevEndPoint=-1;
	}
	{
		if(prevRD>$3)
			diff=prevRD-$3;
		else
			diff=$3-prevRD;
		if(entryPointer==1 && (($3<=lc || $3>=hc) && ($1-prevEndPoint<=500|| isCopyNumberZero(curAvg,count)==0))&& (diff<avg/2))
		{
			curAvg=curAvg+$3;
			count=count+1;
		}
		else if(entryPointer==1)
		{
			entryPointer=-1;
			epoint=prevEndPoint;
			curAvg=curAvg/count;
			cn=(curAvg*2)/avg;
			if(count>1)
				print spoint,epoint,cnvType,cn>> outfile;
			cnvType=-1;
			curAvg=0;
			count=0;
		}
		if(entryPointer==-1&& ($3<=lc || $3>=hc) )
		{
			entryPointer=1;
			spoint=$1;
			
			if($3<=lc)
				cnvType=0;
			else
				cnvType=1;
			count = count +1;
			curAvg = curAvg + $3;
		}
		prevEndPoint = $2;
		prevRD=$3;
	}
	
' $1
