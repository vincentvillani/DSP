/*
 * RunningStats.h
 *
 *  Created on: 12 Nov 2015
 *      Author: vincent
 */

#ifndef RUNNINGSTATS_H_
#define RUNNINGSTATS_H_

#include <cstdint>
#include <cmath>

template<typename T>
class RunningStats
{
private:

	uint32_t _length;
	uint32_t _sumOfSquares;
	uint32_t _sum;

public:



	RunningStats();
	virtual ~RunningStats();

	void update(T* data, uint32_t length);

	T mean();
	T standardDeviation();
	float signalToNoise();
	float coefficientOfVariation();


};


template<typename T>
RunningStats<T>::RunningStats()
{
	_length = 0;
	_sumOfSquares = 0;
	_sum = 0;
}


template<typename T>
RunningStats<T>::~RunningStats()
{

}


template<typename T>
void RunningStats<T>::update(T* data, uint32_t length)
{
	_length += length;

	for(uint32_t i = 0; i < length; ++i)
	{
		_sum += data[i];
		_sumOfSquares += pow(data[i], 2);
	}
}


template<typename T>
T RunningStats<T>::mean()
{
	T result = _sum / _length;
	return result;
}


template<typename T>
T RunningStats<T>::standardDeviation()
{
	T result =  _sumOfSquares - (pow(_sum, 2) / _length);

	result *= (1.0 / (_length - 1));

	return sqrt(result);
}


template<typename T>
float RunningStats<T>::signalToNoise()
{
	return mean() / standardDeviation();
}


template<typename T>
float RunningStats<T>::coefficientOfVariation()
{
	return (standardDeviation() / mean() ) * 100.0f;
}


#endif /* RUNNINGSTATS_H_ */
