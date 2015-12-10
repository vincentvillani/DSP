/*
 * Filters.h
 *
 *  Created on: 6 Dec 2015
 *      Author: vincent
 */

#ifndef FILTERS_H_
#define FILTERS_H_

#include "Signal.h"

#include <stdint.h>

Signal* GenerateMovingAverageFilter(uint32_t length);

Signal* GenerateBlackmanWindowedSincLowPassFilter(uint32_t length, float cutoffFrequency);

//Cutoff frequency is a fraction of the highest signal frequency, from 0.0 to 0.5
Signal* GenerateLowPassFilter(uint32_t evenLength, float cutoffFrequency);

Signal* GenerateHighPassFilter(uint32_t evenLength, float cutoffFrequency);

Signal* GenerateBandPassFilter(uint32_t evenLength, float cutoffFrequencyStart, float cutoffFrequencyEnd);

Signal* GenerateBandRejectFilter(uint32_t evenLength, float cutoffFrequencyStart, float cutoffFrequencyEnd);


#endif /* FILTERS_H_ */
