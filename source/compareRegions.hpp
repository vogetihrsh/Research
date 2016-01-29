// COMPARING REGIONS FROM PEM METHOD AND DOC SIGNAL TO DETERMINE TRUE SV REGIONS FROM CANDIDATE SV REGIONS	

#ifndef COMPARE_H
#define COMPARE_H
#include<iostream>
#include<fstream>
#include<algorithm>
#include<vector>
#include<string>
#include<cmath>
#include "structure.hpp"
using namespace std;


vector<CNVRegion> MatchRegions(vector<DisRegion>,string,int);

vector<CNVRegion> MatchRegions(vector<DisRegion> candidateRegion, string RDInputFile,int FLAG){
	// temp variables
	unsigned int i,j,t1,t2;
	double k;
	unsigned int itr;
	unsigned int windowStart;	// siutable window start value in RDInputFile 
	unsigned int windowEnd;		// suitable window end value in RDInputFile
	unsigned int numWin;		// number of windows spanned by the region 
	double avgRD;		// average read depth for the region 
	vector<CNVRegion> cnv;

	fstream fp;
	fp.open(RDInputFile.c_str());

	int vecSize=candidateRegion.size();
	
	if(vecSize==0)
		return cnv;
	for(itr=0;itr<vecSize;itr++)
	{
		
		
		// set start and end values for the region
		t1=candidateRegion[itr].Start;
		t2=candidateRegion[itr].End;
		windowStart= (int)((t1+50)/100)*100;
		windowEnd= (int)((t2-50)/100)*100;
		
		avgRD=0.0;
		numWin=0;

		while(fp>>i>>j>>k&&i<windowStart);	// read until you reach the window 
		if(!fp.eof()&&i>=windowStart&&j<=windowEnd){
			numWin++;
			avgRD+=k;
		}
		else if(fp.eof()) 
			break;
		else 
			continue;

		while(j<windowEnd&&fp>>i){
			fp>>j>>k;
			avgRD+=k;
			numWin++;
		}
		if(numWin==0)
			continue;
		avgRD=(avgRD*1.0)/numWin;
		cerr<<avgRD<<endl;
		switch(FLAG){
			case 1:
				if(avgRD<LOWTHRES)
					cnv.push_back(CNVRegion(t1,t2,avgRD*2/AVG));
				break;
			case 3:
				if(avgRD>UPPTHRES)
					cnv.push_back(CNVRegion(t1,t2,avgRD*2/AVG));
				break;
			default:
				cerr<<"Wrong flag";
				break;

		}
		
	}
	fp.close();
	return cnv;
}
#endif
