suffix="_sample.cnv";
suffix2="_sample_cnvtv.cor";
outputprefix="cor/"
for i in `seq 1 180`
do
file=$i$suffix
file2=$outputprefix$i$suffix2
awk '{print $1,$2}' $file > $file2;
done 
