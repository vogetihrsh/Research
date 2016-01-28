###### 1st argu,ent is the file name and second is the output name #########
bam=".bam";
int=".intial";
bin=".doc";
zero=".binwiseStartStop";
final=".input";
bincor=".bincor";
a=$1;
b=$2$int;
c=$2$bin;
d=$2$zero;
e=$2$final;
f=$2$bincor;

SOURCEDIR=$(dirname $(readlink -f $0));


#samtools sort $1 $2;
samtools depth  -Q 1 $a > $b;

awk '{print $2,$3}' $b > $c;
rm -rf $b;
awk -f $SOURCEDIR/binwise.awk $c > $d;
awk '{print $3}' $d > $e;
awk '{print $1,$2}' $d > $f;
rm -rf $d; # deleting the three column output 
rm -rf $c; # deleting the doc file
