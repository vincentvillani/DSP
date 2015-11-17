/*
 * RunningStats.cpp
 *
 *  Created on: 14 Nov 2015
 *      Author: vincent
 */

#include <cmath>

#include "RunningStats.h"




RunningStats::RunningStats()
{
	length = 0;
	sumOfSquares = 0;
	sum = 0;
}


RunningStats::RunningStats(float* data, uint32_t dataLength)
{
	length = 0;
	sumOfSquares = 0;
	sum = 0;

	update(data, dataLength);
}


RunningStats::~RunningStats()
{

}


void RunningStats::update(float* data, uint32_t dataLength)
{
	this->length += dataLength;

	for(uint32_t i = 0; i < dataLength; ++i)
	{
		sum += data[i];
		sumOfSquares += powf(data[i], 2.0f);
	}
}

