Rscript RunDNACopy.R na12891_cnvtv_bed.input > temp;
./parseoutput.sh temp > na12891_cbs.cnv;
rm temp;
