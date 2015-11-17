/*
 * Histogram.cpp
 *
 *  Created on: 14 Nov 2015
 *      Author: vincent
 */

#include <cstring>
#include <float.h>
#include <cmath>
#include <iostream>

#include "Histogram.h"



Histogram::Histogram(uint32_t binNum, float* data, uint32_t dataLength)
{

	float dataMin, dataMax;

	//Set the min to the max and the max to the min...
	dataMin = data[0];
	dataMax = data[0];

	//Go thorough the data and find the min and max
	for(uint32_t i = 1; i < dataLength; ++i)
	{

		if(data[i] < dataMin)
			dataMin = data[i];
		else if(data[i] > dataMax)
			dataMax = data[i];
	}


	//Start constructing the histogram
	this->binNum = binNum;
	this->dataSampleNum = dataLength;
	this->bucketDistance = fabs(dataMax - dataMin);

	//Set the histogram values to zero
	this->bins = new uint32_t[binNum];
	memset(this->bins, 0, sizeof(uint32_t) * binNum);

	float rangeOfValues = dataMax - dataMin;
	uint32_t binIndex;

	for(uint32_t i = 0; i < dataLength; ++i)
	{
		binIndex = ((data[i] - dataMin) / rangeOfValues) * (binNum - 1);

		this->bins[binIndex] += 1;
	}


}




Histogram::Histogram(uint32_t binNum, float dataMin, float dataMax, float* data, uint32_t dataLength)
{
	this->binNum = binNum;
	this->dataSampleNum = dataLength;
	this->bucketDistance = fabs(dataMax - dataMin);

	//Set the histogram values to zero
	this->bins = new uint32_t[binNum];
	memset(this->bins, 0, sizeof(uint32_t) * binNum);

	//Start constructing the histogram
	float rangeOfValues = dataMax - dataMin;
	uint32_t binIndex;

	for(uint32_t i = 0; i < dataLength; ++i)
	{
		binIndex = ((data[i] - dataMin) / rangeOfValues) * (binNum - 1);

		this->bins[binIndex] += 1;
	}
}


Histogram::~Histogram()
{
	delete[] this->bins;
}


