#include<set>
#include<cstdlib>
#include<iostream>
#include<vector>
using namespace std;
int main()
{
	int i;
	set<int> s;
	cin>>i;
	while(i!=-1)
	{
		s.insert(i);
		cin>>i;
	}
	cout<<s.size();
	return 0;
}
