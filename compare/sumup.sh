# THIS BASH SCRIPT COMBINES MULTIPLE OUTPUTS FOR A CNV IN THE SIMULATION DATA
# THIS IS REQUIRED FOR THE ANALYSIS OF THE SMULATED DATA WHERE WE NEED TO
# GO THROUGH THE ENTIRE FILES


num_cnv=12 # number of cnvs in the file cahnge this for different number of cnvs
suffix="_sample_rd_def.cor"
SOURCEDIR=$(dirname $(readlink -f $0))

for j in `seq 1  $num_cnv`
do
	count[$j]=0;
done
one=1
fp=0 
for i in `seq 1 30`
do
	cfile=$i$suffix
	$SOURCEDIR/a.out Original.cor $cfile > temp
	k=1
	while read line
	do
		if [ "$k" -gt "$num_cnv" ]
		then
			fp=$(( $fp + $line ));
			break;
		fi
		count[$k]=$(( count[$k] + $line ))
		k=$(( $k + $one))
	done < temp 
done 
echo ${count[@]}
echo $fp


