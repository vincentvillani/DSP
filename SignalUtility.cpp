/*
 * SignalUtility.cpp
 *
 *  Created on: 14 Nov 2015
 *      Author: vincent
 */


#include "SignalUtility.h"

#include <cstring>
#include <iostream>
#include <stdint.h>
#include <cstdio>


static uint32_t tempGraphNumber = 0;

void WriteSignalToTextFile(const std::string filename, const Signal* signal)
{
	FILE* signalFile = fopen(filename.c_str(), "w");

	if(signalFile == NULL)
		return;

	uint32_t i = 0;

	for(; i < signal->sampleLength - 1; ++i)
	{
		fprintf(signalFile, "%u %f\n", i, signal->samples[i]);
	}

	//print last line to the text file without the newline
	fprintf(signalFile, "%u %f", i, signal->samples[i]);


	fclose(signalFile);
}


void GraphSignal(const Signal* signal)
{
	char filenameBuffer[50];
	sprintf(filenameBuffer, "TempSignal%u.txt", tempGraphNumber);
	tempGraphNumber++;

	WriteSignalToTextFile(filenameBuffer, signal);

	FILE* gnuplot;
	gnuplot = popen("gnuplot -persist", "w"); //Linux
	//gnuplot = popen("/usr/local/bin/gnuplot -persist", "w"); //OSX

	if (gnuplot == NULL)
		return;

	fprintf(gnuplot, "set xrange[0 : %u]\n", signal->sampleLength);
	fprintf(gnuplot, "set offset graph 0.01, 0.01, 0.01, 0.01\n");
	fprintf(gnuplot, "set samples %u\n", signal->sampleLength);
	fprintf(gnuplot, "plot \"%s\" with points pointtype 5  notitle\n", filenameBuffer);
	//fprintf(gnuplot, "plot \"%s\" with impulses lw 1 notitle\n", "TempGraphFile.txt");
}


Signal* SignalAmplify(const Signal* signal, float amplificationCoefficent)
{
	uint32_t signalLength = signal->sampleLength;
	Signal* result = new Signal(new float[signalLength], signalLength);

	for(uint32_t i = 0; i < signalLength; ++i)
	{
		result->samples[i] = signal->samples[i] * amplificationCoefficent;
	}

	return result;
}


void SignalAmplifyInPlace(Signal* signal, float amplificationCoefficent)
{
	uint32_t signalLength = signal->sampleLength;

	for(uint32_t i = 0; i < signalLength; ++i)
	{
		signal->samples[i] *= amplificationCoefficent;
	}
}


Signal* SignalAddition(const Signal* signalLHS, const Signal* signalRHS)
{
	if(signalLHS->sampleLength != signalRHS->sampleLength)
	{
		std::cerr << "Tried to add two signals that are not the same length" << std::endl;
		exit(1);
	}

	uint32_t signalLength = signalLHS->sampleLength;
	Signal* result = new Signal(new float[signalLength], signalLength);

	//Add the signals together
	for(uint32_t i = 0 ; i < signalLength; ++i)
	{
		result->samples[i] = signalLHS->samples[i] + signalRHS->samples[i];
	}

	return result;
}


void SignalAdditionInPlace(Signal* signalLHS, const Signal* signalRHS) //Add RHS to LHS
{
	if(signalLHS->sampleLength != signalRHS->sampleLength)
	{
		std::cerr << "Tried to add two signals that are not the same length" << std::endl;
		exit(1);
	}

	//Add the signals together
	for(uint32_t i = 0 ; i < signalLHS->sampleLength; ++i)
	{
		signalLHS->samples[i] += signalRHS->samples[i];
	}
}



float SignalToNoiseRatio(const Histogram* histogram)
{
	return Mean(histogram) / StandardDeviation(histogram);
}


float SignalToNoiseRatio(const RunningStats* runningStat)
{
	return Mean(runningStat) / StandardDeviation(runningStat);
}



float CoefficientOfVariation(const Histogram* histogram)
{
	return (StandardDeviation(histogram) / Mean(histogram) ) * 100.0f;
}


float CoefficientOfVariation(const RunningStats* runningStat)
{
	return (StandardDeviation(runningStat) / Mean(runningStat) ) * 100.0f;
}



Signal* SignalIntegrate(Signal* passedSignal)
{

	uint32_t signalLength = passedSignal->sampleLength;
	Signal* result = new Signal(new float[signalLength], signalLength);


	//Do the first sample
	result->samples[0] = passedSignal->samples[0];

	//Integrate the remaining samples
	for(uint32_t i = 1; i < signalLength; ++i)
	{
		result->samples[i] = result->samples[i - 1] + passedSignal->samples[i];
	}

	return result;
}


void SignalIntegrateInPlace(Signal* passedSignal)
{
	uint32_t signalLength = passedSignal->sampleLength;

	//Integrate along the signal
	for(uint32_t i = 1; i < signalLength; ++i)
	{
		passedSignal->samples[i] += passedSignal->samples[i - 1];
	}
}


Signal* SignalDerivative(Signal* passedSignal)
{
	uint32_t signalLength = passedSignal->sampleLength;
	Signal* result = new Signal(new float[signalLength], signalLength);

	//Derive the signal, from the end working backwards, stop at index 0
	for(uint32_t i = 1; i < signalLength; ++i)
	{
		result->samples[i] = passedSignal->samples[i] - passedSignal->samples[i - 1];
	}

	return result;

}


void SignalDerivativeInPlace(Signal* passedSignal)
{
	uint32_t signalLength = passedSignal->sampleLength;

	//Derive the signal, from the end working backwards, stop at index 0
	//This has to be done to stop overwriting data we need as we do the calculations
	for(uint32_t i = signalLength - 1; i > 0; --i)
	{
		passedSignal->samples[i] = passedSignal->samples[i] - passedSignal->samples[i - 1];
	}
}


