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

#include "Signal.h"
#include "Histogram.h"
#include "RunningStats.h"


float Mean(const Signal* signal);
float Mean(const Histogram* histogram);
float Mean(const RunningStats* runningStat);


float StandardDeviation(const Signal* signal);
float StandardDeviation(const Histogram* histogram);
float StandardDeviation(const RunningStats* runningStat);


float* ProbabilityMassFunction(const Histogram* histogram);


#endif /* STATS_H_ */
