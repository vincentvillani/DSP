/*
 * DiscreteFourierTransform.cpp
 *
 *  Created on: 27 Nov 2015
 *      Author: vincentvillani
 */

#include "DiscreteFourierTransform.h"

#include <cmath>

#include "DFTUtility.h"

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

	float trigArgument;
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
			trigArgument = (PI * 2.0f * i * j) / inputSignal->sampleLength;
			dftOutput->realSignal->samples[i] += cosf(trigArgument) * inputSignal->samples[j];
			dftOutput->imaginarySignal->samples[i] += -(sinf(trigArgument) * inputSignal->samples[j]);
		}
	}


	return dftOutput;
}


Signal* InverseDFTCorrelation(DFTCorrelationOutput* input)
{
	if(input->type == POLAR)
		ConvertToRectangularCoordinates(input);

	//Used to store the scaled values of ReX and ImX (the frequency domain of the signal)
	//float ReXAmplitude, ImXAmplitude;
	uint32_t timeDomainSampleNum = (input->realSignal->sampleLength - 1) * 2;
	uint32_t NDivideTwo = input->realSignal->sampleLength - 1;

	//Convert the frequency domain of the cosine and sine waves into the amplitude of the cosine and sine waves
	float* ReXAmp = new float[input->realSignal->sampleLength];
	float* ImXAmp = new float[input->realSignal->sampleLength]; //Real and imag sample length should be the same

	//ReX Amplitude first
	//Special cases
	ReXAmp[0] = input->realSignal->samples[0] / timeDomainSampleNum;
	ReXAmp[NDivideTwo] = input->realSignal->samples[NDivideTwo] / timeDomainSampleNum;

	//The general cases
	for(uint32_t i = 1; i < NDivideTwo; ++i)
	{
		ReXAmp[i] = input->realSignal->samples[i] / NDivideTwo;
	}

	//Calculate ImX amplitude
	for(uint32_t i = 0; i < input->imaginarySignal->sampleLength; ++i)
	{
		ImXAmp[i] = -(input->imaginarySignal->samples[i] / NDivideTwo);
	}

	//Calculate the inverse DFT ('Synthesis')
	float* outputSignalData = new float[timeDomainSampleNum];
	float trigArgument;

	for(uint32_t i = 0; i < timeDomainSampleNum; ++i)
	{
		//Set the value to zero to begin
		outputSignalData[i] = 0;

		for(uint32_t ampIndex = 0; ampIndex < input->realSignal->sampleLength; ++ampIndex)
		{
			trigArgument = (2.0f * PI * ampIndex * i) / timeDomainSampleNum;

			outputSignalData[i] += ReXAmp[ampIndex] * cosf(trigArgument);
			outputSignalData[i] += ImXAmp[ampIndex] * sinf(trigArgument);
		}
	}

	delete[] ReXAmp;
	delete[] ImXAmp;

	return new Signal(outputSignalData, timeDomainSampleNum);

}

