// FILE TO READ INPUT FROM STRUCTURE FILETED ALIGNMENT FILE
// PLEASE MAKE CHANGES TO THIS FILE IF THE INPUT FILE FORMAT CHANGES
// AUTHOR: SRIHARSHA V
/* FILE FORMAT:
 QNAME POSITION POS_OF_MATE FRAGEMENT_LENGTH LENGTH_OF_READ
 */
#ifndef CLASS_NAME_H
#define CLASS_NAME_H

#include "structure.hpp"
#include<fstream>
#include<vector>
#include<string>
#include<algorithm>
#include<iostream>
#include<cmath>

//bool compareFunction1(Read a, Read b);



vector<ReadPair> readFile(string FileName,int flag){
	vector<ReadPair> FVec;
	ReadPair temp;
	ifstream fp;
	int j;
	unsigned long long int l;
	// READ FROM THE FILE 
	fp.open(FileName.c_str());
	if(fp.fail())
	{
		exit(0);
	}
	while(fp>>temp.Id){
		
		fp>>temp.P>>temp.MP>>temp.FL>>temp.L;
		
		// for deletions check if it crosses cutoff
		if(abs(j-MEAN)<=CUTOFF)
			continue;
		// if flag is 3 then check for its cutsoff
		//  j is always negative if flag=3 this is for tandem duplications 
		FVec.push_back(temp);
		
	}
	fp.close();
	
	// END READ FROM THE FILE
	return FVec;
}
#endif


