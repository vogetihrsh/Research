function abs(x){return ((x < 0.0) ? -x : x)}
BEGIN{
	min=9999999;
	max =-999999;
	total = 0;
}
{
	r = abs($5);
	if(r<min)
		min=r;
	if(r>max)
		max=r;
	total = total + r;
}
END{
	print NR;
	print "max=",max,"min=",min,"avg=",total/NR;
}
