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

#define PI 3.14159265359f

void DFTCorrelationUnitTest()
{
	const uint32_t sampleNum = 64;
	const uint32_t frequency = 3;
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
		if(i == 3)
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


	delete inputSignal;
	delete output;
}

