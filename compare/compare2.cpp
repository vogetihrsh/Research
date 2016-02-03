// this code compares two files containing cnvs. outputs the common cnvs in both the files. 50% area match is the criteria 
#include<iostream>
#include<vector>
#include<cstdio>
#include<string>
#include<fstream>
#include<algorithm>
using namespace std;
int main(int argc, char *argv[])
{
	if(argc<3)
	{
		cout<<"Fatal Error:Error at least 2 files required for comparison"<<endl;
		exit(0);
	}
	ifstream file1;
	file1.open(argv[1]);
	vector<pair<int,int> > v1;        // vectors containing the cnv corodinates correspondign to the two files
	pair<int,int> temp;
	vector<pair<int,int> > result;
	int l1=0,l2=0;
	int i,j,k,l;
	int st,sp;
	int t1,t2;
	// reading from the first file 
	while(file1>>i)
	{
		temp.first=i;
		file1>>j;
		temp.second=j;
		v1.push_back(temp);
		l1++;
	}
	int a[l1];
	for(i=0;i<l1;i++)
		a[i]=0;
	// loop on remaining files
	for(k=0;k<argc-2;k++)
	{
		ifstream file2;
		file2.open(argv[k+2]);
		l2=0;
		vector<pair<int,int> > v2;
		while(file2>>i)
		{
			temp.first=i;
			file2>>j;
			temp.second=j;
			v2.push_back(temp);
			l2++;
		}
		vector<int> b(l2,0);
		vector<int> c(l1,0);
		/*	for(i=0;i<l1;i++)
			cout<<v1[i].first<<" "<<v1[i].second<<endl;

			for(i=0;i<l2;i++)
			cout<<v2[i].first<<" "<<v2[i].second<<endl;*/
		int count=0;
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
					a[i]=1;
					b[j]=1;
					c[i]=1;

				}

			}
			
		}
		int c1=0,c2=0;
		for(i=0;i<l1;i++)
			c1=c1+c[i];
		for(i=0;i<l2;i++)
			c2=c2+b[i];
		cout<<"# of CNVs of "<<argv[k+2]<<" in "<<argv[1]<<":"<<c2<<"\n# of CNVs of "<<argv[1]<<" in "<<argv[k+2]<<":"<<c1<<endl;
		file2.close();
	}
	int count=0;
	for(i=0;i<l1;i++)
	{
		count=count+a[i];
		if(a[i])
		cout<<i+1<<endl;
	}
	cout<<"Percentage of CNVs in "<<argv[1]<<" present in given files:"<<(1.0*count*100.0/(l1*1.0))<<endl;

	return 0;

}
