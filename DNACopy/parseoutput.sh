#!/bin/bash
average=$(awk 'BEGIN{count=0;}{if(NR>5)count=count + $7;}END{print count/(NR-5)}' $1)
awk -v average="$average" '
BEGIN{
	i=0;
}
{
	if(NR>5 && ($7>1.45*average||$7<0.55*average)){
		array[i] = $4;
		i=i+1;
		array[i]=$5;
		i=i+1;
		array[i]=($7*2/average);
		i=i+1;
	}
}
END{
	j=0;
	for(j=0;j<i;j=j+3)
	{
		print array[j]
			print array[j+1]
			print array[j+2]

	}
}
' $1 > $1"_temp"
k=0
while read line 
do
rem=$((k%3))
if [ $rem -eq 0 ]
then		
	linep=$line"p"
	sp=$(sed -n $line,$linep na12891_cnvtv_bed.bincor | awk '{print $1}')
elif [ $rem -eq 1 ]
then 	
	linep=$line"p"
	ep=$(sed -n $line,$linep na12891_cnvtv_bed.bincor | awk '{print $2}')
else 
	echo $sp $ep $line
fi
k=$((k + 1 ))
done < $1"_temp";
rm -rf $1"_temp"
