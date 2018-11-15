// This program executes a typical Interval Join
#include <iostream>
#include "intervalJoin.h"
using namespace std;

// This is the CPU version, please don't modify it
void intervalJoinCPU()
{
	
}

/***	Implement your CUDA Kernel here	***/
__global__
void intervalJoinGPU()
{
}
/***	Implement your CUDA Kernel here	***/

int main()
{
	int intervalJoinCPUExecTime, intervalJoinGPUExecTime;
	read_Meta();
	init();	
	timespec time_begin, time_end;                                                 
	clock_gettime(CLOCK_REALTIME, &time_begin);
	intervalJoinCPU();
	clock_gettime(CLOCK_REALTIME, &time_end);
	intervalJoinCPUExecTime = timespec_diff_us(time_begin, time_end);
	cout << "CPU time for executing a typical Interval Join = " 
			 <<  intervalJoinCPUExecTime / 1000 << "ms" << endl;

	clock_gettime(CLOCK_REALTIME, &time_begin);
	/***	Lunch your CUDA Kernel here	***/

	intervalJoinGPU<<<1,1>>>(); // Lunch the kernel
	
	cudaDeviceSynchronize(); // Do synchronization before clock_gettime()
	/***	Lunch your CUDA Kernel here	***/
	clock_gettime(CLOCK_REALTIME, &time_end);
	intervalJoinGPUExecTime = timespec_diff_us(time_begin, time_end);
	cout << "GPU time for executing a typical Interval Join = " 
			 << intervalJoinGPUExecTime / 1000 << "ms" << endl;

	if(checker()){
		cout << "Congratulations! You pass the check." << endl;
		cout << "Speedup: " << (float)intervalJoinCPUExecTime / intervalJoinGPUExecTime << endl;
	}
	else
		cout << "Sorry! Your result is wrong." << endl;

	ending();
	
	return 0;
}
