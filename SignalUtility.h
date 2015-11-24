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
#include "Signal.h"

float SignalToNoiseRatio(const Histogram* histogram);
float SignalToNoiseRatio(const RunningStats* runningStat);


float CoefficientOfVariation(const Histogram* histogram);
float CoefficientOfVariation(const RunningStats* runningStat);

//Returns a convoluted signal that is fully immersed in the input signal (clips the start and end of the output)
Signal* Convolution(Signal* inputSignal, Signal* impulseResponse);

#endif /* SIGNALUTILITY_H_ */
