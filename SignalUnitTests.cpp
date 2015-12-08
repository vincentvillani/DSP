/*
 * SignalUnitTests.cpp
 *
 *  Created on: 24 Nov 2015
 *      Author: vincent
 */



#include "SignalUnitTests.h"

#include <cassert>
#include <iostream>

#include "Convolution.h"

void Signal_PrintSignal(Signal* signal)
{
	for(uint32_t i = 0; i < signal->sampleLength; ++i)
	{
		std::cout << signal->samples[i] << ", ";
	}

	std::cout << std::endl;
}


void Signal_UpdateUnitTest()
{
	const uint32_t orignalDataLength = 3;
	const uint32_t updateDataLength = 2;

	float* originalTestData = new float[orignalDataLength];
	float* updateTestData = new float[updateDataLength];

	originalTestData[0] = 0;
	originalTestData[1] = 1;
	originalTestData[2] = 2;

	updateTestData[0] = 3;
	updateTestData[1] = 4;

	Signal* signal = new Signal(originalTestData, orignalDataLength);

	//Signal_PrintSignal(signal);

	for(uint32_t i = 0; i < orignalDataLength; ++i)
	{
		assert(signal->samples[i] == i);
	}

	signal->update(updateTestData, updateDataLength);

	//Signal_PrintSignal(signal);

	for(uint32_t i = 0; i < orignalDataLength + updateDataLength; ++i)
	{
		assert(signal->samples[i] == i);
	}

	delete signal;
}



void Signal_ConvolutionUnitTest()
{
	uint32_t inputLength = 6;
	uint32_t impulseLength = 3;

	float* inputSamples = new float[inputLength];
	float* impulseSamples = new float[impulseLength];
	float expectedOutput[4] = {4.25f, 6.0f, 7.75f, 9.5f};

	for(uint32_t i = 0; i < inputLength; ++i)
	{
		inputSamples[i] = i + 1;
	}

	impulseSamples[0] = 1.0f;
	impulseSamples[1] = 0.5f;
	impulseSamples[2] = 0.25f;

	Signal* inputSignal = new Signal(inputSamples, inputLength);
	Signal* impulseSignal = new Signal(impulseSamples, impulseLength);

	Signal* convolutionSignal = TimeDomainConvolution(inputSignal, impulseSignal);

	//Signal_PrintSignal(convolutionSignal);

	for(uint32_t i = 0; i < convolutionSignal->sampleLength; ++i)
	{
		assert(convolutionSignal->samples[i] - expectedOutput[i] < 0.000001);
	}

	delete inputSignal;
	delete impulseSignal;
	delete convolutionSignal;

}


void Signal_IntegrationUnitTest()
{
	Signal* signal = new Signal(new float[5], 5);

	for(uint32_t i = 0; i < 5; ++i)
	{
		signal->samples[i] = 5;
	}

	Signal* result = SignalIntegrate(signal);

	assert(result->samples[0] - 5.0f < 0.000001f);
	assert(result->samples[1] - 10.0f < 0.000001f);
	assert(result->samples[2] - 15.0f < 0.000001f);
	assert(result->samples[3] - 20.0f < 0.000001f);
	assert(result->samples[4] - 25.0f < 0.000001f);

	delete signal;
	delete result;
}


void Signal_DerivativeUnitTest()
{
	Signal* signal = new Signal(new float[5], 5);

	for(uint32_t i = 0; i < 5; ++i)
	{
		signal->samples[i] = 5;
	}

	Signal* result = SignalDerivative(signal);

	for(uint32_t i = 0; i < 5; ++i)
	{
		assert(result->samples[i] < 0.000001f);
	}

	delete signal;
	delete result;
}


void Signal_IntegrationAndDerivativeRoundTripUnitTest()
{
	Signal* signal = new Signal(new float[5], 5);

	for(uint32_t i = 0; i < 5; ++i)
	{
		signal->samples[i] = 5;
	}

	SignalIntegrateInPlace(signal);
	SignalDerivativeInPlace(signal);

	for(uint32_t i = 0; i < 5; ++i)
	{
		assert(signal->samples[i] - 5.0f < 0.000001f);
	}

	delete signal;

}

