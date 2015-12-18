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
#include "FrequencySignalUtility.h"
#include "Convolution.h"
#include "DiscreteFourierTransform.h"
#include "Window.h"

#define PI 3.14159265359f

Signal* FilterGenerateMovingAverageFilter(uint32_t length)
{
	float filterValue = 1.0f / length;

	float* signalSamples = new float[length];

	for(uint32_t i = 0; i < length; ++i)
	{
		signalSamples[i] = filterValue;
	}

	return new Signal(signalSamples, length);
}


Signal* FilterGenerateBlackmanWindowedSincLowPassFilter(uint32_t evenLength, float cutoffFrequency)
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


Signal* FilterGenerateLowPassFilter(uint32_t evenLength, float cutoffFrequency)
{
	return FilterGenerateBlackmanWindowedSincLowPassFilter(evenLength, cutoffFrequency);
}


Signal* FilterGenerateHighPassFilter(uint32_t evenLength, float cutoffFrequency)
{
	Signal* result = FilterGenerateBlackmanWindowedSincLowPassFilter(evenLength, 0.5f - cutoffFrequency);

	SignalSpectralInversionInPlace(result);

	return result;
}


Signal* FilterGenerateBandPassFilter(uint32_t evenLength, float cutoffFrequencyStart, float cutoffFrequencyEnd)
{
	Signal* result;

	Signal* lowPassFilter = FilterGenerateLowPassFilter(evenLength, cutoffFrequencyEnd);
	Signal* highPassFilter = FilterGenerateHighPassFilter(evenLength, cutoffFrequencyStart);

	result = TimeDomainConvolution(lowPassFilter, highPassFilter);

	delete lowPassFilter;
	delete highPassFilter;

	return result;
}


Signal* FilterGenerateBandRejectFilter(uint32_t evenLength, float cutoffFrequencyStart, float cutoffFrequencyEnd)
{
	Signal* result;

	Signal* lowPassFilter = FilterGenerateLowPassFilter(evenLength, cutoffFrequencyStart);
	Signal* highPassFilter = FilterGenerateHighPassFilter(evenLength, cutoffFrequencyEnd);

	result = SignalAddition(lowPassFilter, highPassFilter);

	delete lowPassFilter;
	delete highPassFilter;

	return result;
}


Signal* FilterGenerateCustomFilterKernel(FrequencySignal* desiredFrequencyResponse, uint32_t evenTruncatedLength)
{
	if(evenTruncatedLength % 2 != 0)
	{
		std::cerr << "Even truncated length should be an even number!" << std::endl;
		exit(1);
	}
	else if(evenTruncatedLength > (desiredFrequencyResponse->realSignal->sampleLength * 2) - 1)
	{
		std::cerr << "desiredFrequencyResponse length should be greater than evenTruncatedLength" << std::endl;
		exit(1);
	}

	//Convert the desiredFrequency response to rectangular form before continuing
	if(desiredFrequencyResponse->type == POLAR)
	{
		FrequencySignalConvertToRectangularCoordinates(desiredFrequencyResponse);
	}

	//Take the Inverse DFT to get the signal into the time domain
	Signal* tempSignal = InverseDFTViaCorrelation(desiredFrequencyResponse);

	//SignalGraph(tempSignal);

	//Shift the signal across by evenTruncatedLength/2 so that the signal is centered at the center
	SignalShiftInPlace(tempSignal, evenTruncatedLength/2);
	//SignalGraph(tempSignal);

	//Generate the Hamming window
	//Signal* hammingWindow = WindowGenerateHammingWindow(evenTruncatedLength - 1);

	//Compute the filter kernel
	Signal* result = new Signal(new float[evenTruncatedLength + 1], evenTruncatedLength + 1); //So there is an even number of elements on either side of the middle element

	float twoPI = 2.0f * PI;
	float fourPI = 4.0f * PI;

	//Multiply the amplitudes of the hamming window by the amplitudes of the real values (sine waves?)
	for(uint32_t i = 0; i < evenTruncatedLength + 1; ++i)
	{
		//Times the truncated signal by the hamming window
		result->samples[i] = tempSignal->samples[i] * (0.54f - (0.46f * cosf(twoPI * i / (evenTruncatedLength)  ) ) );

		//Times the truncated signal by the blackman window
		//result->samples[i] = tempSignal->samples[i] * (0.42659f - (0.49656f * cosf((twoPI * i) / (evenTruncatedLength)) +
			//	0.076849f * cosf((fourPI * i) / (evenTruncatedLength))));
	}

	//SignalGraph(result);

	//Signal* stepResponse = SignalIntegrate(result);
	//SignalGraph(stepResponse);

	delete tempSignal;

	return result;
}

