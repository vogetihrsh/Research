library("DNAcopy");
args <- commandArgs(trailingOnly = TRUE)
dataPoint <- scan(args[1],what=double());
chrom <- rep(1,1754843);
maploc=1:1754843
obj=CNA(dataPoint,chrom,maploc,data.type="logratio")

segmented_output = segment(obj)
segmented_output
