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

Signal* SignalAmplify(const Signal* signal, float amplificationCoefficent);
void SignalAmplifyInPlace(Signal* signal, float amplificationCoefficent);

Signal* SignalAddition(const Signal* signal1, const Signal* signal2);
void SignalAdditionInPlace(Signal* signalLHS, const Signal* signalRHS); //Add RHS to LHS


float SignalToNoiseRatio(const Histogram* histogram);
float SignalToNoiseRatio(const RunningStats* runningStat);


float CoefficientOfVariation(const Histogram* histogram);
float CoefficientOfVariation(const RunningStats* runningStat);

#endif /* SIGNALUTILITY_H_ */
