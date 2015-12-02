/*
 * DFTUtility.h
 *
 *  Created on: 28 Nov 2015
 *      Author: vincent
 */

#ifndef DFTUTILITY_H_
#define DFTUTILITY_H_

#include "FrequencySignal.h"

void FrequencySignalConvertToPolarCoordinates(FrequencySignal* dft);
void FrequencySignalConvertToRectangularCoordinates(FrequencySignal* dft);

void FrequencySignalAmplifyInPlace(FrequencySignal* dft, float amplifcationCoefficent);
void FrequencySignalAdditionInPlace(FrequencySignal* dftLHS, FrequencySignal* dftRHS);



#endif /* DFTUTILITY_H_ */
