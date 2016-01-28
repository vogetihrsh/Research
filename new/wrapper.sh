# SHOULD BE EXECUTED AFTER THE SORTING AND EXTRACTING THE DOC FOR THE BAM FILE
# 1 = input file 
# 2 = number of processes
# 3 = output file
SOURCEDIR=$(dirname $(readlink -f $0));
$SOURCEDIR/divide.sh $1 $2;
mpirun -np $2 $SOURCEDIR/a.out;
$SOURCEDIR/merge.sh $2 $3;
rm -rf x*;
