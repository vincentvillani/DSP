/*
 * Window.cpp
 *
 *  Created on: 13 Dec 2015
 *      Author: vincent
 */


#include "Window.h"

#include <cmath>

#define PI 3.14159265359f

Signal* WindowGenerateHammingWindow(uint32_t evenLength)
{
	/*
	//Has to be an odd number to be symmetrical
	if(length % 2 != 0)
	{

	}

	Signal* result = new Signal(new float[length], length);

	float twoPI = 2 * PI;
	uint32_t lengthMinusOne = length - 1;

	for(uint32_t i = 0; i < length; ++i)
	{
		result->samples[i] = 0.54f - (0.46 * cosf((twoPI * i) / lengthMinusOne));
	}

	return result;
	*/
}


Signal* WindowGenerateBlackmanWindow(uint32_t length)
{
	for(uint32_t i = 0; i < length; ++i)
	{

	}
}

