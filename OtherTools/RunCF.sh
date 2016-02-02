for i in `seq 2 180`
do
mkdir $i"_sorted_100"
sed -i '9 c\outputDir = '$i'_sorted_100' config_3.txt
sed -i '18 c\mateFile =/home1/ngs/harsha/chrom4_simulations/Single_ended_Bamfiles/'$i'_sorted.bam' config_3.txt
./freec -conf config_3.txt
done 
