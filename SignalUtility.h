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

#include <string>

Signal* SignalDeepCopy(Signal* signal);

void SignalWriteToTextFile(const std::string filename, const Signal* signal);

void SignalGraph(const Signal* signal);

void SignalSpectralInversionInPlace(Signal* signal);

Signal* SignalAmplify(const Signal* signal, float amplificationCoefficent);
void SignalAmplifyInPlace(Signal* signal, float amplificationCoefficent);

Signal* SignalAddition(const Signal* signal1, const Signal* signal2);
void SignalAdditionInPlace(Signal* signalLHS, const Signal* signalRHS); //Add RHS to LHS

void SignalShiftInPlace(Signal* signal, uint32_t shiftAmount); //Signal wraps around


float SignalToNoiseRatio(const Histogram* histogram);
float SignalToNoiseRatio(const RunningStats* runningStat);


float CoefficientOfVariation(const Histogram* histogram);
float CoefficientOfVariation(const RunningStats* runningStat);

Signal* SignalIntegrate(Signal* passedSignal);
void SignalIntegrateInPlace(Signal* passedSignal);

Signal* SignalDerivative(Signal* passedSignal);
void SignalDerivativeInPlace(Signal* passedSignal);

#endif /* SIGNALUTILITY_H_ */
