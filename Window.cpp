/*
 * Window.cpp
 *
 *  Created on: 13 Dec 2015
 *      Author: vincent
 */


#include "Window.h"

#include <cmath>
#include <iostream>

#define PI 3.14159265359f

Signal* WindowGenerateHammingWindow(uint32_t evenLength)
{

	//Has to be an odd number to be symmetrical
	if(evenLength % 2 != 0)
	{
		std::cerr << "WindowGenerateHammingWindow: evenLength is not an even number!" << std::endl;
		exit(1);
	}

	//Add one so that the signal is , same number of elements either side of the middle element
	uint32_t signalLength = evenLength + 1;

	//Calculate the result
	Signal* result = new Signal(new float[signalLength], signalLength);
	float twoPI = 2 * PI;

	for(uint32_t i = 0; i < signalLength; ++i)
	{
		result->samples[i] = 0.54f - (0.46 * cosf((twoPI * i) / evenLength)); //Even length is used here for the hamming window (signalLength -1)
	}

	return result;
}


Signal* WindowGenerateBlackmanWindow(uint32_t length)
{
	for(uint32_t i = 0; i < length; ++i)
	{

	}
}

