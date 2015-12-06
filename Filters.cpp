/*
 * Filters.cpp
 *
 *  Created on: 6 Dec 2015
 *      Author: vincent
 */

#include "Filters.h"

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

