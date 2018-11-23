#ifndef __INTERVALJOIN_H__
#define __INTERVALJOIN_H__

#include <cstdlib>
#include <iostream>
#include <string>
#include <fstream>
using namespace std;

typedef struct{
  int count;
	int *category;
	int *length;
}SetA;

typedef struct{
  int count;
	int *category;
	int *length;	
}SetB;

SetA setA;
SetB setB;

int *inStartA, *inEndA;
int *inStartB, *inEndB;

int *outGPU_Begin, *outGPU_End;
int *outCPU_Begin, *outCPU_End;

//Read Metadata for csv files
void read_Meta(){
  FILE *mFile;
  int i;
  mFile = fopen ("data/metaA.csv","r");
  fscanf (mFile, "%d", &(setA.count));
  setA.category=new int [setA.count]();
  setA.length=new int [setA.count]();
  for(i=0;i<setA.count;i++)
  	fscanf(mFile,"%d,%d",&(setA.category[i]),&(setA.length[i]));
	fclose(mFile);
  mFile = fopen ("data/metaB.csv","r");
  fscanf (mFile, "%d", &(setB.count));
  setB.category=new int [setB.count]();
  setB.length=new int [setB.count]();
  for(i=0;i<setB.count;i++)
  	fscanf(mFile,"%d,%d",&(setB.category[i]),&(setB.length[i]));
	fclose(mFile);
}

//Read setA.csv or setB.csv
void init_from_csv(FILE *fpA, FILE *fpB, int id){
	int i;
  int temp;
  inStartA=new int [setA.length[id]]();
	inEndA=new int [setA.length[id]]();
	inStartB=new int [setB.length[id]]();
	inEndB=new int [setB.length[id]]();
  for(i=0;i<setA.length[id];i++)
    fscanf(fpA,"%d,%d,%d",&temp,&(inStartA[i]),&(inEndA[i]));
  for(i=0;i<setB.length[id];i++)
    fscanf(fpB,"%d,%d,%d",&temp,&(inStartB[i]),&(inEndB[i]));
	outGPU_Begin=new int [setB.length[id]]();
	outGPU_End=new int [setB.length[id]]();
	outCPU_Begin=new int [setB.length[id]]();
	outCPU_End=new int [setB.length[id]]();
  for(i=0;i<setB.length[id];i++){
        outCPU_Begin[i]=INT_MAX;
        outCPU_End[i]=INT_MIN;
        outGPU_Begin[i]=INT_MAX;
        outGPU_End[i]=INT_MIN;
  }  
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
		if(outCPU_Begin[i] != outGPU_Begin[i] || outCPU_End[i] != outGPU_End[i]){
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
