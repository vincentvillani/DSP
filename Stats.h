/*
 * Stats.h
 *
 *  Created on: 12 Nov 2015
 *      Author: vincent
 */

#ifndef STATS_H_
#define STATS_H_

#include <stdlib.h>
#include <cmath>
#include <cstdint>


template<typename T>
T Mean(T* data, uint32_t length);

template<typename T>
T StandardDeviation(T* data, uint length);



template<typename T>
T Mean(T* data, uint32_t length)
{
	T result = 0;

	for(uint32_t i = 0; i < length; ++i)
	{
		result += data[i];
	}

	return result / length;
}


template<typename T>
T StandardDeviation(T* data, uint32_t length)
{
	T result = 0;
	T average = Mean(data, length);

	for(uint32_t i = 0; i < length; ++i)
	{
		result += pow(data[i] - average, 2);
	}

	result /= (length - 1);

	return sqrt(result);
}


#endif /* STATS_H_ */
