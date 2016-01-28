// AUTHOR: SRIHARSHA
// post processing step to include regions with low mappability score in the CNVs predicted
// requires two inputs 1) .cnv file and 2) regions with low mapabaility score 
// 6/11/2015


#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
int main(int argc, char** argv)
{
	// cnv file to taken as input from std
	
	vector<vector<double> > cnv;	// for cnv file
	vector<vector<double> > inter;	// intermediate output
	vector<pair<int,int> > lowmap;	// for low mappability bins
	ifstream fp;
	fp.open(argv[1]);	// reading coordinates from low mappablity bins

	int i,j,k,l;
	double f1,f2,f3,f4;
	int l1=0,l2=0;	// l1 is number of cnvs
	int l3 = 0;	// length for intermediate result 
	pair<int,int> temp;
	vector<double> vtemp(4);
	int c1,c2;
	
	// scan all bins from file 
	while(fp>>i)
	{
		fp>>j;
		temp.first=i;
		temp.second=j;
		lowmap.push_back(temp);
		l2++;
	}

	// scan cnv from input stream 
	// input stream is std
	while(cin>>f1)
	{
		cin>>f2>>f3>>f4;
		vtemp[0]=f1;
		vtemp[1]=f2;
		vtemp[2]=f3;
		vtemp[3]=f4;
		cnv.push_back(vtemp);
		l1++;
	}

	int ptr=0; // indicates current position in  the lowmap file 
	for(i=0;i<l1-1;i++)
	{
		
	//	cout<<(int)cnv[i][0]<<" "<<(int)cnv[i][1]<<" "<<cnv[i][2]<<" "<<cnv[i][3]<<endl;
		vtemp[0]=cnv[i][0];
		vtemp[1]=cnv[i][1];
		vtemp[2]=cnv[i][2];
		vtemp[3]=cnv[i][3];
		inter.push_back(vtemp);
		l3++;
		
		// i and i+1 donot have same copy number then continue	
		if(cnv[i][3]!=cnv[i+1][3])
		{
			continue;
		}

		// find bin that is after the cnv 
		while(ptr<l2 && lowmap[ptr].first<cnv[i][1])
			ptr++;
		
		// if reached end of map bin file terminate the loop 
		if(ptr==l2)
			break;
		
		// if the current mbin is not immediately adjacent to cnv then continue
		if(cnv[i][1]!=lowmap[ptr].first)
			continue;
		
		// first that mbin 
	//	cout<<lowmap[ptr].first<<" "<<lowmap[ptr].second<<" "<<cnv[i][2]<<" "<<cnv[i][3]<<endl;
		vtemp[0]=lowmap[ptr].first;
		vtemp[1]=lowmap[ptr].second;
		vtemp[2]=cnv[i][2];
		vtemp[3]=cnv[i][3];
		inter.push_back(vtemp);
		l3++;

		// store coordinates
		c1=lowmap[ptr].first;
		c2=lowmap[ptr].second;
		ptr++;

		// print all adjacent bins
		// exxit if there is no adjacent bin 
		while(ptr<l2 && lowmap[ptr].first==c2){
		//	cout<<lowmap[ptr].first<<" "<<lowmap[ptr].second<<" "<<cnv[i][2]<<" "<<cnv[i][3]<<endl;
			vtemp[0]=lowmap[ptr].first;
			vtemp[1]=lowmap[ptr].second;
			vtemp[2]=cnv[i][2];
			vtemp[3]=cnv[i][3];
			inter.push_back(vtemp);
			l3++;
			c2=lowmap[ptr].second;
			ptr++;
		}
		
		//check boundary and exit for loop
		if(ptr==l2)
			break;

	}
	//print remaining cnvs from the cnv file 
	for(j=i;j<l1;j++)
	{
	//	cout<<(int)cnv[j][0]<<" "<<(int)cnv[j][1]<<" "<<cnv[j][2]<<" "<<cnv[j][3]<<endl;
		vtemp[0]=cnv[i][0];
		vtemp[1]=cnv[i][1];
		vtemp[2]=cnv[i][2];
		vtemp[3]=cnv[i][3];
		inter.push_back(vtemp);
		l3++;
	}
	
	// final merging of the cnvs 
	double prev;
	i=0;
	while(i<l3)
	{
		c1=inter[i][0];
		prev=c2=inter[i][1];
		f3=inter[i][2];
		f4=inter[i][3];
		i++;
		while(i<l3&& f4==inter[i][3]&&prev==inter[i][0])
		{
			prev=inter[i][1];
			i++;
		}
		cout<<c1<<" "<<(int)prev<<" "<<f3<<" "<<f4<<endl;
	}

	return 0;
}
