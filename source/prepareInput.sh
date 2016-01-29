samtools view -f 33 -F 3870 -q 1 $1 | awk '{if($4<$8&&$9>0) print $1,$4,$8,$9,length($10)}' > $2"_Deletion.reads"
samtools view -f 17 -F 3884 -q 1 $1 | awk '{if($4<$8&&$9>0) print $1,$4,$8,$9,length($10)}' > $2"_Tandem.reads"

