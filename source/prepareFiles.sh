input_file="";		# sorted input bam file
regions_file="";	# file containing non overlappping regions in bed format 

while getopts 'i:r:' flag; do
	case "${flag}" in 
	i) input_file="${OPTARG}" ;;
	r) regions_file="${OPTARG}" ;;
	esac
done	
samtools view -@ 4 -q 1 -bh  $input_file > $input_file"temp1.bam";
bedtools bamtobed -i $input_file"temp1.bam" > $input_file"_reads.bed";
#rm -rf $input_bam"temp1.bam";
bedtools coverage -a $input_file"_reads.bed" -b $regions_file | sort -n -k 2 |awk '{if($4!=0&&$5!=0)print $2,$3,$4}' > $input_file".RD";
