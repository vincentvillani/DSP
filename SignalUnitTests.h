/*
 * SignalUnitTests.h
 *
 *  Created on: 24 Nov 2015
 *      Author: vincent
 */

#ifndef SIGNALUNITTESTS_H_
#define SIGNALUNITTESTS_H_

#include "Signal.h"
#include "SignalUtility.h"

void Signal_PrintSignal(Signal* signal);
void Signal_UpdateUnitTest();
void Signal_ConvolutionUnitTest();

void Signal_IntegrationUnitTest();
void Signal_DerivativeUnitTest();
void Signal_IntegrationAndDerivativeRoundTripUnitTest();



#endif /* SIGNALUNITTESTS_H_ */
