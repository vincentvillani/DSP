/*
 * Convolution.h
 *
 *  Created on: 2 Dec 2015
 *      Author: vincent
 */

#ifndef CONVOLUTION_H_
#define CONVOLUTION_H_

#include "Signal.h"
#include "FrequencySignal.h"

//Returns a convoluted signal that is fully immersed in the input signal (clips the start and end of the output)
//CONVOLUTION IN THE TIME DOMAIN
Signal* TimeDomainConvolution(Signal* inputSignal, Signal* impulseResponse);
//FrequencySignal* FrequencyDomainConvolution(FrequencySignal* inputDFT, FrequencySignal* impulseResponse);


#endif /* CONVOLUTION_H_ */
