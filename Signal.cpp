/*
 * Signal.cpp
 *
 *  Created on: 24 Nov 2015
 *      Author: vincent
 */

#include "Signal.h"

#include <cstring>
#include <iostream>

/*
Signal::Signal()
{
	sampleLength = 0;
	samples = NULL;
}
*/

Signal::Signal(float* data, uint32_t dataLength)
{
	sampleLength = dataLength;
	samples = data;
}


Signal::~Signal()
{
	if(samples != NULL)
		delete[] samples;
}


void Signal::update(float* data, uint32_t dataLength)
{
	uint32_t newSampleLength = this->sampleLength + dataLength;
	float* newData = new float[newSampleLength];

	//Copy the current signal data into the new array
	memcpy(newData, this->samples, sizeof(float) * this->sampleLength);

	//Copy the new data into the new array
	memcpy(newData + this->sampleLength, data, sizeof(float) * dataLength);

	//Free the old signals data
	delete[] this->samples;

	this->samples = newData;
	this->sampleLength = newSampleLength;
}


void Signal::print()
{
	for(uint32_t i = 0; i < sampleLength; ++i)
	{
		std::cout << "[" << i << "]: " << samples[i] << std::endl;
	}

	std::cout << std::endl << std::endl;
}
