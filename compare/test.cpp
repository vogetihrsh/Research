#include<iostream>
#include<fstream>
#include<vector>
using namespace std;
int main()
{
	ifstream file;
	file.open("file2");
	vector<pair<int,int> > v1;
	pair<int,int> p;
	int arr[]={1,2,3,5,6,7,44,46,92,108,111,113,114,116,118,122,124,126,127,129,133,134};
	int i,j,k;
	while(file>>p.first)
	{
		file>>p.second;
		v1.push_back(p);
	}
	for(i=0;i<22;i++)
		cout<<v1[arr[i]-1].first<<" "<<v1[arr[i]-1].second<<endl;

	return 0;
}
