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
#include "UnitTests.h"
#include "Filters.h"

//TODO: Rethink histogram, its kinda fucked...
//TODO: Add the ability to 'Unwrap the phase' (Chapter 8)
//TODO: Think about frequency domain convolution and the best way to go about it... (Chapter 9)
//TODO: Think about breaking apart the two different types of representations of Frequency Signals
//TODO: Implement the complex conjugate (Characteristics of the phase, Chapter 10)

#define DATA_LENGTH 100000

int main()
{

	Signal* testSignal = GenerateBlackmanWindowedSincLowPassFilter(500, 0.015f);
	GraphSignal(testSignal);

	delete testSignal;





	//RunAllUnitTests();

	/*
	float* distribution = NormalDistribution(DATA_LENGTH, 1.5f, 0.25f, 2);

	RunningStats* runningStats = new RunningStats(distribution, DATA_LENGTH);
	Histogram* hist = new Histogram(256, distribution, DATA_LENGTH);

	std::cout << "RSMean: " << Mean(runningStats) << std::endl;
	std::cout << "RSStdDev: " << StandardDeviation(runningStats) << std::endl;

	std::cout << "HMean: " << Mean(hist) << std::endl;
	std::cout << "HStdDev: " << StandardDeviation(hist) << std::endl;

	std::cout << "Mean: " << Mean(distribution, DATA_LENGTH) << std::endl;
	std::cout << "StdDev: " << StandardDeviation(distribution, DATA_LENGTH) << std::endl;

	*/

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
