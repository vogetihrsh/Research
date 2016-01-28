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
while getopts 'w:p:i:o:m:' flag; do
	case "${flag}" in 
	w) window_length="${OPTARG}" ;;
	p) no_of_procs="${OPTARG}" ;;
	i) input_file="${OPTARG}" ;;
	o) output="${OPTARG}" ;;
	m) mappability_file="${OPTARG}" ;;
	W) window_file="${OPTARG}" ;;
	esac 
done

# ERROR CODE 


# DATA PREPARATION AND FILTERING 
samtools view -@ 4 -q 1 -bh $input_file > temp1.bam;
/usr/bin/bedtools-2.17.0/bin/bedtools bamtobed -i temp1.bam > $output"_reads.bed";
rm -rf temp1.bam;
/usr/bin/bedtools-2.17.0/bin/bedtools coverage -a $output"_reads.bed" -b $window_file > temp1.bed;
rm -rf $output"_reads.bed";
sort -n -k2 temp1.bed -o temp1.bed;
paste temp1.bed $mappability_file > temp2;
mv temp2 temp1.bed;
awk '{if($4!=0&&$5!=0&&$8>=0.5)print $4;}' temp1.bed > $output"_bed.input";
awk '{if($4!=0&&$5!=0&&$8>=0.5)print $2,$3;}' temp1.bed > $output"_bed.bincor"; 
rm -rf temp1.bed;


# DIVIDE INTO CHUNKS 
rm -rf $output"_inp"*
y=$(wc -l $output"_bed.input" | awk '{print $1}')
y=`expr $y / $no_of_procs`;
split -l $y $output"_bed.input" $output"_inp";
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
        cat $output"_out"$n >> $output"_bed.output"
        rm -rf $output"_out"$n
		done

# CODE TO MAKE CNV CALLS 
		
#rgument is the segmented binwise values with start and stop and the second argument is the ouput file ####
### input is a file containing start stop positions and the binwise corrected values ######
##### bashscript first finds the average and then writes the output to the file  given as the second argument######
paste $output"_bed.bincor" $output"_bed.output" > $output"_bed.call";
echo "Here"
avg1=$(awk 'BEGIN{s=0}{s=s+$3}END{print s/NR}' $output"_bed.call");
ll=0.55;
uu=1.45;
bedcnv="_bed.cnv";
lower_cutoff=$(echo $ll $avg1 | awk '{print $1*$2}' )
upper_cutoff=$(echo $uu $avg1 | awk '{print $1*$2}' )
echo $lower_cutoff $upper_cutoff;
awk -v lc="$lower_cutoff" -v hc="$upper_cutoff" -v outfile="$output$bedcnv" -v avg="$avg1" 'BEGIN {
			ptr=-1;
			prev=-1;
			flag=-1;
			aavg=0;
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
	if(ptr==1 && (($3<=lc || $3>=hc) && $1-prevEndPoint<=500)&& (diff<avg/2))
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
	prevRD=$3;
}

' $output"_bed.call";
rm -rf $output"_bed.call";
 
