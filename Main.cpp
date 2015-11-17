/*
 * Main.c
 *
 *  Created on: 12 Nov 2015
 *      Author: vincent
 */

#include <iostream>
#include "Stats.h"
#include "SignalUtility.h"
#include "Noise.h"

//TODO: Rethink histogram, its kinda fucked...
//TODO: Add signal class - Holds number of samples & the samples?


#define DATA_LENGTH 100000

int main()
{
	float* distribution = NormalDistribution(DATA_LENGTH, 1.5f, 0.25f, 2);

	RunningStats* runningStats = new RunningStats(distribution, DATA_LENGTH);
	Histogram* hist = new Histogram(256, distribution, DATA_LENGTH);

	std::cout << "RSMean: " << Mean(runningStats) << std::endl;
	std::cout << "RSStdDev: " << StandardDeviation(runningStats) << std::endl;

	std::cout << "HMean: " << Mean(hist) << std::endl;
	std::cout << "HStdDev: " << StandardDeviation(hist) << std::endl;

	std::cout << "Mean: " << Mean(distribution, DATA_LENGTH) << std::endl;
	std::cout << "StdDev: " << StandardDeviation(distribution, DATA_LENGTH) << std::endl;

	/*

	float* array = new float[5];

	for(int i = 0; i < 5; ++i)
	{
		array[i] = i;
	}

	RunningStats* runningStats = new RunningStats();
	Histogram* histogram = new Histogram(5, array, 5);

	for(int i = 0; i < 5; ++i)
	{
		runningStats->update(array, 5);
	}



	std::cout << "Mean_R: " << Mean(runningStats) << std::endl;
	std::cout << "StdDev_R: " << StandardDeviation(runningStats) << std::endl;
	std::cout << "SNR_R: " << SignalToNoiseRatio(runningStats) << std::endl;
	std::cout << "CV_R: " << CoefficientOfVariation(runningStats) << std::endl;

	std::cout << "Mean_H: " << Mean(histogram) << std::endl;
	std::cout << "StdDev_H: " << StandardDeviation(histogram) << std::endl;
	std::cout << "SNR_H: " << SignalToNoiseRatio(histogram) << std::endl;
	std::cout << "CV_H: " << CoefficientOfVariation(histogram) << std::endl;

	float mean = Mean(array, 5);
	float stdDev = StandardDeviation(array, 5);

	std::cout << "Mean: " << mean << std::endl;
	std::cout << "StdDev: " << stdDev << std::endl;


	delete[] array;
	delete runningStats;
	delete histogram;
	*/

	return 0;
}
