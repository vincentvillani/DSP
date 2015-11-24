/*
 * SignalUtility.cpp
 *
 *  Created on: 14 Nov 2015
 *      Author: vincent
 */


#include "SignalUtility.h"
#include <cstring>
#include <iostream>

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



Signal* Convolution(Signal* inputSignal, Signal* impulseResponse)
{
	uint32_t firstValidIndex = impulseResponse->sampleLength - 1;
	//uint32_t lastValidIndex = inputSignal->sampleLength - firstValidIndex;
	uint32_t lengthOfOutputSignal = (inputSignal->sampleLength + impulseResponse->sampleLength - 1) - (firstValidIndex * 2);

	float* outputSamples = new float[lengthOfOutputSignal];
	memset(outputSamples, 0, sizeof(float) * lengthOfOutputSignal);

	uint32_t outputIndex;

	//Do all the calculations for the first few input, note less than or equal too!
	//Only does the necessary calculations for these first few output indexes
	for(uint32_t inputSignalIndex = 0; inputSignalIndex < firstValidIndex; ++inputSignalIndex)
	{
		//Reset the output index
		outputIndex = 0;

		for(uint32_t impulseIndex = firstValidIndex - inputSignalIndex; impulseIndex < impulseResponse->sampleLength; ++impulseIndex)
		{
			outputSamples[outputIndex] += (inputSignal->samples[inputSignalIndex] * impulseResponse->samples[impulseIndex]);
			outputIndex++;
		}
	}


	//Carry on the normal convolution process
	for(outputIndex = 0; outputIndex < lengthOfOutputSignal; ++outputIndex)
	{
		for(uint32_t impulseIndex = 0; impulseIndex < impulseResponse->sampleLength; ++impulseIndex)
		{
			outputSamples[outputIndex + impulseIndex] += (inputSignal->samples[outputIndex + firstValidIndex] * impulseResponse->samples[impulseIndex]);
		}
	}

	Signal* signal = new Signal(outputSamples, lengthOfOutputSignal);

	return signal;

}