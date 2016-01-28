OURCEDIR=$(dirname $(readlink -f $0));

bam=".bam";
int=".intial";
bin=".doc";
zero=".binwiseStartStop";
final=".input";
bincor=".bincor";
SOURCEDIR=$(dirname $(readlink -f $0));
a=$2$bam;
b=$2$int;
c=$2$bin;
d=$2$zero;
e=$2$final;
f=$2$bincor;
samtools sort -@ 3 -Q 1 $1 $2;
samtools depth   $a > $b;
rm -rf $a;		# deleting intermediate sorted bam file 
awk '{print $2,$3}' $b > $c;
rm -rf $b;
awk -f $SOURCEDIR/binwise.awk $c > $d;
awk '{print $3}' $d > $e;
awk '{print $1,$2}' $d > $f;
rm -rf $d; # deleting the three column output 
rm -rf $c; # deleting the doc file
