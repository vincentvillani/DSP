/*
 * Noise.cpp
 *
 *  Created on: 17 Nov 2015
 *      Author: vincentvillani
 */


#include <random>
#include <chrono>

float* NormalDistribution(uint32_t numberOfSamples, float mean, float stdDev, uint32_t seed)
{
	float* result = new float[numberOfSamples];

	// construct a trivial random generator engine from a seed:
	std::default_random_engine generator (seed); //TODO: Turn this into something better

	//Setup the normal distribution
	std::normal_distribution<float> normalDistribution (mean, stdDev);

	for(uint32_t i = 0; i < numberOfSamples; ++i)
	{
		result[i] = normalDistribution(generator);
	}

	return result;
}



float* NormalDistribution(uint32_t numberOfSamples, float mean, float stdDev)
{
	float* result = new float[numberOfSamples];

	// construct a trivial random generator engine from a time-based seed:
	uint32_t seed = std::chrono::system_clock::now().time_since_epoch().count();
	std::default_random_engine generator (seed); //TODO: Turn this into something better

	//Setup the normal distribution
	std::normal_distribution<float> normalDistribution (mean, stdDev);

	for(uint32_t i = 0; i < numberOfSamples; ++i)
	{
		result[i] = normalDistribution(generator);
	}

	return result;
}
