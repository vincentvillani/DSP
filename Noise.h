/*
 * Noise.h
 *
 *  Created on: 17 Nov 2015
 *      Author: vincentvillani
 */

#ifndef NOISE_H_
#define NOISE_H_


#include <stdint.h>

float* NormalDistribution(uint32_t numberOfSamples, float mean, float stdDev, uint32_t seed);
float* NormalDistribution(uint32_t numberOfSamples, float mean, float stdDev);

#endif /* NOISE_H_ */
