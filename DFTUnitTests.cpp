/*
 * DFTUnitTests.cpp
 *
 *  Created on: 28 Nov 2015
 *      Author: vincent
 */

#include "DFTUnitTests.h"

#include <stdint.h>
#include <cmath>
#include <iostream>
#include <assert.h>

#include "Signal.h"
#include "DiscreteFourierTransform.h"
#include "DFTUtility.h"

#define PI 3.14159265359f

void DFTCorrelationUnitTest()
{
	const uint32_t sampleNum = 64;
	const uint32_t frequency = 2;
	float* inputSignalData = new float[sampleNum];

	//Calculate input signal, a sin wave with frequency 3
	for(uint32_t i = 0; i < sampleNum; ++i)
	{
		inputSignalData[i] = cosf( (2 * PI * frequency * i) / sampleNum);
	}

	Signal* inputSignal = new Signal(inputSignalData, sampleNum);

	DFTCorrelationOutput* output = DFTCorrelation(inputSignal);

	/*
	std::cout << "------ Real signal ------" << std::endl;
	output->realSignal->print();

	std::cout << "------ Imaginary signal ------" << std::endl;
	output->imaginarySignal->print();
	*/


	for(uint32_t i = 0; i < sampleNum; ++i)
	{
		if(i == frequency)
		{
			//This sample should be 32 with the current input signal
			assert(output->realSignal->samples[3] - 32.0f < 0.000001f);
			assert(output->imaginarySignal->samples[3] < 0.0001f);
		}
		else
		{
			assert(output->realSignal->samples[i] < 0.0001f);
			assert(output->imaginarySignal->samples[i] < 0.0001f || output->imaginarySignal->samples[i] == 0.0f);
		}
	}

	/*
	ConvertToPolarCoordinates(output);

	std::cout << "------ magnitude signal ------" << std::endl;
	output->realSignal->print();

	std::cout << "------ phase signal ------" << std::endl;
	output->imaginarySignal->print();


	ConvertToRectangularCoordinates(output);

	std::cout << "------ CONVERTED Real signal ------" << std::endl;
	output->realSignal->print();

	std::cout << "------ CONVERTED Imaginary signal ------" << std::endl;
	output->imaginarySignal->print();
	*/


	delete inputSignal;
	delete output;
}


void DFTCorrelationRoundTripTest()
{
	const uint32_t sampleNum = 64;
	const uint32_t frequency = 2;
	float* inputSignalData = new float[sampleNum];

	//Calculate input signal, a sin wave with frequency 3
	for(uint32_t i = 0; i < sampleNum; ++i)
	{
		inputSignalData[i] = cosf( (2 * PI * frequency * i) / sampleNum);
	}

	Signal* inputSignal = new Signal(inputSignalData, sampleNum);

	//Calculate the DFT
	DFTCorrelationOutput* output = DFTCorrelation(inputSignal);

	//Calculate the Inverse DFT
	Signal* convertedInputSignal = InverseDFTCorrelation(output);

	//Test to see if we got the same thing back
	for(uint32_t i = 0; i < sampleNum; ++i)
	{
		//std::cout << "O[" << i << "]: " << inputSignal->samples[i] << std::endl;
		//std::cout << "C[" << i << "]: " << convertedInputSignal->samples[i] << std::endl;
		assert(fabs(inputSignal->samples[i] - convertedInputSignal->samples[i]) < 0.00001f);
	}

	delete inputSignal;
	delete convertedInputSignal;
	delete output;
}

void DFTCorrelationRoundTripTestWithPolarCoords()
{
	const uint32_t sampleNum = 64;
	const uint32_t frequency = 2;
	float* inputSignalData = new float[sampleNum];

	//Calculate input signal, a sin wave with frequency 3
	for(uint32_t i = 0; i < sampleNum; ++i)
	{
		inputSignalData[i] = cosf( (2 * PI * frequency * i) / sampleNum);
	}

	Signal* inputSignal = new Signal(inputSignalData, sampleNum);

	//Calculate the DFT
	DFTCorrelationOutput* output = DFTCorrelation(inputSignal);

	ConvertToPolarCoordinates(output);

	//Calculate the Inverse DFT
	Signal* convertedInputSignal = InverseDFTCorrelation(output);

	//Test to see if we got the same thing back
	for(uint32_t i = 0; i < sampleNum; ++i)
	{
		//std::cout << "O[" << i << "]: " << inputSignal->samples[i] << std::endl;
		//std::cout << "C[" << i << "]: " << convertedInputSignal->samples[i] << std::endl;
		assert(fabs(inputSignal->samples[i] - convertedInputSignal->samples[i]) < 0.00001f);
	}

	delete inputSignal;
	delete convertedInputSignal;
	delete output;
}

