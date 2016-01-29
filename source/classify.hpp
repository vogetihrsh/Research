// CONTAINS FUNCTIONS REQUIRED FOR CLASSIFYING DISCORDANT READS INTO DIFFERENT SVs
// THREE FUNCTIONS FOR THREE INPUT FILES
// 1-del, insertion, 2-inversion, 3-tandem, transv

#ifndef CLASSIFY_H
#define CLASSIFY_H
#include<iostream>
#include<vector>
#include<algorithm>
#include<string>
#include "structure.hpp"
using namespace std;

vector<DisRegion> DeletionInsertion(vector<ReadPair>&);	// FUNCTION FOR CALLING DELETIONS AND INSERTIONS
vector<DisRegion> Inversion(vector<ReadPair>&);		// FUNCTIONS FOR CALLING INVERSIONS
vector<DisRegion> TandemTransversion(vector<ReadPair> &);	// FUNCTIONS FOR CALLING DUPLICATAIONS (TANDEM) AND INTRACHROMOSOMAL INVERSIONS 
extern int MEAN;
extern unsigned int MIN_COUNT,READ_LENGTH;

// FUNCTION DEFINITION-1
vector<DisRegion> DeletionInsertion(vector<ReadPair>& Vi){
	unsigned int size=Vi.size();
	unsigned int i,j;
	unsigned int dsize,isize;
	unsigned int PCount;
	unsigned int start,stop;
	unsigned int wcount=0;	
	int PREV_FL;
	unsigned int sub=(MEAN-2*READ_LENGTH);
	vector<ReadPair> Deletions;	//  vector for deletions 
	vector<ReadPair> Insertions;	// vector for insertion 
	vector<ReadPair> V;		// temporary vector
	vector<DisRegion> Ret_Vec;	// return vector
	
	for(i=0;i<size;i++)
	{
		if(Vi[i].FL-MEAN>0&&Vi[i].FL-MEAN<1000000)
			Deletions.push_back(Vi[i]);
		else
			Insertions.push_back(Vi[i]);
	}
	dsize=Deletions.size();		// no of deletion supporting pairs
	isize=size-dsize;		// no of insertion supporting pairs
	Vi.clear();
	
	size=dsize;
	V=Deletions;

	for(i=0;i<1;i++)
	{
		j=0;
		while(j<size-1){
			wcount=0;
			start=V[j].P+V[j].L;
			stop=V[j].MP;
			PREV_FL=V[j].FL;
			PCount=1;
			j++;
			while(j<size){
				if(V[j].P+V[j].L<stop&&abs(PREV_FL-V[j].FL)<MEAN){
					stop=max(stop,V[j].MP);
					PCount++;
					j++;
					
				}
			
				else {
					wcount++;
					if(wcount<3)
						continue ;
					else if(PCount>=MIN_COUNT){
						Ret_Vec.push_back(DisRegion(start+sub,stop-sub,PCount));
					}
					break;
				}
			}
		}
		if(PCount>=MIN_COUNT)
			Ret_Vec.push_back(DisRegion(start+sub,stop-sub,PCount));
		size=isize;
		V=Insertions;
	}
	return Ret_Vec; 
}


//FUNCTION DEFINITION-2
vector<DisRegion> Inversion(vector<ReadPair>& V){

	unsigned int size=V.size();
	unsigned int j;
	unsigned int PCount=0;	// PAIR COUNT
	unsigned int start,stop;
	unsigned int wcount=0;
	vector<DisRegion> Ret_Vec;
	j=0;

	//start while 
	while(j<size-1){
		start=V[j].P+V[j].L;
		stop=V[j].MP-V[j].L;
		PCount=1;
		j++;
		while(j<size){
			// if 
			if(V[j].P-V[j-1].P<DISTCUTOFF){
				stop=max(stop,V[j].MP-V[j].L);
				PCount+=1;
				j++;
			}
			// end if 
			// else print it to output
			else {
				wcount++;
				if(wcount<=2)
					continue;
				if(PCount>MIN_COUNT){
					Ret_Vec.push_back(DisRegion(start,stop,PCount));
				}
				break;
			}	//end else
		} 	// end while
	} 	// end while
	return Ret_Vec; 
}

//FUNCTION DEFINITION-3
//
vector<DisRegion> TandemTransversion(vector<ReadPair>& V){
	unsigned int size=V.size();
	unsigned int i,j;
	unsigned int tansize=0;
	unsigned int PCount=0;	// PAIR COUNT
	unsigned int start,stop;	// start and stop of the common region 
	unsigned int THRESHOLD=3*SD;	
	unsigned int wcount=0;	
	
	vector<ReadPair> Tandem_Reads;
	vector<DisRegion> Ret_Vec;

	// SEPARATE TANDEM FROM  TRANSVERSIONS
	for(i=0;i<size;i++)
		if(abs(V[i].FL-MEAN)>THRESHOLD&&(V[i].FL-MEAN)<10000)
			Tandem_Reads.push_back(V[i]);
	V.clear();

	// run the classification
	size=Tandem_Reads.size();
	j=0;
	V=Tandem_Reads;
	i=0;
//	for(i=0;i<size;i++)
//		cout<<Tandem_Reads[i].P<<" "<<Tandem_Reads[i].MP<<" "<<Tandem_Reads[i].FL<<endl;
	// while loop
	while(j<size-1){
		
		wcount=0;
		start=V[j].P;
		stop=V[j].MP+V[j].L;
		PCount=1;
		j++;
		while(j<size){		
			if(V[j].P<stop){
				stop=max(stop,V[j].MP+V[j].L);
				PCount++;
				j++;
			}
			else {
				wcount++;
				i++;
				
				if(PCount>=MIN_COUNT){
					Ret_Vec.push_back(DisRegion(start,stop,PCount));
				}
				break;
			}
		}

	}
	if(PCount>=MIN_COUNT)
		Ret_Vec.push_back(DisRegion(start,stop,PCount));
	// end while loop classification 
	return Ret_Vec;
}
#endif
