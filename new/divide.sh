rm -rf number
rm -rf x*
y=$(wc -l $1 | awk '{print $1}')
y=`expr $y / $2`
split -l $y $1
p=`expr $2 - 1`
q=`expr $p + 1`
k=0
	FILE=x$q
for i in $( ls x* )
	do
	mv -f $i "x"$k
((k++))
done
	if [ -f $FILE ];
	then 
	cat $FILE >> x$p
	rm x$q
	fi

for i in $(seq 0 $p)
do
y=$(wc -l x$i | awk '{print $1}')
done
