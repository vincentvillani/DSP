/*
 * SignalUtility.h
 *
 *  Created on: 14 Nov 2015
 *      Author: vincent
 */

#ifndef SIGNALUTILITY_H_
#define SIGNALUTILITY_H_

#include "RunningStats.h"
#include "Histogram.h"
#include "Stats.h"

float SignalToNoiseRatio(const Histogram* histogram);
float SignalToNoiseRatio(const RunningStats* runningStat);


float CoefficientOfVariation(const Histogram* histogram);
float CoefficientOfVariation(const RunningStats* runningStat);

#endif /* SIGNALUTILITY_H_ */
