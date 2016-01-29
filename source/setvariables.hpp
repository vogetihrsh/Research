// source code of main() function
// this code deals with syntax err
// YET TO ADD ERROR HANDLING AND HELP

#ifndef SET_H
#define SET_H

#include<getopt.h>
#include<iostream>
#include<string>
#include<algorithm>
#include<cstdlib>
#include<cstdio>
#include "structure.hpp"
using namespace std;

// declaring extern variables here 
double SD;
int MEAN,DISTCUTOFF;
unsigned int CUTOFF,OUTLIER_CUTOFF,READ_LENGTH,MIN_COUNT;
double AVG,LOWTHRES,UPPTHRES;
string INPUT_FILE,OUTPUT_PREFIX;

void printError(int); // function to print errors

void setVariables(int argc, char *argv[])
{
	int  c;
	char command[1024];
	const char *short_opt="c:k:u:i:m:s:r:o:";
	FILE *fp;
	char buff[256];
	bool b1=false,b2=false,b3=false,b4=false,b5=false;
	
	
	struct option  long_opt[] =
	{
		{"cutoff", required_argument,NULL, 'c'},
		{"minReads",required_argument, NULL, 'k'},
		{"outlier", required_argument,NULL,'u'},
		{"input", required_argument,NULL,'i'},
		{"meanFragLen", required_argument,NULL,'m'},
		{"stdDev", required_argument,NULL,'s'},
		{"readLen", required_argument,NULL,'r'},
		{"outputPrefix",required_argument,NULL,'o'},
		{NULL,0,NULL,0}
	};

	while((c = getopt_long(argc, argv, short_opt, long_opt, NULL)) != -1)
	{
		switch(c){
			case -1:	// end of options
			case 0:		
				break;
			case 'c':
				CUTOFF=(float)strtod(optarg,NULL);
				break;
			case 'k':
				MIN_COUNT=(unsigned int)strtod(optarg,NULL);
				break;
			case 'u':
				OUTLIER_CUTOFF=(unsigned int)strtod(optarg,NULL);
				break;
			case 'i':
				INPUT_FILE.append(optarg);b1=true;
				break;	
			case 'm':
				MEAN=(unsigned int)strtod(optarg,NULL);b2=true;
				break;
			case 's':
				SD=(double)strtod(optarg,NULL);b3=true;
				break;
			case 'r':
				READ_LENGTH=(unsigned int)strtod(optarg,NULL);b4=true;
				break;
			case 'o':
				OUTPUT_PREFIX.append(optarg);b5=true;
				break;
			default:
				cout<<"Error"<<endl;
			}
	}

	// check for all compulsory arguments 
	if(!(b1&& b2 && b3 && b4 && b5))
		printError(1);
	snprintf(command,sizeof(command),"./prepareInput.sh %s %s",INPUT_FILE.c_str(),OUTPUT_PREFIX.c_str());
	system(command);
	if(!(fp=popen("awk \'BEGIN{c=0;}{c=c+$3;}END{print c/NR}\' 2_RDINPUT","r"))){
		cerr<<"Error in calculating average read depth"<<endl;
		exit(0);
	}
	fgets(buff,sizeof(buff),fp);
	AVG=(double)strtod(buff,NULL);

	// set parameter values
	MIN_COUNT=5;
	CUTOFF=3*SD;
	cout<<AVG<<endl;
	LOWTHRES=0.55*AVG;
	UPPTHRES=1.45*AVG;
	OUTLIER_CUTOFF=1000000;

	return ;
}

// error printing function 
// all error messages should be printing using this function 
void printError(int flag){
	int n;
	switch(flag){
		case 1:
			cerr<<"Compulsory Arguments Missing\n-m -s -r -i -o are mandatory"<<endl;
			break;
		default:
			cerr<<"General Error"<<endl;
	}
	exit(0);
}
#endif
