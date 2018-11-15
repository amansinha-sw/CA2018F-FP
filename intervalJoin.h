#ifndef __INTERVALJOIN_H__
#define __INTERVALJOIN_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

typedef struct{
	char **category;
	int start_idx;
	int end_idx;
}SetA;

typedef struct{
	char **category;
	int start_idx;
	int end_idx;	
}SetB;

int *inStartA, *inEndA;
int *inStartB, *inEndB;

int *outGPU_Begin, *outGPU_End;
int *outCPU_Begin, *outCPU_End;

//Read Metadata for csv files
void read_Meta(){
	
}

//Read setA.csv or setB.csv
void read_csv(char *filename, char *category, bool isSetA){
	
}

//Initialise data for a particular category from both csv files
void init(int length, char *category)
{
	inStartA=new int [length]();
	inEndA=new int [length]();
	inStartB=new int [length]();
	inEndB=new int [length]();
	read_csv("data/setA.csv",category,true);
	read_csv("data/setB.csv",category,false);
	outGPU_Begin=new int [length]();
	outGPU_End=new int [length]();
	outCPU_Begin=new int [length]();
	outCPU_End=new int [length]();
}


void ending()
{
	delete [] inStartA;
	delete [] inStartB;
	delete [] inEndA;
	delete [] inEndB;
	
	delete [] outCPU_Begin;
	delete [] outGPU_Begin;
	delete [] outCPU_End;
	delete [] outGPU_End;	
}

bool checker(int length){
	int i;
	for(i = 0; i < length; i++){ 
		if(outCPU_Begin[i] != outGPU_Begin[i] || outCPU_End[i] != outGPU_End[i]{
			cout << "The element: " << i << " is wrong!\n";
			cout << "outCPU_Begin[" << i << "] = " << outCPU_Begin[i] << endl;
			cout << "outGPU_Begin[" << i << "] = " << outGPU_Begin[i] << endl;
			cout << "outCPU_End[" << i << "] = " << outCPU_End[i] << endl;
			cout << "outGPU_End[" << i << "] = " << outGPU_End[i] << endl;
			return false;
		}
	}

	return true;
}

int timespec_diff_us(timespec& t1, timespec& t2)
{                                                                                
  return (t2.tv_sec - t1.tv_sec) * 1e6 + (t2.tv_nsec - t1.tv_nsec) / 1e3;        
} 

#endif
