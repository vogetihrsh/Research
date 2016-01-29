#include<iostream>
#include<vector>
#include<string>
#include<algorithm>
#include<cstdio>
#include<cmath>
#include<fstream>
#include "structure.hpp"
#include "readFile.hpp"
#include "classify.hpp"
#include "compareRegions.hpp"
#include "setvariables.hpp"


using namespace std;


// comparison function for sorting the array 
bool myfunc(ReadPair a, ReadPair b)
{
	return ((a.P<b.P || (a.P==b.P&&a.MP<b.MP)));
}
bool myfunc2(CNVRegion a, CNVRegion b)
{
	return (a.Start<b.Start||(a.Start==b.Start&&a.End<b.End));
}

int main(int argc, char *argv[])
{
	vector<ReadPair> ret;		// vector after reading the file 
	vector<DisRegion> Deletion_Candidates,Tandem_Candidates;	// vector containing candidate SV regions 
	vector<CNVRegion> cnv,temp;
	int i,numCNVs;
	setVariables(argc,argv);
	cerr<<LOWTHRES<<" "<<UPPTHRES<<endl;
	string del_file=OUTPUT_PREFIX+"_Deletion.reads";	// filename for deletion candidate reads
	string tan_file=OUTPUT_PREFIX+"_Tandem.reads";	// filename for tandem duplications candidate reads
	string output_file=OUTPUT_PREFIX+".cnv";
	string rd_file = INPUT_FILE+".RD";
	
	// parse options and set values for the paramters required 

	// DETECT DELETIONS
	ret=readFile(del_file.c_str(),1);
	sort(ret.begin(),ret.end(),myfunc);
	Deletion_Candidates=DeletionInsertion(ret);
	ret.clear();
	cnv=MatchRegions(Deletion_Candidates,rd_file,1);

	// DETECT TANDEM DUPLICATIONS
	ret=readFile(tan_file.c_str(),3);
	sort(ret.begin(),ret.end(),myfunc);
	Tandem_Candidates=TandemTransversion(ret);
	ret.clear();
	temp=MatchRegions(Tandem_Candidates,rd_file,3);
	cnv.insert(cnv.end(),temp.begin(),temp.end());
	
	// SORT THE PREDICTED CNVS BY COORDINATES
	sort(cnv.begin(),cnv.end(),myfunc2);

	// PRINT TO OUTPUTFILE
	ofstream Out;
	Out.open(output_file.c_str());
	numCNVs=cnv.size();
	cerr<<"Size:"<<numCNVs<<endl;
	for(i=0;i<numCNVs;i++)
		Out<<cnv[i].Start<<"	"<<cnv[i].End<<"	"<<cnv[i].CopyNumber<<endl;
	Out.close();

	return 0;
}

