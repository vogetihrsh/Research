/*****
  rELATED TO POST PROCESSIONG IN THE SIMULATED DATA 
  FOR PREPARING THE TABLE 

***/
//THIS IS A NEW COMPARE PROGRAM PRINTS WHETHER ALL THE CNVS IN THE CNV_DETIALS ARE DETECTED OR NOT AND ALSO PRINTS THE NUMBER OF FLASE POSITIVES IN THE
// RESULT FILE OBTAINED USING SIMULATIONS 
// THE FIRST ARGUMENT IS THE CNV_DETAILS FILE
// THE SECOND ARGUMENT IS THE RESULT FILE 


// this code compares two files containing cnvs. outputs the common cnvs in both the files. 50% area match is the criteria 
#include<iostream>
#include<vector>
#include<cstdio>
#include<string>
#include<fstream>
#include<algorithm>
#include<cmath>
using namespace std;
int main(int argc, char *argv[])
{
	ifstream file1;
	ifstream file2;
//	cout<<argv[1]<<" "<<argv[2]<<endl;
	file1.open(argv[1]);
	file2.open(argv[2]);
	vector<pair<int,int> > v1,v2;        // vectors containing the cnv corodinates correspondign to the two files
	pair<int,int> temp;
	vector<pair<int,int> > result;
	int l1=0,l2=0;
	int i,j,k,l;
	int st,sp;
	int t1,t2;
	while(file1>>i)
	{
		temp.first=i;
		file1>>j;
		temp.second=j;
		v1.push_back(temp);
		l1++;
	}

	int found_1[l1]; // WHETHER FOUND OR NOT RELATED TO THE CNV_DETAIL
	vector<pair<int,int> > cor(l1);
	int corflag[l1];
	for(i=0;i<l1;i++){
		found_1[i]=0;
		corflag[i]=0;
	}
	while(file2>>i)
	{
		temp.first=i;
		file2>>j;
		temp.second=j;
		v2.push_back(temp);
		l2++;
	}
	int found_2[l2]; // THIS FOR THE FALSE POSITIVES REPORTED IN THE OUTPUT
	for(i=0;i<l2;i++)
		found_2[i]=0;
//	cout<<l1<<" "<<l2<<endl;
/*	for(i=0;i<l1;i++)
		cout<<v1[i].first<<" "<<v1[i].second<<endl;

	for(i=0;i<l2;i++)
		cout<<v2[i].first<<" "<<v2[i].second<<endl;*/
	vector<int> cnvlength;
	for(i=0;i<l1;i++)
	{
		for(j=0;j<l2;j++)
		{
			st=max(v1[i].first,v2[j].first);	
			sp=min(v1[i].second,v2[j].second);
		//	cout<<st<<" "<<sp<<endl;
			if(st>sp)
				continue;
			l=sp-st+1;
			t1=v1[i].second-v1[i].first+1;
			t2=v2[j].second-v2[j].first+1;
			t1=min(t1,t2);
			if(l>=(t1/2))
			{
				temp.first=i+1;
				temp.second=j+1;
				result.push_back(temp);
				cnvlength.push_back(l);
				found_1[i]=1;
				found_2[j]=1;
				if(corflag[i]==0)
				{
					cor[i].first  = v2[j].first;
					cor[i].second = v2[j].second;
				}
				else
					cor[i].second = v2[j].second;
				corflag[i]++;
			}

		}
	}

/*	cout<<"Common CNVs\n";
	l=result.size();
	cout<<"Number "<<l<<endl;
	for(i=0;i<l;i++)
		cout<<result[i].first<<" "<<result[i].second<<" "<<cnvlength[i]<<endl;*/
//	for(i=0;i<l1;i++)
//		cout<<found_1[i]<<endl;
	int fp=0;
	for(i=0;i<l1;i++){
		if(corflag[i]!=0){
			cout<<cor[i].first<<" "<<cor[i].second<<" "<<v1[i].first<<" "<<v1[i].second<<" ";
			cout<<abs(cor[i].first-v1[i].first)+abs(cor[i].second - v1[i].second)<<endl;
		}
	}

//	cout<<fp<<endl;

	return 0;
}	

