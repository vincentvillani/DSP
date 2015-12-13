/*
 * Filters.cpp
 *
 *  Created on: 6 Dec 2015
 *      Author: vincent
 */

#include "Filters.h"

#include <cmath>
#include <iostream>

#include "SignalUtility.h"
#include "Convolution.h"

#define PI 3.14159265359f

Signal* GenerateMovingAverageFilter(uint32_t length)
{
	float filterValue = 1.0f / length;

	float* signalSamples = new float[length];

	for(uint32_t i = 0; i < length; ++i)
	{
		signalSamples[i] = filterValue;
	}

	return new Signal(signalSamples, length);
}


Signal* GenerateBlackmanWindowedSincLowPassFilter(uint32_t evenLength, float cutoffFrequency)
{
	//Length must be odd so there is a center point with an even number of values on each side (this is done later... (evenLength + 1) )
	if(evenLength % 2 != 0)
		return NULL;


	Signal* result = new Signal(new float[evenLength + 1], evenLength + 1);

	uint32_t halfIndex = evenLength / 2;


	//Calculate almost half the values
	for(uint32_t i = 0; i < halfIndex; ++i)
	{
		float commonCalc = (i - (evenLength / 2.0f));

		result->samples[i] = sinf(2.0f * PI * cutoffFrequency * commonCalc) / commonCalc *
				(0.42f - (0.5f * cosf( (2.0f * PI * i) / evenLength) ) + (0.08f * cosf((4.0f * PI * i) / evenLength)));
	}

	//Calculate the halfway point like this due to divide by zero errors
	result->samples[halfIndex] = 2.0f * PI * cutoffFrequency;

	//Calculate the rest of the values as normal
	for(uint32_t i = halfIndex + 1; i < evenLength + 1; ++i)
	{

		float commonCalc = (i - (evenLength / 2.0f));

		result->samples[i] = (sinf(2.0f * PI * cutoffFrequency * commonCalc) / commonCalc) *
				(0.42f - (0.5f * cosf( (2.0f * PI * i) / evenLength) ) + (0.08f * cosf((4.0f * PI * i) / evenLength)));

	}


	//Sum all the generated values and divide each sample by the total sum to normalise the signal (all samples should sum to one)
	float sum = 0;

	for(uint32_t i = 0; i < evenLength + 1; ++i)
	{
		sum += result->samples[i];
	}

	for(uint32_t i = 0; i < evenLength + 1; ++i)
	{
		result->samples[i] /= sum;
	}


	return result;

}


Signal* GenerateLowPassFilter(uint32_t evenLength, float cutoffFrequency)
{
	return GenerateBlackmanWindowedSincLowPassFilter(evenLength, cutoffFrequency);
}


Signal* GenerateHighPassFilter(uint32_t evenLength, float cutoffFrequency)
{
	Signal* result = GenerateBlackmanWindowedSincLowPassFilter(evenLength, 0.5f - cutoffFrequency);

	SignalSpectralInversionInPlace(result);

	return result;
}


Signal* GenerateBandPassFilter(uint32_t evenLength, float cutoffFrequencyStart, float cutoffFrequencyEnd)
{
	Signal* result;

	Signal* lowPassFilter = GenerateLowPassFilter(evenLength, cutoffFrequencyEnd);
	Signal* highPassFilter = GenerateHighPassFilter(evenLength, cutoffFrequencyStart);

	result = TimeDomainConvolution(lowPassFilter, highPassFilter);

	delete lowPassFilter;
	delete highPassFilter;

	return result;
}


Signal* GenerateBandRejectFilter(uint32_t evenLength, float cutoffFrequencyStart, float cutoffFrequencyEnd)
{
	Signal* result;

	Signal* lowPassFilter = GenerateLowPassFilter(evenLength, cutoffFrequencyStart);
	Signal* highPassFilter = GenerateHighPassFilter(evenLength, cutoffFrequencyEnd);

	result = SignalAddition(lowPassFilter, highPassFilter);

	delete lowPassFilter;
	delete highPassFilter;

	return result;
}


Signal* ComputeCustomFilterKernel(FrequencySignal* desiredFrequencyResponse)
{
	Signal* result;

	//Take the Inverse DFT to get the signal into the time domain
	//Signal* tempSignal = InverseDFTViaCorrelation(desiredFrequencyResponse);

	//Shift the signal across by signalLength/2


	return result;
}

