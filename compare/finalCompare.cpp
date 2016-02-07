// COMPARISON OF PREDECTED CNVS AND ORIGINAL CNVS
//  CAN BE USED FOR REAL DATA AS WELL AS SIMULATED DATA AND FOR ALL TOOLS
//  DATA: 03/02/2016
//  AUTHOR: SRIHARSHA V
// CRITERIA FOR TRUE POSITIVE IS RECIPROCAL SIMILARITY OF 50% BETWEEN THE PREDICTED AND ORIGINAL CNV

#include<iostream>
#include<vector>
#include<algorithm>
#include<fstream>
using namespace std;
int main(int argc, char* argv[])
{
	ifstream file1;	// ORIGINAL COORDINATES
	ifstream file2;	// TOOL PREDICTED COORDINATES
	vector<pair<int,int> > v1,v2;
	
	pair<int,int> temp;
	int n1=0,n2=0;
	int i,j,k,l;
	// TEMP COORDINATES 
	int d1,d2;	// FOR ORIGINAL	
	int c1,c2;	// FOR TOOL
	int o1,o2;	// FOR OVERLAP BETWEEN TWO
	
	//OPEN AND READ FILES
	file1.open(argv[1]);
	file2.open(argv[2]);
	while(file1>>i){
		
		file1>>j;
		temp.first = i;
		temp.second = j;
		v1.push_back(temp);
		n1++;
	}
	while(file2>>i){
		
		file2>>j;
		temp.first = i;
		temp.second = j;
		v2.push_back(temp);
		n2++;
	}
	
	//INITIALIZATIONS
	vector<int> rlen(n1),cnvpointer(n2),originalPointer(n1);
	for(j=0;j<n2;j++)
		cnvpointer[j]=0;
	for(i=0;i<n1;i++){
		rlen[i] = v1[i].second - v1[i].first +1;
		originalPointer[i]=0;
	}

	// MAIN LOOP
	j=0;
	for(i=0;i<n1;i++)
	{
		for(j=0;j<n2;j++)
		{
			d1 = v1[i].first;d2=v1[i].second;
			c1 = v2[j].first; c2 = v2[j].second;
			
			if(d2<c1 || d1>c2)
				continue;
			o1=max(d1,c1);
			o2=min(c2,d2);
			l = o2-o1;
			if(l>=(c2-c1)/2){
				cnvpointer[j]=1;
			}
			rlen[i]-=l;
		}
	}

	//FINDING NUMBER OF FALSE POSITIVES AND PRINTING CODE
	int falsePositives=0;
	for(i=0;i<n1;i++){
		if(rlen[i]<(v1[i].second-v1[i].first+1)/2)
			originalPointer[i]=1;
		cout<<originalPointer[i]<<endl;
		}
	for(i=0;i<n2;i++){
		if(cnvpointer[i]==0)
			falsePositives+=1;
	}
	cout<<falsePositives<<endl;
	
	return 0;
}
