// HistogramCounter.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <omp.h>

int Find_bin(float, float [5], const int &bin_count, float &min_meas);

//Use OpenMP to implement the parallel histogram program discussed in Chapter 2 . 
int main()
{
	int thread_count = 4;
	const int data_count = 20;
	float data[data_count] = { 1.3, 2.9, 0.4, 0.3, 1.3, 4.4, 1.7, 0.4, 3.2, 0.3, 4.9, 2.4, 3.1, 4.4, 3.9, 0.4, 4.2, 4.5, 4.9, 0.9 };
	float min_meas = 0;
	float max_meas = 5;
	const int bin_count = 5;

	float bin_maxes[bin_count];
	int bin_counts[bin_count];

	int bin_width = (max_meas - min_meas) / bin_count;

	//initialize values
	for (int b = 0; b < bin_count; b++)
	{
		bin_maxes[b] = min_meas + bin_width * (b + 1);
		bin_counts[b] = 0;
	}

	//get bin counts
#pragma omp parallel for num_threads(thread_count) default(none) shared(data, min_meas, max_meas, data_count)
	for (int i = 0; i < data_count; i++) {
		int bin = Find_bin(data[i], bin_maxes, bin_count, min_meas);
#pragma omp critical
		bin_counts[bin]++;
	}


    return 0;
}

//Finds the bin in which data should be placed
int Find_bin(float data, float bin_maxes[], const int &bin_count, float &min_meas)
{
	for (int i = 0; i < bin_count; i++)
	{
		if (data < bin_maxes[i])
			return i;
	}
	return 0;
};
