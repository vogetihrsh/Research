#BAM --> BED
for i in `seq 1 1`
do 
rm -rf /home1/ngs/readDepth/reads/* ;
rm -rf /home1/ngs/readDepth/output/*;				    
samtools view -F 4 "/home1/ngs/harsha/BreakPointAnalysisFiles/"$i"_single.bam" | awk 'OFS="\t"{print $3	,$4-1	,$4	}' > chr4.bed
cp chr4.bed /home1/ngs/readDepth/reads/chr4.bed;
Rscript RD.R > log;
mkdir $i"_single_output_def";
mv /home1/ngs/readDepth/output/* $i"_single_output_def";
done 







