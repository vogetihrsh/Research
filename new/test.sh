#!/bin/bash

# PARAMETERS REQUIRED 
window_length=100;
no_of_procs=32;
input_file="":
output="aa";
mappability_file="";
window_file="win100.bed";
SOURCEDIR=$(dirname $(readlink -f $0));
# SCANNING FOR PARAMETERS
while getopts 'w:p:i:o:m:z:' flag; do
	case "${flag}" in 
	w) window_length="${OPTARG}" ;;
	p) no_of_procs="${OPTARG}" ;;
	i) input_file="${OPTARG}" ;;
	o) output="${OPTARG}" ;;
	m) mappability_file="${OPTARG}" ;;
	z) window_file="${OPTARG}" ;;
	esac 
done

# ERROR CODE 


# DATA PREPARATION AND FILTERING 
samtools view -@ 4 -q 1 -bh $input_file > $output"_temp1.bam";
/usr/bin/bedtools-2.17.0/bin/bedtools bamtobed -i $output"_temp1.bam" > $output"_reads.bed";
/usr/bin/bedtools-2.17.0/bin/bedtools coverage -a $output"_reads.bed" -b $window_file > $output"_temp1.bed";
rm -rf $output"_reads.bed";

sort -n -k2 $output"_temp1.bed" -o $output"_temp1.bed";
paste $output"_temp1.bed" $mappability_file > $output"_temp2";
mv $output"_temp2" $output"_temp1.bed";
awk '{if($4!=0&&$5!=0&&$8>=0.5)print $4;}' $output"_temp1.bed" > $output"_cnvtv.input";
awk '{if($4!=0&&$5!=0&&$8>=0.5)print $2,$3;}' $output"_temp1.bed" > $output"_cnvtv.bincor"; 
rm -rf $output"_temp1.bed" $output"_temp1.bam";


# DIVIDE INTO CHUNKS 
rm -rf $output"_inp"*
y=$(wc -l $output"_cnvtv.input" | awk '{print $1}')
y=`expr $y / $no_of_procs`;
split -l $y $output"_cnvtv.input" $output"_inp";
p=`expr $no_of_procs - 1`
q=`expr $p + 1`
k=0
FILE=$output"_inp"$q;
for i in $( ls $output"_inp"* )
do
	mv -f $i $output"_inp"$k
((k++))
	done
	if [ -f $FILE ];
	then
		cat $FILE >> $output"_inp"$p
		rm $output"_inp"$q
	fi

# RUN THE SEGMENTATION ALGORITHM  USING MPIRUN
	mpirun -np $no_of_procs $SOURCEDIR/segment $output;
rm -rf $output"_inp"*;
# MERGE THE ABOVE RESULTS
for ((n=0;n<$no_of_procs;n++))
do
        cat $output"_out"$n >> $output"_cnvtv.output"
        rm -rf $output"_out"$n
		done

# CODE TO MAKE CNV CALLS 
		
#rgument is the segmented binwise values with start and stop and the second argument is the ouput file ####
### input is a file containing start stop positions and the binwise corrected values ######
##### bashscript first finds the average and then writes the output to the file  given as the second argument######
paste $output"_cnvtv.bincor" $output"_cnvtv.output" > $output"_cnvtv.call";
avg1=$(awk 'BEGIN{s=0}{s=s+$3}END{print s/NR}' $output"_cnvtv.call");
ll=0.55;
uu=1.45;
bedcnv="_cnvtv.cnv";
lower_cutoff=$(echo $ll $avg1 | awk '{print $1*$2}' )
upper_cutoff=$(echo $uu $avg1 | awk '{print $1*$2}' )
awk -v lc="$lower_cutoff" -v hc="$upper_cutoff" -v outfile="$output$bedcnv" -v avg="$avg1" '




function isCopyNumberZero(cAvg,cCount)
{
	average = cAvg/cCount;
	average = (average*2)/avg;
	return int(average + 0.5);
}

function shouldMerge(prevStart, prevEnd, curStart, curEnd)
{
	Ratio=(curStart-prevEnd-1)/(curEnd-prevStart+1);
	if(Ratio<0.2)
		return 1;
	else 
		return 0;
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
	prevStart=-1;
}

{
	if(prevRD>$3)
		diff=prevRD-$3;
	else
		diff=$3-prevRD;
	if(entryPointer==1 && (($3<=lc||$3>=hc||shouldMerge(prevStart,prevEndPoint,$1,$2)==1)&&(diff<avg/4)))
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
	prevStart=$1;
	prevRD=$3;
}' $output"_cnvtv.call";
rm -rf $output"_cnvtv.call";
 
