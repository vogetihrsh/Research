for i in `seq 1 10`
do
../a.out ../Original.cor $i"_single.cor" >> file;
awk -f ../properties.awk file;
done
