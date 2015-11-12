/*
 * Main.c
 *
 *  Created on: 12 Nov 2015
 *      Author: vincent
 */

#include <iostream>
#include "Stats.h"
#include "RunningStats.h"

int main()
{
	float* array = new float[5];
	RunningStats<float>* runningStats = new RunningStats<float>();


	for(int i = 0; i < 5; ++i)
	{
		array[i] = i;
	}

	for(int i = 0; i < 5; ++i)
	{
		runningStats->update(array + i, 1);
	}

	std::cout << "Mean: " << runningStats->mean() << std::endl;
	std::cout << "StdDev: " << runningStats->standardDeviation() << std::endl;
	std::cout << "SNR: " << runningStats->signalToNoise() << std::endl;
	std::cout << "CV: " << runningStats->coefficientOfVariation() << std::endl;
	/*
	float mean = Mean(array, 5);
	float stdDev = StandardDeviation(array, 5);

	std::cout << "Mean: " << mean << std::endl;
	std::cout << "StdDev: " << stdDev << std::endl;
	*/

	delete[] array;
	delete runningStats;

	return 0;
}
