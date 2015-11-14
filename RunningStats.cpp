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


RunningStats::~RunningStats()
{

}


void RunningStats::update(float* data, uint32_t length)
{
	this->length += length;

	for(uint32_t i = 0; i < length; ++i)
	{
		sum += data[i];
		sumOfSquares += pow(data[i], 2);
	}
}

