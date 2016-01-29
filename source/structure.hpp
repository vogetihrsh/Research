// HEADER FILES CONTANING STRUCTURES AND GLOBAL VARIABLES
// AUTHOR: SRIHARSHA V

#ifndef MYSTRUCT_H
#define MYSTRUCT_H

#include<string>
using namespace std;
// strucuture for mate-pair
/*struct MatePair{
	string Id;	// Qname
	unsigned int P1, P2;	// Mate Pair Starting positions 
	int L1,L2,FL;	// Length of reads and Length of the fragment
};*/

// structure for read Information

struct ReadPair{
	string Id;		// QNAME
	unsigned int P,MP;	// Read Position and corresponding mate pair position 
	int L, FL;		// Read Length and the fragement length
};

// sturcture for discordant region 
struct DisRegion{
	unsigned int Start;	// starting position of the region
	unsigned int End;	// Ending poistion of the region
	unsigned int NR;	// Number of reads supporting the structural variant
	
	// constructor function for the structure. note that all variables are public
	DisRegion(unsigned int a, unsigned int b, unsigned c){
		Start=a;
		End=b;
		NR=c;
	}
};

struct CNVRegion{
	unsigned int Start;
	unsigned int End;
	double CopyNumber;
	CNVRegion(unsigned int a, unsigned int b , double c){
		Start=a;
		End=b;
		CopyNumber=c;
	}
};

// GLOBAL VARIABLES REQUIRED BY ALL OTHER FILES
// THESE VARIABLES ARE SET IN MAIN.CPP
extern double SD;		// standard deviation 
extern int MEAN;		// mean of fragment length 
extern unsigned int OUTLIER_CUTOFF;	// cutoffs value for outlier
extern unsigned int CUTOFF;	// cutoff to decide on concordance 
extern int DISTCUTOFF;		// distance between the pairs so that they can be mergerd
extern unsigned int MIN_COUNT;	// minimum cluster size
extern double AVG;			// average readdepth of the singal
extern double LOWTHRES,UPPTHRES;	// lower and upper thresholds this should be taken from thresholds used in RDapproach
extern unsigned int READ_LENGTH;	// average read length 
extern string INPUT_FILE;
extern string OUTPUT_PREFIX;	// output prefix
#endif

