/*
 * Stats.cpp
 *
 *  Created on: 12 Nov 2015
 *      Author: vincent
 */

#include "Stats.h"


float Mean(const float* data, uint32_t length)
{
	float result = 0;

	for(uint32_t i = 0; i < length; ++i)
	{
		result += data[i];
	}

	return result / length;
}



float Mean(const Histogram* histogram)
{
	float result = 0;

	for(uint32_t i = 0; i < histogram->binNum; ++i)
	{
		result += i * histogram->bins[i]; //
	}

	result *= (1.0f / histogram->dataSampleNum);

	return result;
}


float Mean(const RunningStats* runningStat)
{
	return (float)runningStat->sum / runningStat->length;
}



float StandardDeviation(const float* data, uint32_t length)
{
	float result = 0;
	float average = Mean(data, length);

	for(uint32_t i = 0; i < length; ++i)
	{
		result += pow(data[i] - average, 2);
	}

	result /= (length - 1);

	return sqrt(result);
}



float StandardDeviation(const Histogram* histogram)
{
	float result = 0;
	float mean = Mean(histogram);

	for(uint32_t i = 0; i < histogram->binNum; ++i)
	{
		result += (powf((i - mean), 2)) * histogram->bins[i];
	}

	result *= (1.0f / (histogram->binNum - 1));

	return sqrtf(result);
}



float StandardDeviation(const RunningStats* runningStat)
{
	float result =  runningStat->sumOfSquares - (powf(runningStat->sum, 2) / runningStat->length);

	result *= (1.0f / (runningStat->length - 1));

	return sqrtf(result);
}



float* ProbabilityMassFunction(const Histogram* histogram)
{
	//Calculate the PMF
	float* pmf = new float[histogram->binNum];

	for(uint32_t i = 0; i < histogram->binNum; ++i)
	{
		pmf[i] = histogram->bins[i] / histogram->dataSampleNum;
	}

	return pmf;
}
