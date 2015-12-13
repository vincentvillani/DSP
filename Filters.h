/*
 * Filters.h
 *
 *  Created on: 6 Dec 2015
 *      Author: vincent
 */

#ifndef FILTERS_H_
#define FILTERS_H_

#include "Signal.h"
#include "FrequencySignal.h"

#include <stdint.h>

Signal* FilterGenerateMovingAverageFilter(uint32_t length);

Signal* FilterGenerateBlackmanWindowedSincLowPassFilter(uint32_t length, float cutoffFrequency);

//Cutoff frequency is a fraction of the highest signal frequency, from 0.0 to 0.5
Signal* FilterGenerateLowPassFilter(uint32_t evenLength, float cutoffFrequency);

Signal* FilterGenerateHighPassFilter(uint32_t evenLength, float cutoffFrequency);

Signal* FilterGenerateBandPassFilter(uint32_t evenLength, float cutoffFrequencyStart, float cutoffFrequencyEnd);

Signal* FilterGenerateBandRejectFilter(uint32_t evenLength, float cutoffFrequencyStart, float cutoffFrequencyEnd);

//evenActualFilterLength needs to be an even number. evenActualFilterLength + 1 is the length of the generated filter
Signal* FilterGenerateCustomFilterKernel(FrequencySignal* desiredFrequencyResponse, uint32_t evenTruncatedLength);

#endif /* FILTERS_H_ */
