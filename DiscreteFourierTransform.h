/*
 * DiscreteFourierTransform.h
 *
 *  Created on: 27 Nov 2015
 *      Author: vincentvillani
 */

#ifndef DISCRETEFOURIERTRANSFORM_H_
#define DISCRETEFOURIERTRANSFORM_H_

#include <stdint.h>

#include "Signal.h"
#include "FrequencySignal.h"

float* SineBasisFunction(uint32_t signalLength, uint32_t frequency);
float* CosineBasisFunction(uint32_t signalLength, uint32_t frequency);

//Discrete Fourier Transform via Correlation
FrequencySignal* DFTViaCorrelation(Signal* inputSignal);
Signal* InverseDFTViaCorrelation(FrequencySignal* input);


#endif /* DISCRETEFOURIERTRANSFORM_H_ */
