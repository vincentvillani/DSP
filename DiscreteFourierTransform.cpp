/*
 * DiscreteFourierTransform.cpp
 *
 *  Created on: 27 Nov 2015
 *      Author: vincentvillani
 */

#include "DiscreteFourierTransform.h"

#include <cmath>

#define PI 3.14159265359f

float* SineBasisFunction(uint32_t signalLength, uint32_t frequency)
{
	float* sineWave = new float[signalLength];

	for(uint32_t i = 0; i < signalLength; ++i)
	{
		sineWave[i] = sinf( (PI * 2.0f * frequency * i) / signalLength);
	}

	return sineWave;
}


float* CosineBasisFunction(uint32_t signalLength, uint32_t frequency)
{
	float* cosineWave = new float[signalLength];

	for(uint32_t i = 0; i < signalLength; ++i)
	{
		cosineWave[i] = cosf( (PI * 2.0f * frequency * i) / signalLength);
	}

	return cosineWave;
}


DFTCorrelationOutput* DFTCorrelation(Signal* inputSignal)
{
	DFTCorrelationOutput* dftOutput = new DFTCorrelationOutput();

	//Number of real and imaginary numbers each real and imaginary array will have
	uint32_t outputValuesNum = (inputSignal->sampleLength / 2) + 1;

	//Allocate space for the output arrays
	dftOutput->realSignal = new Signal(new float[outputValuesNum], outputValuesNum);
	dftOutput->imaginarySignal = new Signal(new float[outputValuesNum], outputValuesNum);

	//Calculate the DFT values
	//For each result index (N/2 + 1)
	for(uint32_t i = 0; i < outputValuesNum; ++i)
	{
		dftOutput->realSignal->samples[i] = 0;
		dftOutput->imaginarySignal->samples[i] = 0;

		//Calculate the real and imaginary values
		//Number of samples
		for(uint32_t j = 0; j < inputSignal->sampleLength; ++j)
		{
			//Basis wave sample * input signal sample
			//j = current sample in basis wave & input signal, i = frequency of the current basis wave
			dftOutput->realSignal->samples[i] += cosf( (PI * 2.0f * i * j) / inputSignal->sampleLength) * inputSignal->samples[j];
			dftOutput->imaginarySignal->samples[i] += -(sinf( (PI * 2.0f * i * j) / inputSignal->sampleLength) * inputSignal->samples[j]);
		}
	}


	return dftOutput;
}
