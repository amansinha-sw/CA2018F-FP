// This program executes a typical Interval Join
#include <iostream>
#include <omp.h>
#include "intervalJoin.h"
using namespace std;

// This is the CPU version, please don't modify it
void intervalJoinCPU(int id)
{
    int i,j;
    #pragma omp parallel for    
    for(i=0;i<setB.length[id];i++){
        for(j=0;j<setA.length[id];j++){
            if((inStartA[j]<=inStartB[i] && inStartB[i]<=inEndA[j]) || (inStartA[j]<=inEndB[i] && inEndB[i]<=inEndA[j]) || (inStartA[j]<=inStartB[i] && inEndB[i]<=inEndB[j]) || (inStartA[j]>=inStartB[i] && inEndB[i]>=inEndA[j])){
                if(outCPU_Begin[i]==INT_MAX)
                    outCPU_Begin[i]=j;
                outCPU_End[i]=j;
            }
        }  
    }
    int total_intersects=0;
    for(i=0;i<setB.length[id];i++){
        if(outCPU_Begin[i]<INT_MAX && outCPU_End[i]>INT_MIN)
            total_intersects+=(outCPU_End[i]-outCPU_Begin[i]+1);
    }
	
	printf("Intersection count=%d\n",total_intersects);	
}

/***	Implement your CUDA Kernel here	***/
__global__
void intervalJoinGPU()
{
}
/***	Implement your CUDA Kernel here	***/

int main()
{
	int i;
	timespec time_begin, time_end;
	int intervalJoinCPUExecTime, intervalJoinGPUExecTime;
	int cpuTotalTime=0,gpuTotalTime=0; 
	FILE *fpA, *fpB;
	read_Meta();
	
	fpA = fopen ("data/dataA.csv","r");
	fpB = fopen ("data/dataB.csv","r");
	
	for(i=0;i<setA.count;i++){
		init_from_csv(fpA, fpB, i);
		
		clock_gettime(CLOCK_REALTIME, &time_begin);
		intervalJoinCPU(i);
		clock_gettime(CLOCK_REALTIME, &time_end);
		intervalJoinCPUExecTime = timespec_diff_us(time_begin, time_end);
		cout << "CPU time for executing a typical Interval Join = " <<  intervalJoinCPUExecTime / 1000 << "ms" << endl;
		cpuTotalTime+=intervalJoinCPUExecTime;
		
		clock_gettime(CLOCK_REALTIME, &time_begin);
		/***Do the required GPU Memory allocation here***/
		
		/***Do the required GPU Memory allocation here***/
		
		/***Configure the CUDA Kernel call here***/
		intervalJoinGPU<<<1,1>>>(); // Lunch the kernel
		
		cudaDeviceSynchronize(); // Do synchronization before clock_gettime()
		
		/***Copy back the result from GPU Memory to CPU memory arrays outGPU_Begin and outGPU_End***/
		
		/***Copy back the result from GPU Memory to CPU memory arrays outGPU_Begin and outGPU_End***/
		
		clock_gettime(CLOCK_REALTIME, &time_end);
		intervalJoinGPUExecTime = timespec_diff_us(time_begin, time_end);
		cout << "GPU time for executing a typical Interval Join = " << intervalJoinGPUExecTime / 1000 << "ms" << endl;
		cpuTotalTime+=intervalJoinGPUExecTime;
		
		/*
		if(checker(setB.length[i])){
			cout << "Congratulations! You pass the check." << endl;
			cout << "Speedup: " << (float)intervalJoinCPUExecTime / intervalJoinGPUExecTime << endl;
		}
		else
			cout << "Sorry! Your result is wrong." << endl;
		*/
		ending();
		
	}
	
	fclose(fpA);
	fclose(fpB);

	return 0;
}
